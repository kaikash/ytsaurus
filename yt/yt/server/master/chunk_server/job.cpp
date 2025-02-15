#include "job.h"
#include "chunk.h"
#include "chunk_manager.h"
#include "helpers.h"
#include "public.h"

#include <yt/yt/server/master/node_tracker_server/node.h>

namespace NYT::NChunkServer {

using namespace NErasure;
using namespace NNodeTrackerServer;
using namespace NNodeTrackerClient;
using namespace NNodeTrackerClient::NProto;
using namespace NChunkClient;
using namespace NTableServer;
using namespace NObjectClient;
using namespace NChunkClient::NProto;
using namespace NJobTrackerClient::NProto;

////////////////////////////////////////////////////////////////////////////////

TJob::TJob(
    TJobId jobId,
    EJobType type,
    TJobEpoch jobEpoch,
    NNodeTrackerServer::TNode* node,
    const TNodeResources& resourceUsage,
    TChunkIdWithIndexes chunkIdWithIndexes)
    : JobId_(jobId)
    , Type_(type)
    , JobEpoch_(jobEpoch)
    , NodeAddress_(IsObjectAlive(node) ? node->GetDefaultAddress() : "")
    , ResourceUsage_(resourceUsage)
    , ChunkIdWithIndexes_(chunkIdWithIndexes)
    , StartTime_(TInstant::Now())
    , State_(EJobState::Running)
{ }

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NChunkServer
