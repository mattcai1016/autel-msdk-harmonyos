#ifndef IAUTEL_KEY_H
#define IAUTEL_KEY_H

#include "IAutelKeyInfo.h"

namespace AutelMobileSdk
{
class IAutelKey
{
public:
    virtual ~IAutelKey(){}

    inline int GetProductId() const
    {
        return m_productId;
    }

    inline int GetComponentIndex() const
    {
        return m_componentIndex;
    }

    inline int GetSubComponentIndex() const
    {
        return m_subComponentIndex;
    }

    inline int GetSubComponentType() const
    {
        return m_subComponentType;
    }

    inline std::shared_ptr<IAutelKeyInfo> GetKeyInfo()
    {
        return m_keyInfo;
    }

    inline bool CanSet() const
    {
        return m_keyInfo != nullptr && m_keyInfo->CanSet();
    }

    inline bool CanGet() const
    {
        return m_keyInfo != nullptr && m_keyInfo->CanGet();
    }

    inline bool CanListen() const
    {
        return m_keyInfo != nullptr && m_keyInfo->CanListen();
    }

    inline bool CanPerformAction() const
    {
        return m_keyInfo != nullptr && m_keyInfo->CanPerformAction();
    }

    inline std::string GetKeyIdentifier() const
    {
        return m_keyInfo == nullptr ? "" : m_keyInfo->GetIdentifier();
    }

    inline std::string GetKeyInnerIdentifier() const
    {
        return m_keyInfo == nullptr ? "" : m_keyInfo->GetInnerIdentifier();
    }

    inline MessageType GetMessageType() const
    {
        return m_keyInfo == nullptr ? MessageType::INVALID_MSG : m_keyInfo->GetMessageType();
    }

    inline std::string GetMessageTypeName() const
    {
        return m_keyInfo == nullptr ? "" : m_keyInfo->GetMessageTypeName();
    }

    inline ParameterType GetParameterType() const
    {
        return m_keyInfo == nullptr ? ParameterType::PARAMETER_TYPE_UNKNOW : m_keyInfo->GetParameterType();
    }

    inline std::string GetParameterTypeName() const
    {
        return m_keyInfo == nullptr ? "" : m_keyInfo->GetParameterTypeName();
    }

    inline std::string GetUavComponentTypeName() const
    {
        return m_keyInfo == nullptr ? "" : m_keyInfo->GetUavComponentTypeName();
    }

    inline std::string GetSubUavComponentTypeName() const
    {
        return m_keyInfo == nullptr ? "" : m_keyInfo->GetSubUavComponentTypeName();
    }
    DroneParameterType GetDroneParameterType() const;

    inline int64_t GetKeyType() const
    {
        return m_keyInfo == nullptr ? -1 : m_keyInfo->GetKeyType();
    }

    inline int GetTopicId() const
    {
        return m_keyInfo == nullptr ? 0 : m_keyInfo->GetTopicId();
    }

    inline int GetTopicType() const
    {
        return m_keyInfo == nullptr ? 0 : m_keyInfo->GetTopicType();
    }

    inline int GetVersion() const
    {
        return m_keyInfo == nullptr ? 0 : m_keyInfo->GetVersion();
    }

    inline std::shared_ptr<IMsgConverter> GetEgressDataConverter()
    {
        return m_keyInfo == nullptr ? nullptr : m_keyInfo->GetEgressDataConverter();
    }

    inline std::shared_ptr<IMsgConverter> GetIngressDataConverter()
    {
        return m_keyInfo == nullptr ? nullptr : m_keyInfo->GetIngressDataConverter();
    }

    inline std::shared_ptr<IMsgConverter> GetChannelTopicConverter()
    {
        return m_keyInfo == nullptr ? nullptr : m_keyInfo->GetChannelTopicConverter();
    }

    inline std::shared_ptr<IMsgConverter> GetReportMessageConverter()
    {
        return m_keyInfo == nullptr ? nullptr : m_keyInfo->GetReportMessageConverter();
    }

    size_t HashCode() const;

    virtual std::string ToString() const;

protected:
    IAutelKey(int productId, int componentIndex, int subComponentIndex, int subComponentType, std::shared_ptr<IAutelKeyInfo> keyInfo);
    IAutelKey(int componentIndex, int subComponentIndex, int subComponentType, std::shared_ptr<IAutelKeyInfo> keyInfo);

protected:
    int m_productId = 0;
    int m_componentIndex;
    int m_subComponentIndex;
    int m_subComponentType;
    std::shared_ptr<IAutelKeyInfo> m_keyInfo;
};
} // namespace AutelMobileSdk

#endif
