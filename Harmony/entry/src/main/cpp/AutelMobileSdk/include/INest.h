#ifndef INEST_H
#define INEST_H

#include <memory>
#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "NestDataType.h"

namespace AutelMobileSdk
{
class AUTELSDK_API INest
{
public:
    // ==========参数查询、设置，执行操作类接口==========
    // 舱门控制
    virtual ErrorCode ControlNestCabin(uint32_t deviceId, const CabinCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 三轴控制-X
    virtual ErrorCode ControlNestXRod(uint32_t deviceId, const RodCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 三轴控制-Y
    virtual ErrorCode ControlNestYRod(uint32_t deviceId, const RodCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 三轴控制-Z
    virtual ErrorCode ControlNestZRod(uint32_t deviceId, const RodCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 无人机充电
    virtual ErrorCode ControlNestCharge(uint32_t deviceId, const ChargeCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 机巢复位
    virtual ErrorCode ResetNest(uint32_t deviceId, const NestResetCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 校准操作指令
    virtual ErrorCode SetNestCalibrate(uint32_t deviceId, const CalibrateCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 单步校准操作
    virtual ErrorCode SetNestSingleCalibrate(uint32_t deviceId, const NestSingleCalibration& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 机巢系统配置
    virtual ErrorCode SetNestSystemConfig(uint32_t deviceId, const NestSystemConfig& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 无人机开关机
    virtual ErrorCode NestTurnOnOff(uint32_t deviceId, const DroneCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 空调开关控制
    virtual ErrorCode ControlNestAC(uint32_t deviceId, const ACCommand& param, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;

    // 机巢急停控制
    virtual ErrorCode ControlNestScram(uint32_t deviceId, const EmergencyCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 自动命令
    virtual ErrorCode SetNestAutoCommand(uint32_t deviceId, const AutomaticCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 补光灯控制
    virtual ErrorCode ControlNestFillLightSwitch(uint32_t deviceId, const NestCommonSwitchMsg& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 收桨控制
    virtual ErrorCode ControlNestRetractPaddle(uint32_t deviceId, std::shared_ptr<CompletionListener<AutelMobileSdk::NestWaitTime>> listener, int retryCount = 0) = 0;

    // 机巢备用电池开关
    virtual ErrorCode ControlBackupBattery(uint32_t deviceId, const BackupBatteryCommand& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 机巢看门狗控制
    virtual ErrorCode ControlWatchDog(uint32_t deviceId, const NestWatchDogMsg& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 机巢直供电开关
    virtual ErrorCode ControlNestExternalPowerSwitch(uint32_t deviceId, const NestExternalPowerSwitchMsg& param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==================== 通知上报相关接口 ============================
    virtual ErrorCode VirtualPoleStatusReport(uint32_t deviceId, const NestVirtualPoleStateMsg & param) = 0;

    // 机巢精降就绪通知(机巢状态同步给飞机)
    virtual ErrorCode ListenNestFineDropReadyReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestStatusInfoNotifyToDroneMsg>>& listener) = 0;
    virtual void CancelNestFineDropReadyReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 机巢状态信息通知
    virtual ErrorCode ListenNestStatusInfoReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestStatusNtfy>>& listener) = 0;
    virtual void CancelListenNestStatusInfoReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 机身电池动态信息上报
    virtual ErrorCode ListenNestBatteryDynamicStatusReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestBatteryStatusNtfy>>& listener) = 0;
    virtual void CancelListenNestBatteryDynamicStatusReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 机巢备用电池信息上报
    virtual ErrorCode ListenNestBackupBatteryStatusReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestBackupBatteryStatusNtfy>>& listener) = 0;
    virtual void CancelListenNestBackupBatteryStatusReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 电机驱动板信息上报
    virtual ErrorCode ListenNestMotorDriverStatusReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestMotorDriverStateNtfy>>& listener) = 0;
    virtual void CancelListenNestMotorDriverStatusReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 机巢系统信息上报(需要初始化)
    virtual ErrorCode ListenNestSystemInfoReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestSystemInfoNotify>>& listener) = 0;
    virtual void CancelListenNestSystemInfoReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 机巢基站RTK信息上报
    virtual ErrorCode ListenNestSystemRtkReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestRtkStatusNotify>>& listener) = 0;
    virtual void CancelListenNestSystemRtkReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 机巢告警上报 DRONE_WARNING_NTFY MiscFunction::ListenDroneWarning
    //virtual ErrorCode ListenNestWarningReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestWarningNtfy>>& listener) = 0;
    //virtual void CancelListenNestWarningReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 机巢系统自检通知
    virtual ErrorCode ListenNestSystemSelfCheckReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<NestCheckStatusNtfy>>& listener) = 0;
    virtual void CancelListenNestSystemSelfCheckReport(uint32_t deviceId, ObjectId obejctId) = 0;

};

}
#endif // INEST_H
