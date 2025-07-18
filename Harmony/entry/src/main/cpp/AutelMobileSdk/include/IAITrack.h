#ifndef IAITRACK_H
#define IAITRACK_H

#include "CompletionListener.h"
#include "ErrorCode.h"
#include "KeyListener.h"
#include "AITrackKeyDataType.h"
#include "AIServiceKeyDataType.h"

namespace AutelMobileSdk
{
class IAITrack
{
public:
    // 进入智能跟踪模式
    virtual ErrorCode EnterTracking(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出智能跟踪模式
    virtual ErrorCode ExitTracking(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 智能跟踪锁定
    virtual ErrorCode LockTargetRectangle(uint32_t deviceId, const TrackTargetRectangle& targetRect, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 自由跟随
    virtual ErrorCode SetFreeFollow(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 悬停跟随
    virtual ErrorCode SetHoverFollow(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 智能八方位跟随
    virtual ErrorCode SetDynamicFollow(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 平行跟随
    virtual ErrorCode SetParallelFollow(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止跟随任务
    virtual ErrorCode StopTracking(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 进入红外智能跟踪模式
    virtual ErrorCode EnterInfraredTracking(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出红外智能跟踪模式
    virtual ErrorCode ExitInfraredTracking(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 红外智能跟踪锁定
    virtual ErrorCode LockInfraredTargetRect(uint32_t deviceId, const TrackTargetRectangle& targetRect, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 红外自由跟随
    virtual ErrorCode SetInfraredFreeFollow(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 红外悬停跟随
    virtual ErrorCode SetInfraredHoverFollow(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 红外智能八方位
    virtual ErrorCode SetInfraredDynamicFollow(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 红外平行跟随
    virtual ErrorCode SetInfraredParallel(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止红外跟随任务
    virtual ErrorCode StopInfraredTracking(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 进入安防智能检测模式
    virtual ErrorCode EnterSecurityIntelligentDetect(uint32_t deviceId, const AIDetectConfig& cfg, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出安防智能检测模式
    virtual ErrorCode ExitSecurityIntelligentDetect(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 进入全景智能检测模式
    virtual ErrorCode EnterPanoramaIntelligentDetect(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 退出全景智能检测模式
    virtual ErrorCode ExitPanoramaIntelligentDetect(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // =========智能锁定模式==========
    // 进入智能锁定模式
    virtual ErrorCode EnterIntelligentLock(uint32_t deviceId, const AIDetectConfig& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    // 开始智能锁定
    virtual ErrorCode StartIntelligentLock(uint32_t deviceId, const TrackTargetRectangle& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    // 退出智能锁定
    virtual ErrorCode ExitInterlligentLock(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
};
}
#endif // IAITRACK_H
