#ifndef DEVICE_DATA_TYPE_H
#define DEVICE_DATA_TYPE_H

#include <unordered_map>

#include "ErrorCode.h"
#include "CameraBaseType.h"
#include "CameraKeyDataType.h"
#include "GimbalKeyDataType.h"
#include "MiscDataType.h"
#include "FlightPropertyKeyDataType.h"
#include "Common.h"

namespace AutelMobileSdk
{
struct CameraData
{
    // TODO:
};

struct CameraOperateData
{
    // TODO:
};

struct AUTELSDK_API GimbalData
{
    bool isInitialized = false;                                 // 云台姿态是否已经被初始化
    bool isCalibrating = false;                                 // 返回云台当前是否在校准
    bool isRollReachMax = false;                                // 表示云台 Roll 轴是否撞限位
    bool isOverheat = false;                                    // 云台是否过热
    bool isIMUNeedCalibrate = false;                            // 云台 是否需要IMU校准
    bool isHardwareFail = false;                                // 云台发生硬件故障
    bool isSleepForNoAttitude = false;                          // 云台是否因没有收到飞控姿态数据而处于休眠状态
    bool isSleepForRollReachMax = false;                        // 云台是否因达到 Roll 轴限位而进入休眠状态
    bool isLaserRangingSwitchOn = false;                        // 云台激光测距开关
    bool isPitchAngelRangeSwitchOn = false;                     // 云台俯仰限位开关

    GimbalType gimbalType;                                      // 云台类型
    GimbalWorkModeEnum workMode = GimbalWorkModeEnum::UNKNOWN;  // 云台工作状态
    GimbalMotorStatus motorStatus = GimbalMotorStatus::NONE;    // 马达工作状态

    float rotateAngle = 0.0;                                    // 四轴云台rotate轴角度值
    float rotateAngleRange = 0.0;                               // 四轴云台rotate轴角速度值

    int gimbalCalibrateStatus = 0;                              // 表示云台当前的角度校准状态
    int gimbalCalibratePercent = 0;                             // 表示云台当前的角度校准百分比（0-100）
    int pitchAngleRange = 0;                                    // 云台PITCH轴微调角度
    int pitchSpeed = 0;                                         // 云台俯仰速度
    int rollAdjustAngle = 0;                                    // 云台ROLL轴微调角度
    int yawAdjustAngle = 0;                                     // 云台YAW轴微调角度

    CameraData cameraData;                                      // 相机上报数据
    CameraOperateData cameraOperData;                           // 相机的cache数据

    //重载==
    bool operator ==(const GimbalData& other) const
    {
        return isInitialized == other.isInitialized
               && isCalibrating == other.isCalibrating
               && isRollReachMax == other.isRollReachMax
               && isOverheat == other.isOverheat
               && isIMUNeedCalibrate == other.isIMUNeedCalibrate
               && isHardwareFail == other.isHardwareFail
               && isSleepForNoAttitude == other.isSleepForNoAttitude
               && isSleepForRollReachMax == other.isSleepForRollReachMax
               && isLaserRangingSwitchOn == other.isLaserRangingSwitchOn
               && isPitchAngelRangeSwitchOn == other.isPitchAngelRangeSwitchOn
               && gimbalType == other.gimbalType
               && workMode == other.workMode
               && motorStatus == other.motorStatus
               && rotateAngle == other.rotateAngle
               && rotateAngleRange == other.rotateAngleRange
               && gimbalCalibrateStatus == other.gimbalCalibrateStatus
               && gimbalCalibratePercent == other.gimbalCalibratePercent
               && pitchAngleRange == other.pitchAngleRange
               && pitchSpeed == other.pitchSpeed
               && rollAdjustAngle == other.rollAdjustAngle
               && yawAdjustAngle == other.yawAdjustAngle;
               //&& cameraData == other.cameraData
               //&& cameraOperData == other.cameraOperData;
    }

    std::string ToString() const;
};

struct AUTELSDK_API CameraStateMachine
{
    int cameraId = 0;
    bool aeLock = false;
    CameraStatus cameraStatus;
    ProfessionalParamInfo professionalParam;
    CameraAFAEStatusInfo aeAfState;
    StorageStatusInfo storageStatusInfo;
    PixelResolution photoResolution;
    PixelResolution videoResolution;
    // TODO: 按组网版本刷新

