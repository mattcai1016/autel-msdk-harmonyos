#ifndef COMMON_KEY_DATA_TYPE_H
#define COMMON_KEY_DATA_TYPE_H

#include <string>
#include <vector>
#include <cstdint>
#include "KeyValueBaseType.h"
#include "BaseType.h"
#include "Common.h"

namespace AutelMobileSdk
{
struct AUTELSDK_API SystemInfo
{
    std::string mainControlVersion;
    std::string droneSn;
    int droneType = 0;
    int activeState = 0;
    DroneFlightMode flightMode = DroneFlightMode::Unknown;
    FlightControlMainMode droneMainMode = FlightControlMainMode::Unknown;
    DroneWorkMode droneWorkMode = DroneWorkMode::Unknown;
    DroneWorkState droneWorkState = DroneWorkState::Unknown;

    std::string ToString() const;
};

struct AUTELSDK_API SystemTimeInfo
{
    uint64_t utcTimeInterval = 0;  // UTC时间戳
    float timeZone = 0;            // 相对零时区的偏移小时数，比如北京：UTC+8，timeZone就是8

    SystemTimeInfo() : utcTimeInterval(0), timeZone(0.0) {};
    SystemTimeInfo(uint64_t utcTimeIntervalInMilliseconds, float currentTimeZone) : utcTimeInterval(utcTimeIntervalInMilliseconds), timeZone(currentTimeZone) {}

    std::string ToString() const;
};

struct AUTELSDK_API DroneComponentVerInfo
{
    DroneComponentId componentID = DroneComponentId::REMOTE_CONTROL;
    std::string componentSN;
    std::string hardwareVersion;
    std::string softwareVersion;
    int componentModel = 0; //整型枚举值,组件设备型号
    std::string strComponentModel;//字符型组件设备型号，（例如：相机设备型号XM802）
    std::string label;//飞机能力集预留字段，描述当前组件的信息（例如：前相机，后相机)
    DroneComponent componentType = DroneComponent::UNKNOWN; //描述当前组件类型（例如：相机，云台，飞控）
    std::string bootloaderVersion; //mcu的bootloader版本信息

    //重载==
    bool operator ==(const DroneComponentVerInfo& other) const
    {
        return componentID == other.componentID
               && componentSN == other.componentSN
               && hardwareVersion == other.hardwareVersion
               && softwareVersion == other.softwareVersion
               && componentModel == other.componentModel
               && strComponentModel == other.strComponentModel
               && label == other.label
               && componentType == other.componentType
               && bootloaderVersion == other.bootloaderVersion;
    }

    std::string ToString() const;
};

struct AUTELSDK_API DroneAttitude
{
    float pitch = 0; //俯仰角
    float roll = 0;  //横滚角
    float yaw = 0;   //偏航角

    //重载==
    bool operator ==(const DroneAttitude& other) const
    {
        return pitch == other.pitch && roll == other.roll && yaw == other.yaw;
    }

    std::string ToString() const;
};
//飞机通用参数上报（5HZ）
struct AUTELSDK_API DroneSystemStateHF
{
    double droneLatitude = 0;    // 飞机纬度, 当它是个无效值或isGpsOpen为NO，说明无法定位位置，应当忽略
    double droneLongitude = 0;   // 飞经度, 当它是个无效值或isGpsOpen为NO，说明无法定位位置，应当忽略
    float altitude = 0;          // 飞机相对高度
    float altitudeMSL = 0;       // 飞机海拔高度
    float velocityX = 0;         // x速度
    float velocityY = 0;         // y速度
    float velocityZ = 0;         // z速度
    DroneAttitude droneAttitude; // 飞行器姿态(弧度值)
    DroneAttitude gimbalAttitude;// 云台姿态（弧度值）
    float distance = 0;          // 飞机与 Home 点之间的距离
    float ultrasoundAltitude = 0;// 超声对地高度
    int laserDistance = 0;       // 激光测距距离，单位cm
    bool laserDistanceIsValid = 0;// 表示激光测距距离是否有效,0无效，1有效
    double radarHight = 0;       // 雷达高度检测结果
    DroneFlightMode flightMode = DroneFlightMode::Unknown;// 飞行模式，当前飞机飞行状态
    FlightControlMainMode mainMode = FlightControlMainMode::Unknown;// 飞控主模式
    DroneWorkMode droneWorkMode = DroneWorkMode::Unknown;// 飞机工作模式
    DroneWorkState droneWorkStatus = DroneWorkState::Unknown;// 飞机工作状态
    TrackWorkState trackWorkStatus = TrackWorkState::CHECK_STATUS;// 跟踪工作状态
    bool isGpsOpen = false;// GPS开关状态
    AiServiceStatus aiEnableFunc = AiServiceStatus::UNKNOWN;// AiService生效的功能
    RetractPaddleStatus retractPaddleStatus = RetractPaddleStatus::NONE; //收桨状态

