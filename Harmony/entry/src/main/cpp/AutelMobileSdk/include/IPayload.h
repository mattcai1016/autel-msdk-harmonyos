#ifndef IPAYLOAD_H
#define IPAYLOAD_H

#include <list>
#include <memory>
#include "KeyListener.h"
#include "CompletionListener.h"
#include "ErrorCode.h"
#include "PayloadKeyDataType.h"

namespace AutelMobileSdk
{

class AUTELSDK_API IPayload
{
public:
    // ========== 设置类接口 ==========
    // Tracer 工作模式控制
    virtual ErrorCode TracerWorkModeControl(uint32_t deviceId, const TracerWorkModeControlMessage &param, std::shared_ptr<CompletionListener<TracerWorkModeControlRspMessage>> listener, int retryCount = 0) = 0;
    // 投掷器控制
    virtual ErrorCode ThrowerControl(uint32_t deviceId, const ThrowActionMessage &param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 喊话器控制
    virtual ErrorCode LightSpeakerControl(uint32_t deviceId, const LightSpeakerMessage &param, std::shared_ptr<CompletionListener<LightSpeakerControlRspMessage>> listener, int retryCount = 0) = 0;

    // 极至喊话照明一体机opus实时喊话数据消息
    virtual ErrorCode LightSpeakerRunTimeControl(uint32_t deviceId, const LoudspeakerRealTimeMsg &param, std::shared_ptr<CompletionListener<LightSpeakerRspMessage>> listener, int retryCount = 0) = 0;
    
    // 极至喊话照明一体机查询接口
    virtual ErrorCode LightSpeakerQuery(uint32_t deviceId, const LightSpeakerQueryMessage &param, std::shared_ptr<CompletionListener<LightSpeakerQueryRspMessage>> listener, int retryCount = 0) = 0;

    // ========== 通知类接口 ==========
    // 负载注册列表上报
    virtual ErrorCode ListenAccessPayloadListNtfy(uint32_t deviceId, uint32_t objectId, std::shared_ptr<KeyListener<PayloadList>> listener) = 0;
    virtual void CancelListenAccessPayloadListNtfy(uint32_t deviceId, uint32_t objectId) = 0;
    
    // 低速通道监听
    virtual ErrorCode ListenLowSpeedDataNtfy(uint32_t deviceId, uint32_t objectId, std::shared_ptr<KeyListener<std::string>> listener) = 0;
    virtual void CancelListenLowSpeedDataNtfy(uint32_t deviceId, uint32_t objectId) = 0;
    
    // 高速通道监听
    virtual ErrorCode ListenHighSpeedDataNtfy(uint32_t deviceId, uint32_t objectId, std::shared_ptr<KeyListener<std::string>> listener) = 0;
    virtual void CancelListenHighSpeedDataNtfy(uint32_t deviceId, uint32_t objectId) = 0;

    // Tracer 测量数据上报
    virtual ErrorCode ListenTracerTopicMsgNtfy(uint32_t deviceId, uint32_t objectId, std::shared_ptr<KeyListener<TracerMeasureInfoMessage>> listener) = 0;
    virtual void CancelListenTracerTopicMsgNtfy(uint32_t deviceId, uint32_t objectId) = 0;

    // Tracer 系统信息上报
    virtual ErrorCode ListenTracerSystemInfoNtfy(uint32_t deviceId, uint32_t objectId, std::shared_ptr<KeyListener<TracerSystemInfoMessage>> listener) = 0;
    virtual void CancelListenTracerSystemInfoNtfy(uint32_t deviceId, uint32_t objectId) = 0;

    // 抛投器数据上报
    virtual ErrorCode ListenThrowerTopicMsgNtfy(uint32_t deviceId, uint32_t objectId, std::shared_ptr<KeyListener<ThrowerMessage>> listener) = 0;
    virtual void CancelListenThrowerTopicMsgNtfy(uint32_t deviceId, uint32_t objectId) = 0;

    // psdk文件播放进度上报,0-100,每0.5秒会上报一次
    virtual ErrorCode ListenLightSpeakerVoicePlayStatusNtfy(uint32_t deviceId, uint32_t objectId, std::shared_ptr<KeyListener<ChannelCommonMessage>> listener) = 0;
    virtual void CancelListenLightSpeakerVoicePlayStatusNtfy(uint32_t deviceId, uint32_t objectId) = 0;

};

} // namespace AutelMobileSdk

#endif // IPAYLOAD_H
