#include "private.h"

#include <yt/yt/server/lib/hydra_common/config.h>

namespace NYT::NHydra2 {

using namespace NConcurrency;
using namespace NElection;
using namespace NHydra;

////////////////////////////////////////////////////////////////////////////////

TFls<TEpochId> CurrentEpochId;

TCurrentEpochIdGuard::TCurrentEpochIdGuard(TEpochId epochId)
{
    YT_VERIFY(!*CurrentEpochId);
    *CurrentEpochId = epochId;
}

TCurrentEpochIdGuard::~TCurrentEpochIdGuard()
{
    *CurrentEpochId = {};
}

////////////////////////////////////////////////////////////////////////////////

TConfigWrapper::TConfigWrapper(TDistributedHydraManagerConfigPtr config)
    : Config_(config)
{ }

void TConfigWrapper::Set(TDistributedHydraManagerConfigPtr config)
{
    Config_.Store(config);
}

TDistributedHydraManagerConfigPtr TConfigWrapper::Get() const
{
    return Config_.Acquire();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NHydra2
