#pragma once

#include "private.h"

#include <yt/yt/core/actions/invoker.h>

#include <yt/yt/core/profiling/public.h>

#include <yt/yt/library/profiling/sensor.h>

#include <yt/yt/library/ytprof/api/api.h>

#include <library/cpp/yt/threading/event_count.h>
#include <library/cpp/yt/threading/spin_lock.h>

namespace NYT::NConcurrency {

////////////////////////////////////////////////////////////////////////////////

struct TBucketDescription
{
    std::vector<NProfiling::TTagSet> QueueTagSets;
    std::vector<NYTProf::TProfilerTagPtr> QueueProfilerTags;
    NProfiling::TTagSet BucketTagSet;
};

////////////////////////////////////////////////////////////////////////////////

class TFairShareInvokerQueue
    : public TRefCounted
{
public:
    TFairShareInvokerQueue(
        TIntrusivePtr<NThreading::TEventCount> callbackEventCount,
        const std::vector<TBucketDescription>& bucketDescriptions);

    ~TFairShareInvokerQueue();

    void SetThreadId(TThreadId threadId);

    const IInvokerPtr& GetInvoker(int bucketIndex, int queueIndex) const;

    void Shutdown();

    void DrainProducer();
    void DrainConsumer();

    bool IsRunning() const;

    TClosure BeginExecute(TEnqueuedAction* action);
    void EndExecute(TEnqueuedAction* action);

    void Reconfigure(std::vector<double> weights);

private:
    constexpr static i64 UnitWeight = 1000;

    struct TBucket
    {
        TMpscInvokerQueuePtr Queue;
        std::vector<IInvokerPtr> Invokers;
        NProfiling::TCpuDuration ExcessTime = 0;

        // ceil(UnitWeight / weight).
        int64_t InversedWeight = UnitWeight;
    };

    std::vector<TBucket> Buckets_;

    std::atomic<bool> NeedToReconfigure_ = false;

    YT_DECLARE_SPIN_LOCK(NThreading::TSpinLock, WeightsLock_);
    std::vector<double> Weights_;

    TBucket* CurrentBucket_ = nullptr;

    TBucket* GetStarvingBucket();
};

DEFINE_REFCOUNTED_TYPE(TFairShareInvokerQueue)

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NConcurrency

