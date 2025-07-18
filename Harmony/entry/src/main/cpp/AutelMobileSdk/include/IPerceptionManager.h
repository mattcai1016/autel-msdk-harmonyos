#ifndef IPERCEPTIONMANAGER_H
#define IPERCEPTIONMANAGER_H

#include <list>
#include <memory>
#include "KeyListener.h"
#include "CompletionListener.h"
#include "ErrorCode.h"
#include "VisionKeyDataType.h"
#include "IControllCompletionListener.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IPerceptionManager
{
public:
    // ==========控制开关类操作接口==========
    // 水平避障开关
    virtual ErrorCode GetHorizontalObstacleAvoidanceState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetHorizontalObstacleAvoidanceState(uint32_t deviceId, int32_t s32Swtich, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 上方避障开关
    virtual ErrorCode GetTopObstacleAvoidanceState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTopObstacleAvoidanceState(uint32_t deviceId, int32_t s32Swtich, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 下方避障开关
    virtual ErrorCode GetBottomObstacleAvoidanceState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBottomObstacleAvoidanceState(uint32_t deviceId, int32_t s32Swtich, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 雷达开关
    virtual ErrorCode GetRadarDetectionState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRadarDetectionState(uint32_t deviceId, int32_t s32Swtich, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // MIF视觉定位工作状态
    virtual ErrorCode GetAutonomyMifWorkState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetAutonomyMifWorkState(uint32_t deviceId, int32_t s32Swtich, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // MIF视觉定位-地图匹配开关
    virtual ErrorCode GetAutonomyMifMapMatchingState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener,  int retryCount = 0) = 0;
    virtual ErrorCode SetAutonomyMifMapMatchingState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    virtual ErrorCode GetMultiAutonomyMifMapMatchingState(std::shared_ptr<IControllCompletionListener> listener) = 0;
    virtual ErrorCode SetMultiAutonomyMifMapMatchingState(int32_t s32Switch, std::shared_ptr<IControllCompletionListener> listener) = 0;

    // ==========参数设置、查询类操作接口==========
    // 水平避障刹车距离
    virtual ErrorCode GetHorizontalBrakeDistance(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetHorizontalBrakeDistance(uint32_t deviceId, float horizontalBrakeDistance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 水平避障告警距离
    virtual ErrorCode GetHorizontalWarningDistance(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetHorizontalWarningDistance(uint32_t deviceId, float horizontalWarningDistance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 上方避障刹车距离
    virtual ErrorCode GetTopBrakeDistance(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTopBrakeDistance(uint32_t deviceId, float topBrakeDistance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 上方避障告警距离
    virtual ErrorCode GetTopWarningDistance(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTopWarningDistance(uint32_t deviceId, float topWarningDistance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 下方避障刹车距离
    virtual ErrorCode GetBottomBrakeDistance(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBottomBrakeDistance(uint32_t deviceId, float bottomBrakeDistance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 下方避障告警距离
    virtual ErrorCode GetBottomWarningDistance(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBottomWarningDistance(uint32_t deviceId, float bottomWarningDistance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==========消息监听类接口==========
    // 视觉雷达图告警
    virtual ErrorCode ListenEmergencyReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<std::vector<VisionRadarInfo>>>& listener) = 0;
    virtual void CancelListenEmergencyReport(uint32_t deviceId, ObjectId objectId) = 0;
};
}  // namespace AutelMobileSdk

#endif // IPERCEPTIONMANAGER_H
