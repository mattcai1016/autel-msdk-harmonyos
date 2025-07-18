#ifndef IFLIGHT_PARAMS_H
#define IFLIGHT_PARAMS_H

#include <memory>

#include "ErrorCode.h"
#include "CompletionListener.h"
#include "FlightPropertyKeyDataType.h"
#include "IControllCompletionListener.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IFlightParams
{
public:
    // =======参数查询、设置类接口=======
    // 操作模式(新手械/专业模式)
    virtual ErrorCode GetOperationMode(uint32_t deviceId, std::shared_ptr<CompletionListener<OperatorModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetOperationMode(uint32_t deviceId, OperatorModeEnum operatorModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 最大飞行高度
    virtual ErrorCode GetMaxHeight(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetMaxHeight(uint32_t deviceId, float maxHeight, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 最大飞行半径
    virtual ErrorCode GetMaxRadius(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetMaxRadius(uint32_t deviceId, float maxRadius, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 最大水平飞行速度
    virtual ErrorCode GetMaxHorizontalSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetMaxHorizontalSpeed(uint32_t deviceId, float maxHorizontalSpeed, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 最大上升飞行速度
    virtual ErrorCode GetMaxAscentSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetMaxAscentSpeed(uint32_t deviceId, float maxAscentSpeed, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 最大下降飞行速度
    virtual ErrorCode GetDescentSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetDescentSpeed(uint32_t deviceId, float descentSpeed, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 任务返航高度
    virtual ErrorCode GetMissionBackHeight(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetMissionBackHeight(uint32_t deviceId, float missionManagerBackHeight, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 返航水平速度
    virtual ErrorCode GetBackHorizontalSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBackHorizontalSpeed(uint32_t deviceId, float speed, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 返航垂直速度
    virtual ErrorCode GetBackVerticalSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBackVerticalSpeed(uint32_t deviceId, float speed, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // EXP左转右转灵敏度
    virtual ErrorCode GetYawAngleSensitivity(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetYawAngleSensitivity(uint32_t deviceId, float yawAngleSensitivity, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // EXP向前向后灵敏度
    virtual ErrorCode GetPitchSensitivity(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPitchSensitivity(uint32_t deviceId, float pitchSensitivity, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // EXP向左向右灵敏度
    virtual ErrorCode GetRollSensitivity(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRollSensitivity(uint32_t deviceId, float rollSensitivity, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // EXP上升下降灵敏度
    virtual ErrorCode GetThrustSensitivity(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThrustSensitivity(uint32_t deviceId, float thrustSensitivity, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 姿态灵敏度
    virtual ErrorCode GetAttitudeSensitivity(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetAttitudeSensitivity(uint32_t deviceId, float attitudeSensitivity, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 刹车灵敏度
    virtual ErrorCode GetBrakeSensitivity(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBrakeSensitivity(uint32_t deviceId, float brakeSensitivity, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 偏航行程灵敏度
    virtual ErrorCode GetYawTripSensitivity(uint32_t deviceId, std::shared_ptr<CompletionListener<float>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetYawTripSensitivity(uint32_t deviceId, float yawTripSensitivity, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 电池低电量告警门限
    virtual ErrorCode GetLowPowerWarningThreshold(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetLowPowerWarningThreshold(uint32_t deviceId, int threshold, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 电池严重低电量告警门限
    virtual ErrorCode GetSeriousLowPowerWarningThreshold(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetSeriousLowPowerWarningThreshold(uint32_t deviceId, int threshold, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 飞机失联行为
    virtual ErrorCode GetRCLostAction(uint32_t deviceId, std::shared_ptr<CompletionListener<DroneLostActionEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRCLostAction(uint32_t deviceId, DroneLostActionEnum droneLostActionEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 飞行器档位
    virtual ErrorCode GetGearLever(uint32_t deviceId, std::shared_ptr<CompletionListener<GearLevelEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetGearLever(uint32_t deviceId, GearLevelEnum gearLevelEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // GPS工作模式
    virtual ErrorCode GetFcsSwitchGpsMode(uint32_t deviceId, std::shared_ptr<CompletionListener<DroneGpsEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFcsSwitchGpsMode(uint32_t deviceId, DroneGpsEnum droneGpsEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 飞机运行模式
    virtual ErrorCode GetDroneRunningMode(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetDroneRunningMode(uint32_t deviceId, int runningMode, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    // =======功能开关类接口=======
    // 飞行器激活状态
    virtual ErrorCode GetAircraftActivationState(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetAircraftActivationState(uint32_t deviceId, int activated, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 低电量返航开关：//0: disable , 无设置 1: return home，返航 2: loiter, 悬停 3: auto land，自主降落 4: continue the mission，继续任务
    virtual ErrorCode GetLowPowerBackState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetLowPowerBackState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 蜂鸣状态（查找飞机）开关
    virtual ErrorCode GetBuzzingState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetBuzzingState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ATTI模式开关
    virtual ErrorCode GetAttiModeState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetAttiModeState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 协调转弯开关
    virtual ErrorCode GetCoordinatedTurnState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCoordinatedTurnState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 融合视觉定位开关
    virtual ErrorCode GetFusionVisionLocationState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFusionVisionLocationState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 绕障功能开关
    virtual ErrorCode GetFcsApasModeState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFcsApasModeState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 静默模式状态开关
    virtual ErrorCode GetSilentModeState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetSilentModeState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 超级电容开关
    virtual ErrorCode GetFCSSupercapacitorsState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFCSSupercapacitorsState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // GPS飞行开关
    virtual ErrorCode GetFcsGpsSwitchState(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFcsGpsSwitchState(uint32_t deviceId,  int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    virtual ErrorCode GetMultiDevFcsGpsSwitchState(std::shared_ptr<IControllCompletionListener> listener) = 0;
    virtual ErrorCode SetMultiDevFcsGpsSwitchState(int32_t s32Switch, std::shared_ptr<IControllCompletionListener> listener) = 0;

    // RTK北斗模式开关
    virtual ErrorCode GetFcsSwitchRtkMode(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFcsSwitchRtkMode(uint32_t deviceId, int32_t s32Switch,std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 紧急停桨生效配置
    virtual ErrorCode GetFcsTmpDisarmAir(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFcsTmpDisarmAir(uint32_t deviceId, int32_t s32Switch,std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
};
}  // namespace AutelMobileSdk

#endif
