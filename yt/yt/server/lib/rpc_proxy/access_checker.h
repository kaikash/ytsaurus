#pragma once

#include "public.h"

namespace NYT::NRpcProxy {

////////////////////////////////////////////////////////////////////////////////

struct IAccessChecker
    : public TRefCounted
{
    virtual TError ValidateAccess(const TString& user) const = 0;
};

DEFINE_REFCOUNTED_TYPE(IAccessChecker)

////////////////////////////////////////////////////////////////////////////////

IAccessCheckerPtr CreateNoopAccessChecker();

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NRpcProxy