    //重载==
    bool operator ==(const DroneSystemStateHF& other) const
    {
        return droneLatitude == other.droneLatitude
               && droneLongitude == other.droneLongitude
               && altitude == other.altitude
               && altitudeMSL == other.altitudeMSL
               && velocityX == other.velocityX
               && velocityY == other.velocityY
               && velocityZ == other.velocityZ
               && droneAttitude == other.droneAttitude
               && gimbalAttitude == other.gimbalAttitude
               && distance == other.distance
               && ultrasoundAltitude == other.ultrasoundAltitude
               && laserDistance == other.laserDistance
               && laserDistanceIsValid == other.laserDistanceIsValid
               && radarHight == other.radarHight
               && flightMode == other.flightMode
               && mainMode == other.mainMode
               && droneWorkMode == other.droneWorkMode
               && droneWorkStatus == other.droneWorkStatus
               && trackWorkStatus == other.trackWorkStatus
               && isGpsOpen == other.isGpsOpen
               && aiEnableFunc == other.aiEnableFunc
               && retractPaddleStatus == other.retractPaddleStatus;
    }

    std::string ToString() const;
};
//飞机通用参数上报（2HZ）
struct AUTELSDK_API DroneSystemStateLFNtfyInfo
{
    float remainingFlightTime = 0; //剩余飞行时间，单位：s
    int batteryRemainingPower = 0; //电池剩余电量
    float batteryPercentage = 0; //电池电量百分比
    float batteryTemperature = 0; //电池温度
    float batteryVoltage = 0; //电池当前电压
    float batteryCurrent = 0; //电池当前电流
    int satelliteCount = 0; //可见卫星数
    GPSLevel gpsLevel = GPSLevel::LEVEL_NONE; // GPS信号等级
    int remoteIdStatus = 1; // remoteID工作状态，1:开启，2:关闭
    double slamConfidence = 0;      // 当前视觉SLAM置信度,视觉定位强弱 0.7以上高，0.4到0.7中，0.4以下低
    int gpsStrengthPercentage = 0;  // 当前GPS强度百分比 建议：40%以下为弱,80%以下为中，大于80%强

    //重载==
    bool operator ==(const DroneSystemStateLFNtfyInfo& other) const
    {
        return remainingFlightTime == other.remainingFlightTime
               && batteryRemainingPower == other.batteryRemainingPower
               && batteryPercentage == other.batteryPercentage
               && batteryTemperature == other.batteryTemperature
               && batteryVoltage == other.batteryVoltage
               && batteryCurrent == other.batteryCurrent
               && satelliteCount == other.satelliteCount
               && gpsLevel == other.gpsLevel
               && remoteIdStatus == other.remoteIdStatus
               && slamConfidence == other.slamConfidence
               && gpsStrengthPercentage == other.gpsStrengthPercentage;
    }