    std::string ToString() const;
};

struct AUTELSDK_API GimbalStateMachine
{
    int gimbalId = 0;
    GimbalState state;
    // TODO: 按组网版本刷新

    std::string ToString() const;
};

struct AUTELSDK_API FlightControlData
{
    // 飞机纬度，当它是个无效值或isGPSValid为NO，说明无法定位位置，应当忽略。
    double droneLatitude = 0.0;
    // 飞机经度，当它是个无效值或isGPSValid为NO，说明无法定位位置，应当忽略。
    double droneLongitude = 0.0;
    // 飞机相对高度
    float altitude = 0.0;
    // 飞机海拔高度
    float altitudeMSL = 0.0;
    // x速度X
    float velocityX = 0.0;
    // y速度
    float velocityY = 0.0;
    // z速度
    float velocityZ = 0.0;
    // 飞行器姿态 pitch degree
    float droneAttitudePitch = 0.0;
    // 飞行器姿态 roll degree
    float droneAttitudeRoll = 0.0;
    // 飞行器姿态 yaw degree
    float droneAttitudeYaw = 0.0;
    // 云台姿态 pitch degree
    float gimbalAttitudePitch = 0.0;
    // 云台姿态 roll degree
    float gimbalAttitudeRoll = 0.0;
    // 云台姿态 yaw degree
    float gimbalAttitudeYaw = 0.0;
    // 飞机与 Home 点之间的距离
    float distance = 0.0;
    // 超声对地高度
    float ultrasoundAltitude = 0.0;
    // 激光测距距离; 单位cm
    int laserDistance = 0;
    // 表示激光测距距离是否有效;0无效，1有效
    bool laserDistanceIsValid = false;
    // 雷达高度检测结果
    double radarHeight = 0.0;
    // 飞行模式
    DroneFlightMode flightMode = DroneFlightMode::Unknown;
    // 飞控主模式，见 FLIGHT_CONTROL_MAIN_MODE
    FlightControlMainMode mainMode = FlightControlMainMode::Unknown;
    // 飞机智能模式; 见FlightControlDefine -> DroneWorkMode
    DroneWorkMode droneWorkMode = DroneWorkMode::Unknown;
    // 飞机工作状态
    DroneWorkState droneWorkStatus = DroneWorkState::Unknown;
    // 跟踪工作状态。0：退出跟随，1：检测状态 2：目标跟随状态（云台动，飞机不动）3：规划跟随状态（云台动，飞机动）
    TrackWorkState trackWorkStatus = TrackWorkState::EXIT_FOLLOW;
    // GPS开关状态（false：GPS关闭 true：GPS打开）
    bool isGpsOpen = false;
    // 剩余飞行时间
    float remainingFlightTime = 0.0;
    // 电池剩余电量
    int batteryRemainingPower = 0;
    // 电池电量百分比
    float batteryPercentage = 0.0;
    // 电池温度
    float batteryTemperature = 0.0;
    // 电池当前电压
    float batteryVoltage = 0.0;
    // 电池当前电流
    float batteryCurrent = 0.0;
    // 可见卫星数
    int satelliteCount = 0;
    // remoteID工作状态，
    bool remoteIdStatus = false;
    // 当前视觉SLAM置信度;视觉定位强弱 0.7以上高，0.4到0.7中，0.4以下低
    double slamConfidence = 0.0;
    // 当前GPS强度百分比 建议：40%以下为弱;80%以下为中，大于80%强
    int gpsStrengthPercentage = 0;
    // 飞机类型
    int droneType = 0;
    // 飞机档位，见 GEAR_LEVEL
    GearLevel droneGear = GearLevel::UNKNOWN;
    // 是否支持RTK
    bool supportRTK = false;
    // home点是否无效
    bool isHomeInvalid = false;
    // home点纬度
    double homeLatitude = 0.0;
    // home点经度
    double homeLongitude = 0.0;
    // 避障使能
    bool obstacleAvoidanceEnabled = false;
    // 雷达图显示
    bool radarChartDispalyed = false;
    // 下视补光灯状态
    int visionledStatus = 0;
    // 降落保护开关
    bool visionEnableSecureLanding = false;
    // 是否启用精准降落功能
    bool visionEnablePreciseLanding = false;
    // 指南针校准状态
    CompassCalibrationStatus compassCalibrationStatus = CompassCalibrationStatus::NONE;
    // IMU校准状态
    IMUCalibrationStep imuCalibrationStatus = IMUCalibrationStep::NONE;
    // 电池放电次数
    int numberOfDischarge = 0;
    // 电池不在位标志0：在位 1：不在位
    BatteryInPlace batteryState = BatteryInPlace::UNREADY;
    // 当前飞机环境亮度信息 0:正常的亮度说明视觉特征应该是可行的 1:环境亮度对于某些视觉特征来说太低了
    Environment environmentInfo = Environment::NORMAL_BRIGHTNESS;
    int aiEnableFunc = 0;

