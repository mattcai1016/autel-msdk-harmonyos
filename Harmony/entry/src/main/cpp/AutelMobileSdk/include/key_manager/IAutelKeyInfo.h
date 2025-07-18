#ifndef IAUTEL_KEY_INFO_H
#define IAUTEL_KEY_INFO_H

#include <string>
#include <memory>
#include "IMsgConverter.h"
#include "BaseType.h"
#include "MsgType.h"
#include "Common.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IAutelKeyInfo
{
public:
    IAutelKeyInfo(MessageType messageType, ComponentType componentType = ComponentType::Common, int subComponentType = 0,
        std::shared_ptr<IMsgConverter> egressConverter = nullptr, std::shared_ptr<IMsgConverter> ingressConverter = nullptr);

    IAutelKeyInfo(MessageType messageType, ParameterType parameterType = ParameterType::PARAMETER_TYPE_UNKNOW,
        ComponentType componentType = ComponentType::Common, int subComponentType = 0, std::shared_ptr<IMsgConverter> egressConverter = nullptr,
        std::shared_ptr<IMsgConverter> ingressConverter = nullptr);

    IAutelKeyInfo(UavComponentType uavComponentType, const std::string& keyName, int subUavComponentType = 0, ComponentType componentType = ComponentType::Common, int subComponentType = 0,
                  std::shared_ptr<IMsgConverter> egressConverter = nullptr, std::shared_ptr<IMsgConverter> ingressConverter = nullptr);

    IAutelKeyInfo(UavComponentType uavComponentType, int subUavComponentType, ComponentType componentType = ComponentType::Common, int subComponentType = 0,
                  std::shared_ptr<IMsgConverter> egressConverter = nullptr, std::shared_ptr<IMsgConverter> ingressConverter = nullptr);

public:
    static int64_t GetKeyType(MessageType messageType, ParameterType parameterType = ParameterType::PARAMETER_TYPE_UNKNOW);
    static int64_t GetKeyType(int uavComponentType, int subUavComponentType);

    inline IAutelKeyInfo& SetCanSet(bool canSet)
    {
        m_canSet = canSet;
        return *this;
    }

    inline IAutelKeyInfo& SetCanGet(bool canGet)
    {
        m_canGet = canGet;
        return *this;
    }

    inline IAutelKeyInfo& SetCanListen(bool canListen)
    {
        m_canListen = canListen;
        return *this;
    }

    inline IAutelKeyInfo& SetCanReport(bool canReport)
    {
        m_canReport = canReport;
        return *this;
    }

    inline IAutelKeyInfo& SetCanPerformAction(bool canPerformAction)
    {
        m_canPerformAction = canPerformAction;
        return *this;
    }

    inline IAutelKeyInfo& SetIsEvent(bool isEvent)
    {
        m_isEvent = isEvent;
        return *this;
    }

    inline IAutelKeyInfo& SetIdentifier(const std::string& identifier)
    {
        m_identifier = identifier;
        return *this;
    }

    inline IAutelKeyInfo& SetInnerIdentifier(const std::string& innerIdentifier)
    {
        m_innerIdentifier = innerIdentifier;
        return *this;
    }

    inline IAutelKeyInfo& SetCanRetry(bool canRetry)
    {
        m_canRetry = canRetry;
        return *this;
    }
    
    inline IAutelKeyInfo& SetCommon(bool common)
    {
        m_common = common;
        return *this;
    }
    
    inline IAutelKeyInfo& SetDestNodeId(int destNodeId)
    {
        m_destNodeId = destNodeId;
        return *this;
    }
    
    inline IAutelKeyInfo& SetSrcNodeId(int srcNodeId)
    {
        m_srcNodeId = srcNodeId;
        return *this;
    }
    
    inline IAutelKeyInfo& SetTopicType(int topicType)
    {
        m_topicType = topicType;
        return *this;
    }
    
    inline IAutelKeyInfo& SetTopicId(int topicId)
    {
        m_topicId = topicId;
        return *this;
    }

    inline IAutelKeyInfo& SetUavComponentType(UavComponentType uavComponentType)
    {
        m_uavComponentType = uavComponentType;
        return *this;
    }

    inline MessageType GetMessageType() const
    {
        return m_messageType;
    }

    std::string GetMessageTypeName() const;

    inline ParameterType GetParameterType() const
    {
        return m_parameterType;
    }

    std::string GetParameterTypeName() const;

    inline ComponentType GetComponentType() const
    {
        return m_componentType;
    }

    inline int GetSubComponentType() const
    {
        return m_subComponentType;
    }

    inline bool CanSet() const
    {
        return m_canSet;
    }

    inline bool CanGet() const
    {
        return m_canGet;
    }

    inline bool CanListen() const
    {
        return m_canListen;
    }

    inline bool CanReport() const
    {
        return m_canReport;
    }

    inline bool CanPerformAction() const
    {
        return m_canPerformAction;
    }

    inline bool IsEvent() const
    {
        return m_isEvent;
    }

    inline const std::string& GetIdentifier() const
    {
        return m_identifier;
    }

    inline const std::string& GetInnerIdentifier() const
    {
        return m_innerIdentifier;
    }
    std::string GetUavComponentTypeName() const;
    std::string GetSubUavComponentTypeName() const;
    inline int GetUavComponentType() const
    {
        return static_cast<int>(m_uavComponentType);
    }

    inline int GetSubUavComponentType() const
    {
        return m_subUavComponentType;
    }


    inline int64_t GetKeyType() const
    {
        return GetKeyType(m_messageType, m_parameterType);
    }

    inline int64_t GetUavKeyType() const
    {
        return GetKeyType(static_cast<int>(m_uavComponentType), static_cast<int>(m_subUavComponentType));
    }

    inline std::shared_ptr<IMsgConverter> GetEgressDataConverter()
    {
        return m_egressDataConverter;
    }

    inline std::shared_ptr<IMsgConverter> GetIngressDataConverter()
    {
        return m_ingressDataConverter;
    }

    inline bool CanRetry() const
    {
        return m_canRetry;
    }
    
    inline bool IsCommon() const
    {
        return m_common;
    }
    
    inline int GetDstNodeId() const
    {
        return m_destNodeId;
    }
    
    inline int GetSrcNodeId() const
    {
        return m_srcNodeId;
    }
    
    inline int GetTopicType() const
    {
        return m_topicType;
    }
    
    inline int GetTopicId() const
    {
        return m_topicId;
    }

    inline int GetVersion() const
    {
        return m_version;
    }

    size_t HashCode() const;

    std::string ToString() const;

    inline const std::string& GetKeyName() const
    {
        return m_keyName;
    }
    
    inline IAutelKeyInfo& SetKeyName(const std::string& keyName)
    {
        m_keyName = keyName;
        return *this;
    }
    
    inline std::shared_ptr<IMsgConverter> GetChannelTopicConverter() const
    {
        return m_channelTopicConverter;
    }
    
    inline IAutelKeyInfo& SetChannelTopicConverter(std::shared_ptr<IMsgConverter> converter)
    {
        m_channelTopicConverter = converter;
        return *this;
    }
    
    inline std::shared_ptr<IMsgConverter> GetReportMessageConverter() const
    {
        return m_reportMessageConverter;
    }
    
    inline IAutelKeyInfo& SetReportMessageConverter(std::shared_ptr<IMsgConverter> converter)
    {
        m_reportMessageConverter = converter;
        return *this;
    }

protected:
    MessageType m_messageType = MessageType::INVALID_MSG;
    ParameterType m_parameterType = ParameterType::PARAMETER_TYPE_UNKNOW;
    ComponentType m_componentType = ComponentType::Unknown;
    int m_subComponentType = 0;
    UavComponentType m_uavComponentType = UavComponentType::COMPONENT_ID_UNKNOW;
    int m_subUavComponentType = 0;
    bool m_canGet = false;
    bool m_canSet = false;
    bool m_canListen = false;
    bool m_canReport = false;
    bool m_canPerformAction = false;
    bool m_isEvent = false;
    bool m_isActionKey = false;
    bool m_canRetry = false;
    bool m_common = false; // 是否是龙鱼通用指令
    int m_destNodeId = 0;
    int m_srcNodeId = 1;  // 默认值设为1
    int m_topicType = 0;  // 可能需要根据常量定义调整默认值
    int m_topicId = 0;    // 可能需要根据常量定义调整默认值
    int m_version = 0;
    std::string m_identifier;
    std::string m_innerIdentifier;
    std::string m_keyName;
    std::shared_ptr<IMsgConverter> m_egressDataConverter = nullptr;
    std::shared_ptr<IMsgConverter> m_ingressDataConverter = nullptr;
    std::shared_ptr<IMsgConverter> m_channelTopicConverter = nullptr;
    std::shared_ptr<IMsgConverter> m_reportMessageConverter = nullptr;
};
} // namespace AutelMobileSdk

#endif