    std::string ToString() const;
};

struct AUTELSDK_API FlightControlStatusInfo   // （飞机工作状态信息上报）
{
    int droneType = 0;//飞机类型
    GearLevel droneGear = GearLevel::UNKNOWN; //飞机档位
    bool supportRTK = true; //是否支持RTK
    bool isHomeInvalid = true;//home点是否无效
    double homeLatitude = 0;   // Home点纬度(degrees * 1E7), 如果飞行器返航点无效，则 isHomeInvalid 属性为YES
    double homeLongitude = 0;  // Home点经度(degrees * 1E7), 如果飞行器返航点无效，则 isHomeInvalid 属性为YES
    bool obstacleAvoidanceEnabled = true;//避障使能
    bool radarChartDispalyed = true;//雷达图显示
    int visionledStatus = 0;//下视补光灯状态
    bool visionEnableSecureLanding = true;//降落保护开关
    bool visionEnablePreciseLanding = true;//是否启用精准降落功能
    CompassCalibrationStatus compassCalibrationStatus = CompassCalibrationStatus::UNKNOWN;//指南针校准状态
    IMUCalibrationStep imuCalibrationStatus = IMUCalibrationStep::UNKNOWN;//IMU校准状态
    int numberOfDischarge = 0;//电池放电次数 仅单电池使用
    int batteryNotInPlaceFlag = 0;//电池不在位标志  0=在位  1=不在位
    Environment environmentInfo = Environment::LOW_BRIGHTNESS;//当前飞机环境亮度信息
    bool isBackupHomeValid = true;//备降点是否有效，true:备降点有效  false:备降点无效
    double backupHomeLatitude = 0;//备降点纬度，如果飞行器返航失败，且备降点有效，且达到低电量时会自动降落到备降点
    double backupHomeLongitude = 0;//备降点经度
    double backupHomeAlt = 0;//备降点高度
    int preflightCheckResult = 0; //飞行检查结果(0=检查通过可以飞行 1=其它原因检查不通过 2=任务管理模块检查不通过 3=路径规划模块检查不通过)
    int preflightCheckResultGsc = 0;  //电网飞前检查结果(0=正常 其它值异常)
    int armLampStatus;   //机臂灯状态
    SwarmManagerStatus swarmMissionStatus = SwarmManagerStatus::WAIT_INIT; //蜂群任务状态 (参见 SwarmManagerStatus)

    //重载==
    bool operator ==(const FlightControlStatusInfo& other) const
    {
        return droneType == other.droneType
               && droneGear == other.droneGear
               && supportRTK == other.supportRTK
               && isHomeInvalid == other.isHomeInvalid
               && homeLatitude == other.homeLatitude
               && homeLongitude == other.homeLongitude
               && obstacleAvoidanceEnabled == other.obstacleAvoidanceEnabled
               && radarChartDispalyed == other.radarChartDispalyed
               && visionledStatus == other.visionledStatus
               && visionEnableSecureLanding == other.visionEnableSecureLanding
               && visionEnablePreciseLanding == other.visionEnablePreciseLanding
               && compassCalibrationStatus == other.compassCalibrationStatus
               && imuCalibrationStatus == other.imuCalibrationStatus
               && numberOfDischarge == other.numberOfDischarge
               && batteryNotInPlaceFlag == other.batteryNotInPlaceFlag
               && environmentInfo == other.environmentInfo
               && isBackupHomeValid == other.isBackupHomeValid
               && backupHomeLatitude == other.backupHomeLatitude
               && backupHomeLongitude == other.backupHomeLongitude
               && backupHomeAlt == other.backupHomeAlt
               && preflightCheckResult == other.preflightCheckResult
               && preflightCheckResultGsc == other.preflightCheckResultGsc
               && armLampStatus == other.armLampStatus
               && swarmMissionStatus == other.swarmMissionStatus;
    }


    std::string ToString() const;
};
//飞机告警上报
struct AUTELSDK_API DroneWarningStateNtfy
{
    BatteryPowerWarning lowPowerWarning = BatteryPowerWarning::LOW;//低电量告警
    bool isBatteryOverheated = true;   // 电池是否过热
    bool isBatteryLowTemperature = true;//电池温度是否过低。
    bool isBatteryVoltageDiff = true;//电池电芯电压不平衡
    FlightControlTurnOnMotorStatus turnOnMotorError = FlightControlTurnOnMotorStatus::REDZONE;//电机无法正常启动告警状态
    bool isIMUOverheated = true;//IMU过热
    bool isStickLimited = true;//杆量受限
    bool highWindWarning = true;//大风告警
    bool isHomePointNotAccurate = true;//返航点可能不准
    bool overloadWarning = true;//过载告警
    IMUCalibratoionWarning imuCalibrationWarn = IMUCalibratoionWarning::BEGIN;//IMU校准告警
    MainControllerNoflyZoneStatus noFlyStatus = MainControllerNoflyZoneStatus::INSIDE;//禁飞区告警状态
    CompassInterferenceLevel compassInterferenceLevel = CompassInterferenceLevel::LEVEL0;//指南针受干扰等级
    bool isReachMaxRange = true;//是否达到最大飞行范围
    bool isNearMaxRange = true;//是否即将达到最大飞行范围
    bool isReachMaxHeight = true;//是否达到最大飞行高度
    bool isGPSValid = true;         // GPS信号是否可用
    bool isCompassValid = true;     // 指南针有效
    bool visionLimitedWhenDark = true;
    bool insufficientSpaceToPass = true;//空间不足，无法通过
    bool flyToOpenSpace = true;//将飞行器移到空旷区域后重试
    int visionErrorCode = 0;//所有视觉错误，比如：视觉传感器是否可用。

