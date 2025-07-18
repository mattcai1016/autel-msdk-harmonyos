#ifndef NESTDATATYPE_H
#define NESTDATATYPE_H

#include <string>
#include <vector>
#include <cstdint>
#include "KeyValueBaseType.h"
#include "BaseType.h"
#include "Common.h"

namespace AutelMobileSdk
{


// 操作类型
enum class NestOperationType{
    Automatic = 1,   // 自动
    JogMode = 2,     // 点动
    Stop = 3         // 停止
};

// 舱门动作
enum class CabinAction{
    Open = 1,        // 开门
    Close = 2        // 关门
};

// 三轴动作
enum class RodAction {
    Tighten = 0,     // 收紧
    Release = 1      // 释放
};

// 充电动作
enum class ChargeAction {
    Start = 1,       // 充电开启
    Stop = 2         // 充电关闭
};

// 校准动作
enum class CalibrateAction {
    Start = 1,       // 校准开始
    Complete = 2     // 校准完成
};

// 无人机开关机动作
enum class DroneAction {
    PowerOn = 1,     // 开机
    PowerOff = 2     // 关机
};

// 空调开关动作
enum class ACAction {
    TurnOn = 1,      // 开启
    TurnOff = 2      // 关闭
};

// 急停控制动作
enum class EmergencyStopAction {
    Stop = 1,        // 急停
    Release = 2      // 急停解除
};

// 自动命令动作
enum class AutomaticAction {
    PrepareToFly = 1,    // 一键备飞
    PrepareToDescent = 2, // 一键备降
    Terminate = 3,        // 终止当前自动命令，并退出自动模式
    SelfCheck = 4         // 自检
};

// 备用电池开关动作
enum class BackupBatteryAction {
    TurnOn = 1,      // 开
    TurnOff = 2      // 关
};

// 机巢部件
enum class NestComponent {
    XRod = 1,           // x杆
    YRod = 2,           // y杆
    Cabin = 3,          // 舱门
    RightBackServo = 4, // 右后舵机
    RightFrontServo = 5,// 右前舵机
    LeftBackServo = 6,  // 左后舵机
    LeftFrontServo = 7  // 左前舵机
};

// 校准方向
enum class CalibrationDirection {
    Forward = 1,        // 正向校准
    Reverse = 2         // 反向校准
};

// 通用开关动作
enum class SwitchAction {
    TurnOn = 1,      // 开启
    TurnOff = 2      // 关闭
};

// 看门狗命令
enum class WatchDogCommand {
    Enable = 1,      // 开启看门狗
    Disable = 2,     // 关闭看门狗
    Feed = 3         // 喂狗
};

// 看门狗工作模式
enum class WatchDogMode {
    SingleTime = 1,  // 单次模式，超时后关闭看门狗(默认)
    Continuous = 2   // 连续模式，超时后不关闭看门狗
};

/**
 * @brief 机巢重置命令结构体
 * 用于外部重置控制
 */
struct AUTELSDK_API NestResetCommand {
    NestOperationType nestType;  // 通用指令
    std::string ToString() const;
};

// 舱门控制
struct AUTELSDK_API CabinCommand{
    NestOperationType nestType;
    CabinAction nestAction;
    std::string ToString() const;
};

// 三轴控制命令
struct AUTELSDK_API RodCommand{
    NestOperationType nestType;
    RodAction nestAction;
    std::string ToString() const;
};

// 充电控制命令
struct AUTELSDK_API ChargeCommand{
    NestOperationType nestType;
    ChargeAction nestAction;
    std::string ToString() const;
};

// 校准控制命令
struct AUTELSDK_API CalibrateCommand{
    NestOperationType nestType;
    CalibrateAction nestAction;
    std::string ToString() const;
};
// 无人机开关机控制命令
struct AUTELSDK_API DroneCommand{
    NestOperationType nestType;
    DroneAction nestAction;
    std::string ToString() const;
};
// 空调开关控制命令
struct AUTELSDK_API ACCommand{
    NestOperationType nestType;
    ACAction nestAction;
    std::string ToString() const;
};
// 急停控制命令
struct AUTELSDK_API EmergencyCommand{
    NestOperationType nestType;
    EmergencyStopAction nestAction;
    std::string ToString() const;
};

// 自动命令控制
struct AUTELSDK_API AutomaticCommand{
    NestOperationType nestType;
    AutomaticAction nestAction;
    std::string ToString() const;
};

// 备用电池开关控制命令
struct AUTELSDK_API BackupBatteryCommand{
    NestOperationType nestType;
    BackupBatteryAction nestAction;
    std::string ToString() const;
};

/**
 * @brief 机巢单项校准结构体
 * 用于控制特定机巢部件的校准
 */
struct AUTELSDK_API NestSingleCalibration {
    NestOperationType nestType;          // 通用指令
    NestComponent nestComponents;        // 机巢部件
    CalibrationDirection direction;      // 校准方向
    std::string ToString() const;
};

/**
 * @brief 机巢系统配置结构体
 * 用于设置机巢系统的各项参数
 */
struct AUTELSDK_API NestSystemConfig {
    NestOperationType nestType;      // 通用指令
    int32_t airOpenLimit;           // 空调自动开启阈值，单位℃
    int32_t airCloseLimit;          // 空调自动关闭阈值，单位℃
    int32_t unixTime;               // unix时间，小端格式
    int32_t autoDischarge;          // 自放电时间阈值（1~5小时）
    int32_t autoCharge;             // 自动补电电量阈值（50%~70%）

