#pragma once

#include "public.h"

#include <yt/yt/client/scheduler/public.h>

#include <yt/yt/ytlib/job_tracker_client/proto/job_tracker_service.pb.h>

namespace NYT::NJobTrackerClient {

////////////////////////////////////////////////////////////////////////////////

struct TJobToAbort
{
    TJobId JobId;
    std::optional<NScheduler::EAbortReason> AbortReason = {};
};

////////////////////////////////////////////////////////////////////////////////

namespace NProto {

void ToProto(NProto::TJobToAbort* protoJobToAbort, const NJobTrackerClient::TJobToAbort& jobToAbort);

void FromProto(NJobTrackerClient::TJobToAbort* jobToAbort, const NProto::TJobToAbort& protoJobToAbort);

} // namespace NProto

////////////////////////////////////////////////////////////////////////////////

// TODO(pogorelov): Remove it.
void AddJobToAbort(NProto::TRspHeartbeat* response, const TJobToAbort& jobToAbort);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NJobTrackerClient