    //重载==
    bool operator ==(const DroneWarningStateNtfy& other) const
    {
        return lowPowerWarning == other.lowPowerWarning
               && isBatteryOverheated == other.isBatteryOverheated
               && isBatteryLowTemperature == other.isBatteryLowTemperature
               && isBatteryVoltageDiff == other.isBatteryVoltageDiff
               && turnOnMotorError == other.turnOnMotorError
               && isIMUOverheated == other.isIMUOverheated
               && isStickLimited == other.isStickLimited
               && highWindWarning == other.highWindWarning
               && isHomePointNotAccurate == other.isHomePointNotAccurate
               && overloadWarning == other.overloadWarning
               && imuCalibrationWarn == other.imuCalibrationWarn
               && noFlyStatus == other.noFlyStatus
               && compassInterferenceLevel == other.compassInterferenceLevel
               && isReachMaxRange == other.isReachMaxRange
               && isNearMaxRange == other.isNearMaxRange
               && isReachMaxHeight == other.isReachMaxHeight
               && isGPSValid == other.isGPSValid
               && isCompassValid == other.isCompassValid
               && visionLimitedWhenDark == other.visionLimitedWhenDark
               && insufficientSpaceToPass == other.insufficientSpaceToPass
               && flyToOpenSpace == other.flyToOpenSpace
               && visionErrorCode == other.visionErrorCode;
    }

    std::string ToString() const;
};

struct AUTELSDK_API RCHardwareStateNtfy
{
    int leftHorizontalValue = 0;//左摇杆水平方向值
    int leftVerticalValue = 0;//左摇杆竖直方向值
    int rightHorizontalValue = 0;//右摇杆水平方向值
    int rightVerticalValue = 0;//右摇杆竖直方向值
    int wheelValue1 = 0;//左滚轮值（云台pitch）
    int wheelValue2 = 0;//右滚轮值（云台yaw）
    RcFlightMode flightMode = RcFlightMode::UNKNOWN;//飞行模式
    RCButtonType buttonType = RCButtonType::UNKNOWN;
    int combinedButtonType = 0;//组合按键

    //重载==
    bool operator ==(const RCHardwareStateNtfy& other) const
    {
        return leftHorizontalValue == other.leftHorizontalValue
               && leftVerticalValue == other.leftVerticalValue
               && rightHorizontalValue == other.rightHorizontalValue
               && rightVerticalValue == other.rightVerticalValue
               && wheelValue1 == other.wheelValue1
               && wheelValue2 == other.wheelValue2
               && flightMode == other.flightMode
               && buttonType == other.buttonType
               && combinedButtonType == other.combinedButtonType;
    }

    std::string ToString() const;
};

struct AUTELSDK_API DroneRuntimeReport
{
    uint64_t timestamp; //时间戳 ns
    uint32_t totalFactoryTime;  //飞机从生产以来的飞行累计总时长
    uint32_t totalStartupTime;  //飞机本次开机的飞行累计时长
    uint32_t totalArmedTime;  //飞机本次打桨的飞行累计时长

    std::string ToString() const;
};

struct AUTELSDK_API HardwareButtonInfo
{
    RCButtonType buttonType = RCButtonType::UNKNOWN;
    RcButtonState clickType = RcButtonState::UNKNOWN;
    int thumbWheelValue = 0;

    std::string ToString() const;
};
//遥控器状态上报
struct AUTELSDK_API RCStateNtfy
{
    int rcSignalQuality = 0;//遥控器信号强度,[0-100]
    int dspSignalQuality = 0;//图传信号强度,[0-100]
    int remainPowerPercent = 0;//剩余电量百分比,[0-100]
    int calibrationState = 0;//遥控器校准状态（未用，填0）
    int batteryTemperature = 0;//遥控器电池温度，单位：摄氏度（未用，填0）
    int chargingVoltage = 0;//遥控器充电输入电压，单位：mV。(带屏遥控无)
    int isDroneNestMode = 0;//是否为机巢模式 0：否，1：在机巢模式(带屏遥控无)