    //重载==
    bool operator ==(const FlightControlData& other) const
    {
        return droneLatitude == other.droneLatitude
               && droneLongitude == other.droneLongitude
               && altitude == other.altitude
               && altitudeMSL == other.altitudeMSL
               && velocityX == other.velocityX
               && velocityY == other.velocityY
               && velocityZ == other.velocityZ
               && droneAttitudePitch == other.droneAttitudePitch
               && droneAttitudeRoll == other.droneAttitudeRoll
               && droneAttitudeYaw == other.droneAttitudeYaw
               && gimbalAttitudePitch == other.gimbalAttitudePitch
               && gimbalAttitudeRoll == other.gimbalAttitudeRoll
               && gimbalAttitudeYaw == other.gimbalAttitudeYaw
               && distance == other.distance
               && ultrasoundAltitude == other.ultrasoundAltitude
               && ultrasoundAltitude == other.ultrasoundAltitude
               && laserDistance == other.laserDistance
               && laserDistanceIsValid == other.laserDistanceIsValid
               && radarHeight == other.radarHeight
               && flightMode == other.flightMode
               && mainMode == other.mainMode
               && droneWorkMode == other.droneWorkMode
               && droneWorkStatus == other.droneWorkStatus
               && trackWorkStatus == other.trackWorkStatus
               && isGpsOpen == other.isGpsOpen
               && remainingFlightTime == other.remainingFlightTime
               && batteryRemainingPower == other.batteryRemainingPower
               && batteryPercentage == other.batteryPercentage
               && batteryTemperature == other.batteryTemperature
               && batteryVoltage == other.batteryVoltage
               && batteryCurrent == other.batteryCurrent
               && satelliteCount == other.satelliteCount
               && remoteIdStatus == other.remoteIdStatus
               && slamConfidence == other.slamConfidence
               && gpsStrengthPercentage == other.gpsStrengthPercentage
               && droneType == other.droneType
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
               && batteryState == other.batteryState
               && environmentInfo == other.environmentInfo
               && aiEnableFunc == other.aiEnableFunc;
    }

