#include "address_helpers.h"

#include <yt/yt/core/net/address.h>
#include <yt/yt/core/net/local_address.h>

namespace NYT::NApi::NRpcProxy {

using namespace NNet;

////////////////////////////////////////////////////////////////////////////////

const EAddressType DefaultAddressType(EAddressType::InternalRpc);
const TString DefaultNetworkName("default");

////////////////////////////////////////////////////////////////////////////////

TAddressMap GetLocalAddresses(const NNodeTrackerClient::TNetworkAddressList& addresses, int port)
{
    // Append port number.
    TAddressMap result;
    result.reserve(addresses.size());
    for (const auto& [networkName, networkAddress] : addresses) {
        YT_VERIFY(result.emplace(networkName, BuildServiceAddress(networkAddress, port)).second);
    }

    // Add default address.
    result.emplace(DefaultNetworkName, BuildServiceAddress(GetLocalHostName(), port));

    return result;
}

////////////////////////////////////////////////////////////////////////////////

std::optional<TString> GetAddressOrNull(
    const TProxyAddressMap& addresses,
    EAddressType type,
    const TString& network)
{
    auto typeAddresses = addresses.find(type);
    if (typeAddresses != addresses.end()) {
        auto it = typeAddresses->second.find(network);
        if (it != typeAddresses->second.end()) {
            return it->second;
        }
    }
    return std::nullopt;
};

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NApi::NRpcProxy