    //重载==
    bool operator ==(const RCStateNtfy& other) const
    {
        return rcSignalQuality == other.rcSignalQuality
               && dspSignalQuality == other.dspSignalQuality
               && remainPowerPercent == other.remainPowerPercent
               && calibrationState == other.calibrationState
               && batteryTemperature == other.batteryTemperature
               && chargingVoltage == other.chargingVoltage
               && isDroneNestMode == other.isDroneNestMode;
    }

    std::string ToString() const;
};
//摇杆校准状态上报
struct AUTELSDK_API RockerCalibrationStateNtfy
{
    int rightStickStatus = 0;//右摇杆校准状态信息
    int leftStickStatus = 0;//左摇杆校准状态信息
    int rightThumbWheelStatus = 0;//右拨轮校准状态信息
    int leftThumbWheelStatus = 0;//左拨轮校准状态信息
    int midValibFlag = 0;// 1：中位有效。0：摇杆或拨轮不居中

    //重载==
    bool operator ==(const RockerCalibrationStateNtfy& other) const
    {
        return rightStickStatus == other.rightStickStatus
               && leftStickStatus == other.leftStickStatus
               && rightThumbWheelStatus == other.rightThumbWheelStatus
               && leftThumbWheelStatus == other.leftThumbWheelStatus
               && midValibFlag == other.midValibFlag;
    }

    std::string ToString() const;
};

struct AUTELSDK_API DroneLedStatusInfo
{
    DroneLedType ledType = DroneLedType::NONE;
    DroneLedStatus ledStatus = DroneLedStatus::UNKNOWN;

    std::string ToString() const;
};

struct AUTELSDK_API DroneAllLedStatus
{
    bool nightLedStatus = true;
    std::vector<DroneLedStatusInfo> ledsStatus;

    std::string ToString() const;
};

struct AUTELSDK_API CalibrationCommandInfo
{
    CalibrationType type = CalibrationType::UNKNOWN;
    Cmd cmd;

    std::string ToString() const;
};

struct AUTELSDK_API CalibrationEventInfo
{
    CalibrationType calibrationType;
    CalibrationEvent calibrationEvent;

    bool operator == (const CalibrationEventInfo& other) const
    {
        return calibrationEvent == other.calibrationEvent && calibrationType == other.calibrationType;
    }

    std::string ToString() const;
};

struct AUTELSDK_API CalibrationScheduleInfo
{
    ImuCalibrationStep imcStep = ImuCalibrationStep::STEP0;
    CompassCalibrationStep compassStep = CompassCalibrationStep::STEP0;
    int calibrationPercent = 0;
    CalibrationType calibrationType = CalibrationType::UNKNOWN;

    bool operator==(const CalibrationScheduleInfo& other) const
    {
        return imcStep == other.imcStep
                   && compassStep == other.compassStep
                   && calibrationPercent == other.calibrationPercent
                   && calibrationType == other.calibrationType;
    }

    std::string ToString() const;
};
//飞机事件通知
struct AUTELSDK_API EventInfo
{
    DroneComponent componentType = DroneComponent::UNKNOWN;//组件类型
    DroneComponentId componentId = DroneComponentId::ATSERVICE_RC;//组件ID
    EventPriority priority = EventPriority::UNKNOWN;//事件等级
    DroneEvent eventId = DroneEvent::UNKNOWN;//事件ID
    uint32_t eventReason = 0; //事件原因

    //重载==
    bool operator ==(const EventInfo& other) const
    {
        return componentType == other.componentType
               && componentId == other.componentId
               && priority == other.priority
               && eventId == other.eventId
               && eventReason == other.eventReason;
    }

    std::string ToString() const;
};

struct AUTELSDK_API DeviceTempConnectInfo
{
    std::string droneSn;
    float droneBatteryPercentage = 0;
    bool isMatched = true;
    std::string droneName;

    std::string ToString() const;
};

struct AUTELSDK_API DroneUTCTimeSyncInfo
{
    uint64_t gpsTime = 0;

    std::string ToString() const;
};

struct AUTELSDK_API LampLanguageCommand
{
    LampLanguageCommandType type = LampLanguageCommandType::LampLanguageCommandUnknow;
    uint32_t cmd = 0; // LamplngGetLogCmd、LamplngUpgradeServiceCmd、LamplngDirectCtrl

