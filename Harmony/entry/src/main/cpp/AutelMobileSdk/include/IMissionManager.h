#ifndef IMISSION_MANAGER_H
#define IMISSION_MANAGER_H

#include <memory>
#include "CompletionListener.h"
#include "ErrorCode.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IMissionManager
{
public:
    // 融合雷达数据开关 false - 关闭雷达数据融合 true - 开启雷达数据融合
    virtual ErrorCode GetRadarFusionState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRadarFusionState(uint32_t deviceId, int s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 精准降落开关 false-关闭二维码精准降落 true-开启二维码精准降落
    virtual ErrorCode GetPreciseLandingState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPreciseLandingState(uint32_t deviceId, int s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 使能返航绕障 false-关闭返航绕障 true-打开返航绕障
    virtual ErrorCode GetReturnObstacleAvoidanceState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetReturnObstacleAvoidanceState(uint32_t deviceId, int s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 是否开启降落保护
    virtual ErrorCode GetLandingProtectionState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetLandingProtectionState(uint32_t deviceId, int s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 是否忽略风险强制降落
    virtual ErrorCode GetIgnoreLandingRiskState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetIgnoreLandingRiskState(uint32_t deviceId, int s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 电网自动任务起飞高度
    virtual ErrorCode GetTakeoffHeight(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTakeoffHeight(uint32_t deviceId, float f32Height, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    //抵达首个航点飞行速度
    virtual ErrorCode GetStartHorSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetStartHorSpeed(uint32_t deviceId, float f32Height, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

};
}

#endif // IMISSIONMANAGER_H
