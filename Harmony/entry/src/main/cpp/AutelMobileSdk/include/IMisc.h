#ifndef IMISC_H
#define IMISC_H

#include <memory>
#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "MiscDataType.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IMisc
{
public:
    // ==========参数查询、设置，执行操作类接口==========
    // 设置设备系统时间
    virtual ErrorCode SetSystemTime(uint32_t deviceId, const SystemTimeInfo& systemTimeInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取设备初始化参数
    virtual ErrorCode GetSystemInitData(uint32_t deviceId, std::shared_ptr<CompletionListener<SystemInfo>> listener, int retryCount = 0) = 0;

    // 获取设备组件版本信息
    virtual ErrorCode GetDeviceVerInfo(uint32_t deviceId, std::shared_ptr<CompletionListener<std::vector<DroneComponentVerInfo>>> listener, int retryCount = 0) = 0;

    // 设置LED灯开关
    virtual ErrorCode SetLedState(uint32_t deviceId, const DroneLedStatusInfo& droneLedStatusInfo, std::shared_ptr<ICompletionListener> listener, int retryCount = 0) = 0;

    // 查询所有LED灯状态
    virtual ErrorCode QueryLedStatus(uint32_t deviceId, std::shared_ptr<CompletionListener<DroneAllLedStatus>> listener, int retryCount = 0) = 0;

    // 通用灯语控制(机臂灯控制)
    virtual ErrorCode LampLanguageCommandCtrl(uint32_t deviceId, const LampLanguageCommand& lampLanguage,std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 执行通用校准指令
    virtual ErrorCode ExecCalibrationCommand(uint32_t deviceId, const CalibrationCommandInfo& calibrationCommandInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 设置国家代码
    virtual ErrorCode SetCountryCode(uint32_t deviceId, const std::string& countryCode, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 控制LED夜航灯开关
    virtual ErrorCode SetNightNavigationLedState(uint32_t deviceId, int32_t s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 清除禁飞区
    virtual ErrorCode CleanNoflyZone(uint32_t deviceId, const CleanNoFlyZoneType& cleanNoFlyZoneType, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==========消息监听类接口==========
    // 飞机运行时间统计消息上报
    virtual ErrorCode ListenDroneRuntimeReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<DroneRuntimeReport>>& listener) = 0;
    virtual void CancelListenDroneRuntimeReport(uint32_t deviceId, ObjectId obejctId)  = 0;

    // 遥控器定频上报(需要先开启遥控器定频上报)，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode ListenRCHardwareState(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<RCHardwareStateNtfy>>& listener) = 0;
    virtual void CancelListenRCHardwareState(uint32_t deviceId, ObjectId obejctId) = 0;

    // 遥控器按钮触发上报，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode ListenRCButtonState(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<HardwareButtonInfo>>& listener) = 0;
    virtual void CancelListenRCButtonState(uint32_t deviceId, ObjectId obejctId) = 0;

    // 遥控器状态上报，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode ListenRCState(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<RCStateNtfy>>& listener) = 0;
    virtual void CancelListenRCState(uint32_t deviceId, ObjectId obejctId) = 0;

    // 遥控器校准上报，此接口deviceId为本地摇控器的设备ID
    virtual ErrorCode ListenRCRockerCalibrationState(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<RockerCalibrationStateNtfy>>& listener) = 0;
    virtual void CancelListenRCRockerCalibrationState(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机通用参数(位置、状态等)上报（5HZ）
    virtual ErrorCode ListenDroneSystemStatusHFReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<DroneSystemStateHF>>& listener) = 0;
    virtual void CancelListenDroneSystemStatusHFReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机通用参数(电池电量等)上报（2HZ）
    virtual ErrorCode ListenDroneSystemStatusLFReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<DroneSystemStateLFNtfyInfo>>& listener) = 0;
    virtual void CancelListenDroneSystemStatusLFReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机工作状态信息上报
    virtual ErrorCode ListenDroneWorkStatusReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<FlightControlStatusInfo>>& listener) = 0;
    virtual void CancelListenDroneWorkStatusReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机告警上报
    virtual ErrorCode ListenDroneWarningMFReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<DroneWarningStateNtfy>>& listener) = 0;
    virtual void CancelListenDroneWarningMFReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 校准事件通知
    virtual ErrorCode ListenDroneCalibrationEventReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<CalibrationEventInfo>>& listener) = 0;
    virtual void CancelListenDroneCalibrationEventReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 校准进度通知
    virtual ErrorCode ListenDroneCalibrationScheduleReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<CalibrationScheduleInfo>>& listener) = 0;
    virtual void CancelListenDroneCalibrationScheduleReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机设备版本信息通知
    virtual ErrorCode ListenDroneVersionReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<std::vector<DroneComponentVerInfo>>>& listener) = 0;
    virtual void CancelListenDroneVersionReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机事件通知
    virtual ErrorCode ListenDroneEventReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<EventInfo>>& listener) = 0;
    virtual void CancelListenDroneEventReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 设备临时连接上报 飞机未连接时可以收到
    virtual ErrorCode ListenDroneTempConnectReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<DeviceTempConnectInfo>>& listener) = 0;
    virtual void CancelListenDroneTempConnectReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机GPS UTC时间同步上报
    virtual ErrorCode ListenDroneUtcTimeSyncReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<DroneUTCTimeSyncInfo>>& listener) = 0;
    virtual void CancelListenDroneUtcTimeSyncReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 摇控器频带信息通知
    virtual ErrorCode ListenRCBandInfoTypeReport(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<RCBandInfoTypeInfo>>& listener) = 0;
    virtual void CancelListenRCBandInfoTypeReport(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机告警通知
    virtual ErrorCode ListenDroneWarning(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<std::vector<WarningAtomMsg>>>& listener) = 0;
    virtual void CancelListenDroneWarning(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机实时告警通知
    virtual ErrorCode ListenDroneRuntimeWarning(uint32_t deviceId, ObjectId obejctId, const std::shared_ptr<KeyListener<WarningAtomMsg>>& listener) = 0;
    virtual void CancelListenDroneRuntimeWarning(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机北斗卫星信息上报
    virtual ErrorCode ListenDroneDbsInfoReport(uint32_t deviceId, ObjectId objectId, const std::shared_ptr<KeyListener<FcsBdsInfo>> & listerner) = 0;
    virtual void CancelListenDroneDbsInfoReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 飞机关键信息低频上报
    virtual ErrorCode ListenDroneKeyInfoLfReport(uint32_t deviceId, ObjectId objectId, const std::shared_ptr<KeyListener<DroneKeyInfoLFNtfy>> & listerner) = 0;
    virtual void CancelListenDroneKeyInfoLfReport(uint32_t deviceId, ObjectId objectId) = 0;
};
}

#endif // ICOMMON_H
