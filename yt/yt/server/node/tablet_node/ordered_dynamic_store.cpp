#include "ordered_dynamic_store.h"
#include "tablet.h"
#include "transaction.h"
#include "automaton.h"

#include <yt/yt/server/lib/tablet_node/config.h>

#include <yt/yt/core/ytree/fluent.h>

#include <yt/yt/core/concurrency/scheduler.h>

#include <yt/yt/ytlib/table_client/schemaless_chunk_writer.h>
#include <yt/yt/ytlib/table_client/schemaful_chunk_reader.h>
#include <yt/yt/ytlib/table_client/cached_versioned_chunk_meta.h>
#include <yt/yt/ytlib/table_client/chunk_state.h>

#include <yt/yt/ytlib/chunk_client/chunk_reader.h>
#include <yt/yt/ytlib/chunk_client/chunk_reader_options.h>
#include <yt/yt/ytlib/chunk_client/chunk_reader_statistics.h>
#include <yt/yt/ytlib/chunk_client/config.h>
#include <yt/yt/ytlib/chunk_client/memory_reader.h>
#include <yt/yt/ytlib/chunk_client/memory_writer.h>

#include <yt/yt_proto/yt/client/chunk_client/proto/chunk_meta.pb.h>
#include <yt/yt_proto/yt/client/chunk_client/proto/chunk_spec.pb.h>

#include <yt/yt/client/table_client/row_buffer.h>
#include <yt/yt/client/table_client/unversioned_reader.h>
#include <yt/yt/client/table_client/unversioned_writer.h>
#include <yt/yt/client/table_client/row_batch.h>
#include <yt/yt/client/table_client/name_table.h>

#include <library/cpp/yt/memory/chunked_memory_pool.h>

#include <util/generic/cast.h>