    // 参数有效性检查
    bool IsValid() const {
        return (autoDischarge >= 1 && autoDischarge <= 5) &&  // 自放电时间在1-5小时范围内
               (autoCharge >= 50 && autoCharge <= 70) &&      // 自动补电阈值在50%-70%范围内
               (airOpenLimit > airCloseLimit);                // 确保开启阈值大于关闭阈值
    }
    std::string ToString() const;
};

/**
 * @brief 补光灯开关控制结构体
 * 用于控制补光灯的开启和关闭
 */
struct AUTELSDK_API NestCommonSwitchMsg {
    SwitchAction command;     // 开关命令
    std::string ToString() const;
};

/**
 * @brief 收浆控制等待时间结构体
 * 用于设置收浆操作的等待时间
 */
struct AUTELSDK_API NestWaitTime {
    uint32_t waitTime;    // 等待时间
    std::string ToString() const;
};

/**
 * @brief 看门狗控制消息结构体
 * App发送指令进行喂狗及开关看门狗
 */
struct AUTELSDK_API NestWatchDogMsg {
    WatchDogCommand command;  // 看门狗控制命令
    uint32_t overtime;        // 超时时间，单位s
    WatchDogMode mode;        // 工作模式
    std::string ToString() const;
};

/**
 * @brief 飞机外部供电开关控制结构体
 * 用于控制飞机外部供电的开启和关闭
 */
struct AUTELSDK_API NestExternalPowerSwitchMsg {
    SwitchAction command;     // 开关命令
    std::string ToString() const;
};

/**
 *@brief 遥感控制
 */
struct AUTELSDK_API NestVirtualPoleStateMsg {
    int32_t leftHorizontalValue = 0;  //左摇杆水平方向值
    int32_t leftVerticalValue = 0;    //左摇杆竖直方向值
    int32_t rightHorizontalValue = 0; //右摇杆水平方向值
    int32_t rightVerticalValue = 0;   //右摇杆竖直方向值
    int32_t gimbalPitch; //云台pitch
    int32_t generalKey = 359; //按键 359：无效，625：停止任务，891：一键起飞降落，1157：返航，1423：悬停，1689：自定义
    int32_t combinedKey = 329; //组合按键 329:无效， 625：指南针校准

