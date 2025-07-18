#ifndef IAUTEL_KEY_FACTORY_H
#define IAUTEL_KEY_FACTORY_H

#include "IAutelKey.h"
#include "SdkApiContext.h"
#include "EnumNameConverter.h"

namespace AutelMobileSdk
{
class IAutelKeyBuilder
{
public:
    std::shared_ptr<IAutelKey> GetKey(MessageType messageType, ParameterType parameterType = ParameterType::PARAMETER_TYPE_UNKNOW)
    {
        auto keyType = IAutelKeyInfo::GetKeyType(messageType, parameterType);
        auto keys = GetKeyMap();
        auto itr = keys.find(keyType);
        if (itr != keys.cend() && itr->second != nullptr) {
            return itr->second;
        }

        API_ERROR("The message type is not registered, failed to get key. messageType={}({}), parameterType={}({})",
            GetMessageTypeName(messageType), messageType, GetParameterTypeName(parameterType), parameterType);
        return nullptr;
    }


    std::shared_ptr<IAutelKey> GetKey(UavComponentType uavComponentType, int subUavComponentType)
    {
        auto keyType = IAutelKeyInfo::GetKeyType(static_cast<int>(uavComponentType), subUavComponentType);
        auto keys = GetKeyMap();
        auto itr = keys.find(keyType);
        if (itr != keys.cend() && itr->second != nullptr) {
            return itr->second;
        }

        API_ERROR("The message type is not registered, failed to get key. UavComponentType={} , subUavComponentType={}", uavComponentType, subUavComponentType);
        return nullptr;
    }


protected:
    virtual const std::unordered_map<int64_t, std::shared_ptr<IAutelKey>>& GetKeyMap() const = 0;
};

class IAutelKeyFactory
{
public:
    virtual IAutelKeyBuilder* GetCameraKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetCommonKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetAirLinkKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetFlightControlKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetFlightMissionKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetFlightPropertyKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetGimbalKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetMissionManagerKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetNetworkingKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetVisionKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetPerceptionKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetAIServiceKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetAITrackKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetRCKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetAccessoriesProxyKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetSwarmBuilder() = 0;
    virtual IAutelKeyBuilder* GetNestKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetRtkKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetLteKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetUpgradeKeyBuilder() = 0;
    virtual IAutelKeyBuilder* GetPayloadKeyBuilder() = 0;
};
} // namespace AutelMobileSdk

#endif // FLIGHTPROPERTYKEYFACTORY_H