namespace NYT::NTabletNode {

using namespace NYTree;
using namespace NYson;
using namespace NTableClient;
using namespace NTransactionClient;
using namespace NChunkClient;
using namespace NConcurrency;

using NChunkClient::NProto::TChunkSpec;
using NChunkClient::NProto::TChunkMeta;
using NChunkClient::NProto::TDataStatistics;

////////////////////////////////////////////////////////////////////////////////

static const size_t ReaderPoolSize = 16_KB;

struct TOrderedDynamicStoreReaderPoolTag
{ };

////////////////////////////////////////////////////////////////////////////////

class TOrderedDynamicStore::TReader
    : public ISchemafulUnversionedReader
{
public:
    TReader(
        TOrderedDynamicStorePtr store,
        int tabletIndex,
        i64 lowerRowIndex,
        i64 upperRowIndex,
        const std::optional<TColumnFilter>& optionalColumnFilter)
        : Store_(std::move(store))
        , TabletIndex_(tabletIndex)
        , UpperRowIndex_(std::min(upperRowIndex, Store_->GetStartingRowIndex() + Store_->GetRowCount()))
        , MaybeColumnFilter_(optionalColumnFilter)
        , CurrentRowIndex_(std::max(lowerRowIndex, Store_->GetStartingRowIndex()))
    {
        if (!MaybeColumnFilter_) {
            // For flushes and snapshots only.
            return;
        }

        if (MaybeColumnFilter_->IsUniversal()) {
            TColumnFilter::TIndexes columnFilterIndexes;
            // +2 is for (tablet_index, row_index).
            for (int id = 0; id < Store_->Schema_->GetColumnCount() + 2; ++id) {
                columnFilterIndexes.push_back(id);
            }
            MaybeColumnFilter_.emplace(std::move(columnFilterIndexes));
        }

        Pool_ = std::make_unique<TChunkedMemoryPool>(TOrderedDynamicStoreReaderPoolTag(), ReaderPoolSize);
    }

    IUnversionedRowBatchPtr Read(const TRowBatchReadOptions& options) override
    {
        std::vector<TUnversionedRow> rows;
        rows.reserve(options.MaxRowsPerRead);

        i64 dataWeight = 0;
        while (CurrentRowIndex_ < UpperRowIndex_ &&
               std::ssize(rows) < options.MaxRowsPerRead &&
               dataWeight < options.MaxDataWeightPerRead)
        {
            auto row = CaptureRow(Store_->GetRow(CurrentRowIndex_));
            rows.push_back(row);
            dataWeight += GetDataWeight(row);
            ++CurrentRowIndex_;
        }
        if (rows.empty()) {
            return nullptr;
        }
        RowCount_ += rows.size();
        DataWeight_ += dataWeight;

        Store_->PerformanceCounters_->DynamicRowReadCount += rows.size();
        Store_->PerformanceCounters_->DynamicRowReadDataWeightCount += dataWeight;

        return CreateBatchFromUnversionedRows(MakeSharedRange(std::move(rows), MakeStrong(this)));
    }

    TFuture<void> GetReadyEvent() const override
    {
        YT_ABORT();
    }

    TDataStatistics GetDataStatistics() const override
    {
        TDataStatistics dataStatistics;
        dataStatistics.set_row_count(RowCount_);
        dataStatistics.set_data_weight(DataWeight_);
        return dataStatistics;
    }

    TCodecStatistics GetDecompressionStatistics() const override
    {
        return TCodecStatistics();
    }

    bool IsFetchingCompleted() const override
    {
        return false;
    }

    std::vector<TChunkId> GetFailedChunkIds() const override
    {
        return {};
    }

private:
    const TOrderedDynamicStorePtr Store_;
    const int TabletIndex_;
    const i64 UpperRowIndex_;
    std::optional<TColumnFilter> MaybeColumnFilter_;

    std::unique_ptr<TChunkedMemoryPool> Pool_;

    i64 CurrentRowIndex_;
    i64 RowCount_ = 0;
    i64 DataWeight_ = 0;


    TUnversionedRow CaptureRow(TOrderedDynamicRow dynamicRow)
    {
        if (!MaybeColumnFilter_) {
            // For flushes and snapshots only.
            return dynamicRow;
        }

        auto columnCount = std::ssize(MaybeColumnFilter_->GetIndexes());
        auto row = TMutableUnversionedRow::Allocate(Pool_.get(), columnCount);
        for (int index = 0; index < columnCount; ++index) {
            ui16 id = static_cast<ui16>(MaybeColumnFilter_->GetIndexes()[index]);
            auto& dstValue = row[index];
            if (id == 0) {
                dstValue = MakeUnversionedInt64Value(TabletIndex_, id);
            } else if (id == 1) {
                dstValue = MakeUnversionedInt64Value(CurrentRowIndex_, id);
            } else {
                dstValue = dynamicRow[id - 2];
                dstValue.Id = id;
            }
        }
        return row;
    }
};

////////////////////////////////////////////////////////////////////////////////

namespace {

std::optional<int> GetTimestampColumnId(const TTableSchema& schema)
{
    const auto* column = schema.FindColumn(TimestampColumnName);
    if (!column) {
        return std::nullopt;
    }
    return schema.GetColumnIndex(*column);
}

std::optional<int> GetCumulativeDataWeightColumnId(const TTableSchema& schema)
{
    const auto* column = schema.FindColumn(CumulativeDataWeightColumnName);
    if (!column) {
        return std::nullopt;
    }
    return schema.GetColumnIndex(*column);
}

} // namespace

TOrderedDynamicStore::TOrderedDynamicStore(
    TTabletManagerConfigPtr config,
    TStoreId id,
    TTablet* tablet)
    : TDynamicStoreBase(config, id, tablet)
    , TimestampColumnId_(GetTimestampColumnId(*Schema_))
    , CumulativeDataWeightColumnId_(GetCumulativeDataWeightColumnId(*Schema_))
{
    AllocateCurrentSegment(InitialOrderedDynamicSegmentIndex);

    YT_LOG_DEBUG("Ordered dynamic store created");
}

ISchemafulUnversionedReaderPtr TOrderedDynamicStore::CreateFlushReader()
{
    YT_VERIFY(FlushRowCount_ != -1);
    return DoCreateReader(
        -1,
        StartingRowIndex_,
        StartingRowIndex_ + FlushRowCount_,
        std::nullopt);
}

ISchemafulUnversionedReaderPtr TOrderedDynamicStore::CreateSnapshotReader()
{
    return DoCreateReader(
        -1,
        StartingRowIndex_,
        StartingRowIndex_ + GetRowCount(),
        std::nullopt);
}

TOrderedDynamicRow TOrderedDynamicStore::WriteRow(
    TUnversionedRow row,
    TWriteContext* context)
{
    YT_ASSERT(context->Phase == EWritePhase::Commit);

    int columnCount = Schema_->GetColumnCount();
    auto dynamicRow = RowBuffer_->AllocateUnversioned(columnCount);

    for (int index = 0; index < columnCount; ++index) {
        dynamicRow[index] = MakeUnversionedSentinelValue(EValueType::Null, index);
    }

    for (const auto& srcValue : row) {
        auto& dstValue = dynamicRow[srcValue.Id];
        dstValue = RowBuffer_->CaptureValue(srcValue);
    }

    bool versionedWrite = TimestampColumnId_ && dynamicRow[*TimestampColumnId_].Type != EValueType::Null;

    if (TimestampColumnId_ && !versionedWrite) {
        dynamicRow[*TimestampColumnId_] = MakeUnversionedUint64Value(context->CommitTimestamp, *TimestampColumnId_);
    }

    // NB: Includes the weight of the $timestamp column if it exists.
    // NB: Be sure to place writes of all additional columns before this line.
    auto dataWeight = static_cast<i64>(GetDataWeight(dynamicRow));
    if (CumulativeDataWeightColumnId_) {
        // Account for the $cumulative_data_weight column we are adding.
        dataWeight += static_cast<i64>(GetDataWeight(EValueType::Uint64)) - static_cast<i64>(GetDataWeight(EValueType::Null));

        GetTablet()->IncreaseCumulativeDataWeight(dataWeight);
        dynamicRow[*CumulativeDataWeightColumnId_] = MakeUnversionedInt64Value(
            GetTablet()->GetCumulativeDataWeight(),
            *CumulativeDataWeightColumnId_);
    }

    CommitRow(dynamicRow);
    UpdateTimestampRange(context->CommitTimestamp);
    OnDynamicMemoryUsageUpdated();

    ++PerformanceCounters_->DynamicRowWriteCount;
    PerformanceCounters_->DynamicRowWriteDataWeightCount += dataWeight;
    ++context->RowCount;
    context->DataWeight += dataWeight;

    return dynamicRow;
}

TOrderedDynamicRow TOrderedDynamicStore::GetRow(i64 rowIndex)
{
    rowIndex -= StartingRowIndex_;
    YT_ASSERT(rowIndex >= 0 && rowIndex < StoreRowCount_);
    int segmentIndex;
    i64 segmentRowIndex;
    if (rowIndex < (1LL << InitialOrderedDynamicSegmentIndex)) {
        segmentIndex = InitialOrderedDynamicSegmentIndex;
        segmentRowIndex = rowIndex;
    } else {
        segmentIndex = 64 - __builtin_clzl(rowIndex);
        segmentRowIndex = rowIndex - (1ULL << (segmentIndex - 1));
    }
    return TOrderedDynamicRow((*Segments_[segmentIndex])[segmentRowIndex]);
}

std::vector<TOrderedDynamicRow> TOrderedDynamicStore::GetAllRows()
{
    std::vector<TOrderedDynamicRow> rows;
    for (i64 index = StartingRowIndex_; index < StartingRowIndex_ + StoreRowCount_; ++index) {
        rows.push_back(GetRow(index));
    }
    return rows;
}

EStoreType TOrderedDynamicStore::GetType() const
{
    return EStoreType::OrderedDynamic;
}

i64 TOrderedDynamicStore::GetRowCount() const
{
    return StoreRowCount_;
}

TCallback<void(TSaveContext&)> TOrderedDynamicStore::AsyncSave()
{
    using NYT::Save;

    auto tableReader = CreateSnapshotReader();

    return BIND([=, this, this_ = MakeStrong(this)] (TSaveContext& context) {
        YT_LOG_DEBUG("Store snapshot serialization started");

        auto chunkWriter = New<TMemoryWriter>();

        auto tableWriterConfig = New<TChunkWriterConfig>();
        tableWriterConfig->WorkloadDescriptor = TWorkloadDescriptor(EWorkloadCategory::SystemTabletRecovery);
        // Ensure deterministic snapshots.
        tableWriterConfig->SampleRate = 0.0;

        auto tableWriterOptions = New<TChunkWriterOptions>();
        tableWriterOptions->OptimizeFor = EOptimizeFor::Scan;
         // Ensure deterministic snapshots.
        tableWriterOptions->SetChunkCreationTime = false;
        tableWriterOptions->Postprocess();

        auto tableWriter = CreateSchemalessChunkWriter(
            tableWriterConfig,
            tableWriterOptions,
            Schema_,
            /*nameTable*/ nullptr,
            chunkWriter,
            /*dataSink*/ std::nullopt);

        YT_LOG_DEBUG("Serializing store snapshot");

        i64 rowCount = 0;
        while (auto batch = tableReader->Read()) {
            if (batch->IsEmpty()) {
                YT_LOG_DEBUG("Waiting for table reader");
                WaitFor(tableReader->GetReadyEvent())
                    .ThrowOnError();
                continue;
            }

            auto rows = batch->MaterializeRows();
            rowCount += rows.size();
            if (!tableWriter->Write(rows)) {
                YT_LOG_DEBUG("Waiting for table writer");
                WaitFor(tableWriter->GetReadyEvent())
                    .ThrowOnError();
            }
        }

        // pushsin@ forbids empty chunks.
        if (rowCount == 0) {
            Save(context, false);
            return;
        }

        Save(context, true);

        // NB: This also closes chunkWriter.
        YT_LOG_DEBUG("Closing table writer");
        WaitFor(tableWriter->Close())
            .ThrowOnError();

        Save(context, *chunkWriter->GetChunkMeta());

        auto blocks = TBlock::Unwrap(chunkWriter->GetBlocks());
        YT_LOG_DEBUG("Writing store blocks (RowCount: %v, BlockCount: %v)",
            rowCount,
            blocks.size());

        Save(context, blocks);

        YT_LOG_DEBUG("Store snapshot serialization complete");
    });
}

void TOrderedDynamicStore::AsyncLoad(TLoadContext& context)
{
    using NYT::Load;

    if (Load<bool>(context)) {
        auto chunkMeta = New<TRefCountedChunkMeta>(Load<TChunkMeta>(context));
        auto blocks = Load<std::vector<TSharedRef>>(context);

        auto chunkState = New<TChunkState>(GetNullBlockCache());
        chunkState->TableSchema = Schema_;

        auto chunkReader = CreateMemoryReader(
            chunkMeta,
            TBlock::Wrap(blocks));
        auto tableReader = CreateSchemafulChunkReader(
            std::move(chunkState),
            New<TColumnarChunkMeta>(*chunkMeta),
            TChunkReaderConfig::GetDefault(),
            chunkReader,
            TClientChunkReadOptions(),
            Schema_,
            TSortColumns(),
            TReadRange());

        while (auto batch = tableReader->Read()) {
            if (batch->IsEmpty()) {
                WaitFor(tableReader->GetReadyEvent())
                    .ThrowOnError();
                continue;
            }

            for (auto row : batch->MaterializeRows()) {
                LoadRow(row);
            }
        }
    }

    // Cf. YT-4534
    if (StoreState_ == EStoreState::PassiveDynamic ||
        StoreState_ == EStoreState::RemovePrepared)
    {
        // NB: No more changes are possible after load.
        YT_VERIFY(FlushRowCount_ == -1);
        FlushRowCount_ = GetRowCount();
    }

    OnDynamicMemoryUsageUpdated();
}

TOrderedDynamicStorePtr TOrderedDynamicStore::AsOrderedDynamic()
{
    return this;
}

i64 TOrderedDynamicStore::GetTimestampCount() const
{
    return GetRowCount();
}

ISchemafulUnversionedReaderPtr TOrderedDynamicStore::CreateReader(
    const TTabletSnapshotPtr& /*tabletSnapshot*/,
    int tabletIndex,
    i64 lowerRowIndex,
    i64 upperRowIndex,
    const TColumnFilter& columnFilter,
    const NChunkClient::TClientChunkReadOptions& /*chunkReadOptions*/,
    std::optional<EWorkloadCategory> /*workloadCategory*/)
{
    return DoCreateReader(
        tabletIndex,
        lowerRowIndex,
        upperRowIndex,
        columnFilter);
}

void TOrderedDynamicStore::OnSetPassive()
{
    YT_VERIFY(FlushRowCount_ == -1);
    FlushRowCount_ = GetRowCount();
}

void TOrderedDynamicStore::AllocateCurrentSegment(int index)
{
    CurrentSegmentIndex_ = index;
    CurrentSegmentCapacity_ = 1LL << (index - (index == InitialOrderedDynamicSegmentIndex ? 0 : 1));
    CurrentSegmentSize_ = 0;
    Segments_[CurrentSegmentIndex_] = std::make_unique<TOrderedDynamicRowSegment>(CurrentSegmentCapacity_);
}

void TOrderedDynamicStore::OnDynamicMemoryUsageUpdated()
{
    SetDynamicMemoryUsage(GetUncompressedDataSize());
}

void TOrderedDynamicStore::CommitRow(TOrderedDynamicRow row)
{
    if (CurrentSegmentSize_ == CurrentSegmentCapacity_) {
        AllocateCurrentSegment(CurrentSegmentIndex_ + 1);
    }
    (*Segments_[CurrentSegmentIndex_])[CurrentSegmentSize_] = row.GetHeader();
    ++CurrentSegmentSize_;
    StoreRowCount_ += 1;
    StoreValueCount_ += row.GetCount();
}

void TOrderedDynamicStore::LoadRow(TUnversionedRow row)
{
    CommitRow(RowBuffer_->CaptureRow(row, true));
}

ISchemafulUnversionedReaderPtr TOrderedDynamicStore::DoCreateReader(
    int tabletIndex,
    i64 lowerRowIndex,
    i64 upperRowIndex,
    const std::optional<TColumnFilter>& optionalColumnFilter)
{
    return New<TReader>(
        this,
        tabletIndex,
        lowerRowIndex,
        upperRowIndex,
        optionalColumnFilter);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NTabletNode
