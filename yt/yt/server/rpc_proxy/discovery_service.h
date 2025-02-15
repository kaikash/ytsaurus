#pragma once

#include "public.h"

#include <yt/yt/client/api/rpc_proxy/public.h>

#include <yt/yt/core/rpc/public.h>

namespace NYT::NRpcProxy {

////////////////////////////////////////////////////////////////////////////////

NRpc::IServicePtr CreateDiscoveryService(
    NRpcProxy::TBootstrap* bootstrap);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NRpcProxy