    std::string ToString() const;
};

/**
 * @brief 电源模块状态
 */
struct AUTELSDK_API PowerStatus {
    uint32_t err_code;      // 错误码
    uint32_t status;        // 状态
    std::string ToString() const;
};

/**
 * @brief 电池状态
 */
struct AUTELSDK_API BatteryStatus {
    uint32_t err_code;      // 错误码
    uint32_t pos_status;    // 位置状态
    uint32_t power_status;  // 电源状态
    uint32_t charge_status; // 充电状态
    std::string ToString() const;
};

/**
 * @brief 充电模块状态
 */
struct AUTELSDK_API ChargeStatus {
    uint32_t err_code;    // 错误码
    uint32_t status;      // 状态
    uint32_t ibus_limit;  // 输入电流限制
    uint32_t ibat_limit;  // 电池电流限制
    uint32_t vbus;        // 输入电压
    uint32_t vbat;        // 电池电压
    uint32_t ibus;        // 输入电流
    uint32_t ibat;        // 电池电流
    std::string ToString() const;
};

/**
 * @brief 备用电池状态
 */
struct AUTELSDK_API BatteryStandbyStatus {
    uint32_t err_code;    // 错误码
    std::string ToString() const;
};

/**
 * @brief 电机板状态
 */
struct AUTELSDK_API MotorStatus {
    uint32_t err_code;    // 错误码
    std::string ToString() const;
};

/**
 * @brief 温湿度状态
 */
struct AUTELSDK_API TemperatureStatus {
    uint32_t err_code;            // 错误码
    int32_t temperature;          // 温度
    uint32_t humidity;            // 湿度
    int32_t surface_temperature;  // 表面温度
    std::string ToString() const;
};

/**
 * @brief 气象站状态
 */
struct AUTELSDK_API AtmosStatus {
    uint32_t err_code;     // 错误码
    int32_t pressure;      // 压力
    uint32_t temperature;  // 温度
    uint32_t humidity;     // 湿度
    uint32_t wind_speed;   // 风速
    uint32_t wind_dir;     // 风向
    uint32_t rainfall;     // 降雨量
    std::string ToString() const;
};

/**
 * @brief 振动器状态
 */
struct AUTELSDK_API MpuStatus {
    uint32_t err_code;    // 错误码
    uint32_t alarm_flag;  // 告警标志
    std::string ToString() const;
};

/**
 * @brief 水浸传感器状态
 */
struct AUTELSDK_API WaterStatus {
    uint32_t err_code;    // 错误码
    uint32_t alarm_flag;  // 告警标志
    std::string ToString() const;
};

/**
 * @brief 半导体空调状态
 */
struct AUTELSDK_API TecStatus {
    int32_t err_code;           // 错误码
    uint32_t alert_code;        // 告警码
    uint32_t work_sta;          // 工作状态
    uint32_t ifan_sta;          // 内风扇状态
    uint32_t efan_sta;          // 外风扇状态
    uint32_t cmp_sta;           // 压缩机状态
    int32_t iw_temp;            // 内部温度
    uint32_t pump_sta;          // 水泵状态
    uint32_t ext_temp;          // 外部温度
    int32_t cds_temp;           // 冷凝器温度
    int32_t evat_temp;          // 蒸发器温度
    uint32_t ifan_rpm;          // 内风扇转速
    uint32_t efan_rpm;          // 外风扇转速
    uint32_t ac_in_vol;         // 交流输入电压
    uint32_t dc_in_vol;         // 直流输入电压
    uint32_t ac_current;        // 交流电流
    uint32_t dev_runtime;       // 设备运行时间
    uint32_t cmp_runtime;       // 压缩机运行时间
    uint32_t ifan_runtime;      // 内风扇运行时间
    uint32_t cmp_run_cnt;       // 压缩机运行次数
    uint32_t dc_current;        // 直流电流
    uint32_t dc_watt;           // 直流功率
    uint32_t ac_watt;           // 交流功率
    uint32_t srfgrt_cap;        // 制冷能力
    int32_t tec1_base_current;  // TEC1基准电流
    int32_t tec1_current;       // TEC1电流
    int32_t tec2_base_current;  // TEC2基准电流
    int32_t tec2_current;       // TEC2电流
    uint32_t duty;              // 占空比
    std::string ToString() const;
};

/**
 * @brief 指示灯状态
 */
struct AUTELSDK_API LedStatus {
    uint32_t land_led;    // 降落指示灯
    std::string ToString() const;
};

/**
 * @brief 系统模式信息
 */
struct AUTELSDK_API SystemMode {
    uint32_t auto_mode;   // 自动模式
    uint32_t chg_mode;    // 充电模式
    std::string ToString() const;
};

/**
 * @brief 风扇状态
 */
struct AUTELSDK_API FanStatus {
    uint32_t error_code;           // 错误码
    uint32_t fan1234_rpm_percent;  // 风扇1-4转速百分比
    uint32_t fan56_rpm_percent;    // 风扇5-6转速百分比
    uint32_t fan78_rpm_percent;    // 风扇7-8转速百分比
    std::vector<uint32_t> rpm;     // 各风扇转速
    std::string ToString() const;
};

/**
 * @brief 机巢状态通知
 */
struct AUTELSDK_API NestStatusNtfy {
    PowerStatus power;                 // 电源模块状态
    BatteryStatus uav;                 // 无人机状态
    ChargeStatus chg0;                 // 充电模块0状态
    ChargeStatus chg1;                 // 充电模块1状态
    BatteryStandbyStatus bat_stby;     // 备用电池状态
    MotorStatus motor;                 // 电机板状态
    TemperatureStatus temp0;           // 温湿度0状态
    TemperatureStatus temp1;           // 温湿度1状态
    AtmosStatus atmos;                 // 气象站状态
    MpuStatus mpu;                     // 振动器状态
    WaterStatus water;                 // 水浸传感器状态
    TecStatus tec;                     // 半导体空调状态
    LedStatus led;                     // 指示灯状态
    SystemMode sys_mode;               // 系统模式信息
    FanStatus fan_status;              // 风扇状态
    std::string ToString() const;
};

/**
 * @brief 机巢电池状态通知结构体
 * 用于上报电池的详细状态信息
 */
struct AUTELSDK_API NestBatteryStatusNtfy {
    uint32_t status;          // 通讯状态
    uint32_t safe_status;     // 安全状态信息
    uint32_t voltage;         // 当前总电压，单位mV
    uint32_t current;         // 当前总电流，单位mA
    uint32_t remain_cap;      // 电池剩余容量，单位mAh
    uint32_t full_cap;        // 电池满充容量，单位mAh
    int32_t temperature;      // 电池温度，单位0.1摄氏度
    std::vector<uint32_t> cell_vol;  // 电芯电压
    uint32_t rsoc;           // 剩余电量百分比，范围0-100
    uint32_t cell_num;       // 电芯数目
    uint32_t remain_time;    // 剩余充电时间
    std::string ToString() const;
};

/**
 * @brief 机巢备用电池状态通知结构体
 * 用于上报备用电池的详细状态信息
 */
struct AUTELSDK_API NestBackupBatteryStatusNtfy {
    uint32_t voltage;         // 当前总电压，单位mV
    int32_t current;          // 当前总电流，单位mA
    uint32_t remain_cap;      // 电池剩余容量，单位mAh
    uint32_t rsoc;           // 剩余电量百分比，范围0-100
    uint32_t cell_num;       // 电芯数目
    uint32_t design_cap;     // 电池设计容量
    uint32_t cycle_cnt;      // 循环次数
    uint32_t manus_date;     // 生产日期
    uint32_t balance_sta_l;  // 平衡状态低位
    uint32_t balance_sta_h;  // 平衡状态高位
    uint32_t protect_sta;    // 保护状态
    uint32_t soft_ver;       // 软件版本
    uint32_t fet_sta;        // FET状态
    uint32_t ntc_num;        // NTC数量
    std::vector<uint32_t> temperature;      // 温度数组
    std::vector<uint32_t> bat_cell_voltage; // 电芯电压数组
    std::string ToString() const;
};

/**
 * @brief 机巢电机驱动状态通知结构体
 * 用于上报舱门和三轴电机的状态信息
 */
struct AUTELSDK_API NestMotorDriverStateNtfy {
    uint32_t door_status;            // 舱门状态
    uint32_t door_angle;             // 舱门角度
    uint32_t door_limit_sw_status;   // 舱门限位开关状态
    uint32_t xbar_status;            // X轴状态
    uint32_t xbar_angle;             // X轴角度
    uint32_t xbar_limit_sw_status;   // X轴限位开关状态
    uint32_t ybar_status;            // Y轴状态
    uint32_t ybar_angle;             // Y轴角度
    uint32_t ybar_limit_sw_status;   // Y轴限位开关状态
    uint32_t zbar_status;            // Z轴状态
    uint32_t zbar_angle;             // Z轴角度
    uint32_t zbar_limit_sw_status;   // Z轴限位开关状态
    std::string ToString() const;
};

/**
 * @brief 机巢系统信息通知结构体
 * 用于上报机巢系统的工作状态和资源使用情况
 */
struct AUTELSDK_API NestSystemInfoNotify {
    uint32_t work_status1;   // 工作状态1
    uint32_t work_status2;   // 工作状态2
    uint32_t device_type;    // 设备类型
    uint32_t work_mode;      // 工作模式
    uint32_t cpu_usage;      // CPU使用率
    uint32_t mem_usage;      // 内存使用率
    uint32_t cpu_temp;       // CPU温度
    std::string ToString() const;
};

/**
 * @brief 机巢RTK状态通知结构体
 * 用于上报RTK定位系统的状态和坐标信息
 */
struct AUTELSDK_API NestRtkStatusNotify {
    uint32_t fixStatus;      // fix状态
    double latitude;         // 经度
    double longitude;        // 纬度
    double altitude;         // 高度
    double setLatitude;      // 设定经度
    double setLongitude;     // 设定纬度
    double setAltitude;      // 设定高度
    uint32_t workMode;       // 工作模式: 
                            // 0.自定位模式
                            // 1.设定坐标模式(参数经度、纬度、高度)
                            // 2.移动模式
                            // 3.流动站模式
    bool rtcmIsValid;        // RTCM解析状态-数据是否有效
    bool rtcmSwitch;         // RTCM开关
    bool rtkDebug;           // 是否开启调试
    std::string ToString() const;
};

/**
 * @brief 机巢自检状态通知结构体
 * 用于上报机巢各部件的自检结果
 */
struct AUTELSDK_API NestCheckStatusNtfy {
    uint32_t nest_result;    // 机巢部件自检结果
    uint32_t fan_result;     // 风扇自检结果
    uint32_t self_check;     // 自检标识: 
                            // 0 - 未开始
                            // 1 - 自检中
                            // 2 - 自检完成
    std::string ToString() const;
};


/**
 * @brief 机巢状态信息通知结构体
 * 用于向无人机通知机巢的状态信息
 */
struct AUTELSDK_API NestStatusInfoNotifyToDroneMsg {
    bool fineDropReady;   // 机巢是否就绪精降状态
    std::string ToString() const;
};


}; // namespace AutelMobileSdk

#endif // NESTDATATYPE_H
