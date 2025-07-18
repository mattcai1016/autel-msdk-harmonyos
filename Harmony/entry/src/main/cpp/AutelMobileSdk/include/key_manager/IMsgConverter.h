#ifndef IMSG_CONVERTER_H
#define IMSG_CONVERTER_H

#include <any>
#include <string>
#include <memory>

#include "ErrorCode.h"
#include "MsgType.h"
#include "BaseType.h"

namespace AutelMobileSdk
{
class IMsgConverter
{
public:
    IMsgConverter(MessageType messageType, ParameterType parameterType = ParameterType::PARAMETER_TYPE_UNKNOW);
    IMsgConverter(UavComponentType uavComponentType, int subUavComponentType = 0);
    virtual ~IMsgConverter();

public:
    MessageType GetMessageType() const;
    ParameterType GetParameterType() const;
    UavComponentType GetUavComponentType() const;
    int GetSubUavComponentType() const;

    virtual std::any PackToMsg(const std::any& data) const;
    virtual std::any UnpackFromMsg(const std::any& msg) const;
    virtual DroneParameterType GetDroneParameterType() const;
    virtual AutelStatusCode ValidData(const std::any& data) const;
    virtual std::string ValueToString(const std::any& data) const;

protected:
    MessageType m_messageType = MessageType::INVALID_MSG;
    ParameterType m_parameterType = ParameterType::PARAMETER_TYPE_UNKNOW;
    UavComponentType m_uavComponentType = UavComponentType::COMPONENT_ID_UNKNOW;
    int m_subUavComponentType = 0;
};
} // namespace AutelMobileSdk

#endif