    std::string ToString() const;
};

struct AUTELSDK_API FlightOperateData
{
    // 飞行器激活状态
    bool aircraftActivation = false;
    // 是否开启atti模式
    bool bAttiMode = false;
    // 灵敏度姿态值
    float fAttitudeSensitivity = 0.0;
    // 电池严重低电量告警值
    int batSeriousLowWarningValue = 0;
    // 电池低电量告警值
    int batteryLowWarningValue = 0;
    // 新手模式
    OperatorModeEnum operMode = OperatorModeEnum::NEW_HAND;
    // 灵敏度刹车值
    float fBrakeSensitivity = 0.0;
    // 蜂鸣状态（查找飞机）值
    bool buzzingStatus = false;
    // 协调转弯值
    bool coordinatedTurn = false;
    // 最大下降飞行速度值
    float fDescentSpeed = 0.0;
    // 绕障功能开关
    bool fcsApasModeEn = false;
    // GPS飞行开关
    bool fcsEnGpsMode = false;
    // 超级电容开关状态
    bool fCSEnSuperCap = false;
    // GPS工作模式
    DroneGpsEnum fcsSwitchGpsMode = DroneGpsEnum::UNKNOWN;
    // 融合视觉定位开关
    bool locationStatus = false;
    // 低电量返航开关值
    bool lowBatLowBack = false;
    // 最大上升飞行速度值
    float fMaxAscentSpeed = 0.0;
    // 最大飞行高度值
    float maxHeight = 0.0;
    // 最大水平飞行速度值
    float maxHorizontalSpeed = 0.0;
    // 最大飞行半径值
    float maxRadius = 0.0;
    // EXP向前向后值
    float pitchSensitivity = 0.0;
    // 飞机失联行为值
    DroneLostActionEnum rcLostAction = DroneLostActionEnum::UNKNOWN;
    // EXP向左向右值
    float rollSensitivity = 0.0;
    // 静默模式状态值
    bool silentModeStatus = false;
    // EXP上升下降值
    float thrustSensitivity = 0.0;
    // EXP左转右转值
    float yawAngleSensitivity = 0.0;
    // 灵敏度偏航行程值
    float yawTripSensitivity = 0.0;
    // 返航高度
    float backHeight = 0.0;
    // 飞机各部件版本信息
    std::list<DroneComponentVerInfo> droneVersions;
    // 返航的水平速度
    float backHSpeed = 0.0;
    // 返航的垂直速度
    float backVSpeed = 0.0;

    //重载==
    bool operator ==(const FlightOperateData& other) const
    {
        return aircraftActivation == other.aircraftActivation
               && bAttiMode == other.bAttiMode
               && fAttitudeSensitivity == other.fAttitudeSensitivity
               && batSeriousLowWarningValue == other.batSeriousLowWarningValue
               && batteryLowWarningValue == other.batteryLowWarningValue
               && operMode == other.operMode
               && fBrakeSensitivity == other.fBrakeSensitivity
               && buzzingStatus == other.buzzingStatus
               && coordinatedTurn == other.coordinatedTurn
               && fDescentSpeed == other.fDescentSpeed
               && fcsApasModeEn == other.fcsApasModeEn
               && fcsEnGpsMode == other.fcsEnGpsMode
               && fCSEnSuperCap == other.fCSEnSuperCap
               && fcsSwitchGpsMode == other.fcsSwitchGpsMode
               && locationStatus == other.locationStatus
               && lowBatLowBack == other.lowBatLowBack
               && fMaxAscentSpeed == other.fMaxAscentSpeed
               && maxHeight == other.maxHeight
               && maxHorizontalSpeed == other.maxHorizontalSpeed
               && maxRadius == other.maxRadius
               && pitchSensitivity == other.pitchSensitivity
               && rcLostAction == other.rcLostAction
               && rollSensitivity == other.rollSensitivity
               && silentModeStatus == other.silentModeStatus
               && thrustSensitivity == other.thrustSensitivity
               && yawAngleSensitivity == other.yawAngleSensitivity
               && yawTripSensitivity == other.yawTripSensitivity
               && backHeight == other.backHeight
               && droneVersions == other.droneVersions
               && backHSpeed == other.backHSpeed
               && backVSpeed == other.backVSpeed;
    }

    std::string ToString() const;
};

struct AUTELSDK_API DroneStateData
{
    DeviceId deviceId;
    SystemInfo systemInfo;
    std::vector<DroneComponentVerInfo> componentVersions;
    std::unordered_map<int, CameraStateMachine> cameraStates;
    std::unordered_map<int, GimbalStateMachine> gimbalStates;
    DroneSystemStateHF droneSystemHFState;
    DroneSystemStateLFNtfyInfo droneSystemLFState;
    FlightControlStatusInfo flightControlState;
    DroneWarningStateNtfy droneWarningState;
    FlightControlData flightControlData;
    FlightOperateData flightOperateData;
    GimbalData gimbalData;

    std::string ToString() const;
};

struct AUTELSDK_API SDKErrorInfo
{
    SDKErrorType errorType = SDKErrorType::UNKNOWN;
    AutelStatusCode errorCode = AutelStatusCode::UNKNOWN;
    std::string errorMsg;

    std::string ToString() const;
};
} // namespace AutelMobileSdk

#endif
