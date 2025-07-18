#ifndef IAIR_LINK_H
#define IAIR_LINK_H

#include <memory>
#include "AirLinkKeyDataType.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "ErrorCode.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IAirLink
{
public:
    // ==========参数查询、设置，执行操作类接口==========
    // 图传频段模式
    virtual ErrorCode GetBandMode(uint32_t deviceId, std::shared_ptr<CompletionListener<AirLinkBandModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBandMode(uint32_t deviceId, AirLinkBandModeEnum airLinkBandModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图传清晰度模式
    virtual ErrorCode GetTransmissionMode(uint32_t deviceId, std::shared_ptr<CompletionListener<VideoTransMissionModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTransmissionMode(uint32_t deviceId, VideoTransMissionModeEnum videoTransMissionModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 辐射功率模式
    virtual ErrorCode GetFccCeMode(uint32_t deviceId, std::shared_ptr<CompletionListener<FccCeModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFccCeMode(uint32_t deviceId, FccCeModeEnum fccCeModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 切换高速模式
    virtual ErrorCode GetSpeedMode(uint32_t deviceId, std::shared_ptr<CompletionListener<HighSpeedEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetSpeedMode(uint32_t deviceId, HighSpeedEnum highSpeedEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图传可见光最大码率
    virtual ErrorCode GetVisibleLightMaxRate(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetVisibleLightMaxRate(uint32_t deviceId, int visibleLightMaxRate, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 4G推流最大码率
    virtual ErrorCode Get4GStreamMaxRate(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode Set4GStreamMaxRate(uint32_t deviceId, int maxRate, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 开始对频，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode StartMatching(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 重置对频标志
    virtual ErrorCode ResetMatchFlag(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 进入图传静默模式
    virtual ErrorCode EnterSilenceMode(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // App图传显示模式
    virtual ErrorCode SplitAppScreenInfo(uint32_t deviceId, const GimbalTransmission& screenInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==========消息监听类接口==========
    // 对频进度上报事件，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode ListenMatchingStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<AirLinkMatchStatusEnum>>& listener) = 0;
    virtual void CancelListenMatchingStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // 图传信号强度上报，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode ListenSignalStrength(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<AirLinkSignalStrengthBean>>& listener) = 0;
    virtual void CancelListenSignalStrength(uint32_t deviceId, ObjectId objectId) = 0;

    // 用户单击电池确认连接通知
    virtual ErrorCode ListenConnectionConfirm(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<void>>& listener) = 0;
    virtual void CancelListenConnectionConfirm(uint32_t deviceId, ObjectId objectId) = 0;
};
}  // namespace AutelMobileSdk

#endif
