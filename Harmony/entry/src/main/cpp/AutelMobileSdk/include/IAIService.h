#ifndef IAISERVICE_H
#define IAISERVICE_H

#include <CompletionListener.h>
#include <ErrorCode.h>
#include <AIServiceKeyDataType.h>
#include <KeyListener.h>

namespace AutelMobileSdk
{
class AUTELSDK_API IAIService
{
public:
    // ==========参数查询、设置，执行操作类接口==========
    // 目标检测类型
    virtual ErrorCode GetTrackingTargetType(uint32_t deviceId, std::shared_ptr<CompletionListener<AIDetectConfig>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTrackingTargetType(uint32_t deviceId, const AIDetectConfig& aiDetectConfig, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // planner bag record开关
    virtual ErrorCode GetPlannerRosBagRecordState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPlannerRosBagRecordState(uint32_t deviceId, int32_t rosBag, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==========消息监听类接口==========
    // 侦测区域上报。飞机端检测目标并将检测框发送至App
    virtual ErrorCode ListenSecurityDetectTarget(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<DetectTrackAreaNotify>>& listener) = 0;
    virtual void CancelListenDetectTrackAreaNotify(uint32_t deviceId, ObjectId objectId) = 0;

    // 跟踪目标上报。用户在App上选定目标后，飞机端锁定目标后将跟踪框发送至App
    virtual ErrorCode ListenTrackingTargetRect(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<TrackAreaNotify>>& listener) = 0;
    virtual void CancelListenTrackingTargetRect(uint32_t deviceId, ObjectId objectId) = 0;

    // 飞机端检测目标并拍照上报，DetectObjectPhotoInfo待确认
    virtual ErrorCode ListenDetectPhotoInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<DetectPhotoInfo>>& listener) = 0;
    virtual void CancelListenDetectPhotoInfo(uint32_t deviceId, ObjectId objectId) = 0;
};
}
#endif // IAISERVICE_H