    std::string ToString() const;
};

struct AUTELSDK_API RCBandInfoTypeInfo
{
    std::string bandMode;
    std::string bandWidth;
    int district = 0;
    int disableSetBandMode = 0;
    int RCType = 0;
    int modemMode = 0;
    int fccModel = 0;

    std::string ToString() const;
};

struct AUTELSDK_API WarningAtomMsg
{
    DroneComponent componentType = DroneComponent::UNKNOWN;
    DroneComponentId componentId = DroneComponentId::ATSERVICE_RC;
    WaringId warningId;

    //重载==
    bool operator ==(const WarningAtomMsg& other) const
    {
        return componentType == other.componentType
               && componentId == other.componentId
               && warningId == other.warningId;
    }

    std::string ToString() const;
};

struct AUTELSDK_API FcsBdsInfo
{
    uint32_t satBdsB1; // 通道1 捜星数
    uint32_t satBdsB2; // 通道2 捜星数
    uint32_t satBdsB3; // 通道3 捜星数

    std::string ToString() const;
};

struct AUTELSDK_API DroneKeyInfoLFNtfy
{
    uint64_t  timestamp;          // 时间戳 系统boot
    uint32_t  gpsTime;          // GPS时间戳(秒)
    double  gpsLat;           // GPS纬度(度)
    double  gpsLon;           // GPS经度(度)
    float   gpsAlt;          // GPS海拔高度（米）
    float   velNedX;         // x在NED坐标系中的速度，单位为m/s
    float   velNedY;         // y在NED坐标系中的速度，单位为m/s
    float   velNedZ;         // z在NED坐标系中的速度，单位为m/s
    float   accuracyH;        // 水平精度, 以米为单位
    float   accuracyV;        // 垂直精度, 以米为单位
    float   accuracyS;        // 速度精度, 以米为单位
    double  hmsl;              // 椭球面的高度
    uint32_t  gnssFixType;     // GNSS fix 类型 0: no fix 1: dead reckoning only 2: 2D fix 3: 3D fix 4: GNSS + Dead Reckoning 5: Time only Fix
    uint32_t satellitesNum;    // number of satellites used
    uint32_t  gpsQuality;       // GPS质量等级(0~100)
    double  xacc;              // X 加速度 (m/s^2)
    double  yacc;              // Y 加速度 (m/s^2)
    double  zacc;              // Z 加速度 (m/s^2)
    double  xgyro;             // 绕 X 轴的角速度 (rad / sec)
    double  ygyro;             // 绕 Y 轴的角速度 (rad / sec)
    double  zgyro;             // 绕 Z 轴的角速度 (rad / sec)
    double  xacc1;            // X 加速度 (m/s^2)备
    double  yacc1;            // Y 加速度 (m/s^2)备
    double  zacc1;            // Z 加速度 (m/s^2)备
    double  xgyro1;           // 绕 X 轴的角速度1 (rad / sec)备
    double  ygyro1;            // 绕 Y 轴的角速度1 (rad / sec)备
    double  zgyro1;            // 绕 Z 轴的角速度1 (rad / sec)备
    double  xmag;              // X 磁场 (Gauss)
    double  ymag;              // Y 磁场 (Gauss)
    double  zmag;              // Z 磁场 (Gauss)
    double  xmag1;            // X 磁场1 (Gauss)备
    double  ymag1;            // Y 磁场1 (Gauss)备
    double  zmag1;            // Z 磁场1 (Gauss)备
    double  absPressure;      // 绝对压强 (millibar)
    double  temperature;       // 温度(摄氏度)
    double  absPressure1;    // 绝对压强1 (millibar)备
    double  temperature1;     // 温度1(摄氏度)备
    uint32_t  fieldsUpdated;         // 自上次消息以来已更新的字段的位掩码, bit 0 = xacc, bit 12: temperature
    uint32_t  smartMode;        // 飞机智能模式，drone_work_mode
    uint32_t  smartModeStatus;         // 智能模式工作状态 drone_work_status
    uint32_t  batteryStatus;         // 电池状态 see battery_status
    uint32_t  unlockValid;         // 当前是否允许飞控解锁 0: 不允许 1: 允许
    //GPS开关信息
    int32_t  isGpsInterfaceOpen;         // GPS开关状态（0：GPS关闭 1：GPS打开）
    //遥控器按键信息
    int32_t  button;         // 遥控按钮命令, 625 : arm button 1157: go home button 1423: Pause_Button 891: Takeoff Landing button
    uint32_t  alarmStatus1;         // 系统告警状态1
    uint32_t  alarmStatus2;         // 系统告警状态2
    uint32_t  type;         // MAV类型
    uint32_t  flightMode;         // 飞行模型
    uint32_t  errorCode1;         // 飞控心跳错误码
    uint32_t  uavSta1;         // 飞控心跳plus 系统告警状态1
    uint32_t  uavSta2;         // 飞控心跳plus 系统告警状态2
    uint32_t  uavSta3;         // 飞控心跳plus 系统告警状态3
    std::vector<uint32_t> dataU32;         // data_u32[1],0-5 前向最大速度,6-11 后向最大速度,12-16 左右最大速度, 17-20 上升最大速度,21-24 下降最大速度,25-31 偏航角
    std::vector<uint32_t> dataU8;
    uint32_t  safeStatus;         // 电池安全状况 仅单电池使用 多电池复用DroneSystemStateLFNtfy batteryInfo字段
    uint32_t  maxerror;         // 电池错误状态信息 仅单电池使用 多电池复用DroneSystemStateLFNtfy batteryInfo字段
    uint32_t  droneGear;         // 飞机档位
    bool    supportRtk;         // 是否支持RTK
    bool    isHomeInvalid;         // home点是否无效
    uint32_t  lowPowerWarning;         // 低电量告警
    uint32_t  noFlyStatus;         // 禁飞区告警状态
    float   airspeedPressure;         // air speed Pressure
    float   aglMeas;         // Above Ground Level (AGL) measurement, m
    uint32_t  aglInfo;         // Above Ground Level (AGL) source and validity; 0-not valid; 1-Sonar; 2-Downward Radar
    uint32_t  alarmStatus3;         // 系统告警状态1
    uint32_t  alarmStatus4;         // 系统告警状态2
    uint64_t  rawTimestamp;         // 时间戳 系统boot
    uint32_t  rawGpsTime;         // GPS时间戳(秒)
    double  rawGpsLat;         // GPS纬度(度)
    double  rawGpsLon;         // GPS经度(度)
    float   rawGpsAlt;         // GPS海拔高度（米）
    float   rawVelNedX;         // x在NED坐标系中的速度，单位为m/s
    float   rawVelNedY;         // y在NED坐标系中的速度，单位为m/s
    float   rawVelNedZ;         // z在NED坐标系中的速度，单位为m/s
    float   rawAccuracyH;         // 水平精度, 以米为单位
    float   rawAccuracyV;         // 垂直精度, 以米为单位
    float   rawAccuracyS;         // 速度精度, 以米为单位
    double  rawHmsl;         // 椭球面的高度
    uint32_t  rawGnssFixType;         // GNSS fix 类型 0: no fix 1: dead reckoning only 2: 2D fix 3: 3D fix 4: GNSS + Dead Reckoning 5: Time only Fix
    uint32_t  rawSatellitesNum;         // number of satellites used
    uint32_t  rawGpsQuality;         // GPS质量等级(0~100)

    std::string ToString() const;
};

struct AUTELSDK_API FileUploadInfo
{
    FileType fileType = FileType::UNKNOWN;
    std::string fileName;

    std::string ToString() const;
};

//上报遥控器位置信息给飞机
struct AUTELSDK_API RCPositionInfo
{
    uint64_t timestamp; //时间戳 ms
    double lattitude = 0.0;  //纬度，精度为 10E-7 度
    double longitude = 0.0;  //经度，精度为 10E-7 度
    float altitude = 0.0;  //高度(相对海平面)，精度为 10E-3 米
    int32_t posType = 0;  //位置类型，0:起飞点位置  1:实时GPS位置  2:固定位置
    int32_t altType = 0;  //高度类型，预留字段
    int32_t coordinateSystem = 0;  //坐标系  0:WGS84
    float velNedX = 0;  //GPS南北方向速度(北为正)  单位: m/s
    float velNedY = 0;  //GPS东西方向速度(东为正)  单位: m/s
    float velNedZ = 0;  //GPS垂直方向速度(下为正)  单位: m/s
    float accuracyS = 0;  //速度精度值  单位: m/s
    int32_t satellitesNum = 0;  //搜星数量

    std::string ToString() const;
};


} // namespace AutelMobileSdk

#endif
