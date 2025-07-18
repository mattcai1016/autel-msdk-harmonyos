#ifndef KEY_VALUE_BASE_TYPE_H
#define KEY_VALUE_BASE_TYPE_H

namespace AutelMobileSdk
{
enum class DroneFlightMode
{
    Disarm = 0,      // 电机停止
    Landed = 1,      // 飞行器电机在转动，但飞行器还在地面上
    Landing = 2,     // 飞行器正在降落 不要使用了，用DroneWorkMode::Land代替
    TakeOff = 3,     // 飞行器正在起飞,包括自动起飞和通过遥控器控制起飞不要使用了，用DroneWorkMode::TAKEOFF代替
    Attitude = 4,    // 飞行器正在飞行，处于姿态模式（无GPS、无视觉）
    GPS = 5,         // 飞行器正在飞行，处于GPS模式或StarPoint（视觉）模式
    Working = 6,     // 飞行器正在进行智能任务
    Unknown = 0xff,
};

enum class FlightControlMainMode
{
    Unknown = 0,
    Attitude = 1,   // 姿态：无定位且无视觉
    GPS = 2,
    IOC = 3,
    StarPoint = 4,  // 室内定位：无定位，有视觉
};

enum class DroneWorkMode
{
    Waypoint = 1,                    // 航点
    Rectangle = 2,                   // 矩形
    Polygon = 3,                     // 多边形
    Pthotography = 4,                // 倾斜摄影
    Vedio = 5,
    Keyframe = 6,                    // 精准复拍
    Delaysurr = 7,                   // 延时摄影
    NormalOrbit = 8,                 // 环绕
    Panorama = 9,                    // 全景
    Return = 10,                     // 返航
    Spiral = 11,                     // 螺旋
    SuperclearMat = 12,              // 超清
    Track = 13,                      // 可见光跟踪
    Land = 14,                       // 智能下降模式
    Takeoff = 15,                    // 自动起飞模式
    InterestPoint = 16,              // 智能图传打点模式
    InfraredTrack = 17,              // 红外跟踪
    AirStrip = 18,                   // 智能任务航带飞行
    PolygonalImitation = 19,         // 智能任务多边形仿地
    MonomerSurround = 20,            // 智能任务单体环绕
    LandManual = 21,                 // 手动下降模式，云台可以被飞控控制
    PanoramicIntelligentDetect = 22, // 全景智能检测
    SecurityIntelligentDetect = 23,  // 安防智能检测
    ManualSmooth = 24,               // 手动舒适档
    ManualNormal = 25,               // 手动标准档
    SemiAuto = 26,                   // 手动绕障模式
    GpsEscape = 27,                  // Gps逃逸模式
    Sport=28,//狂暴模式档位（目前不使用）
    Exception=29,//异常模式状态，兰前只是planner选程挂掉，会切换至此模式，而且飞控会接管自动返航
    Swarm = 30,//蜂群编队模式
    Fast = 31,//快速任务(目前用于组网空中替换）
    OrbitModeling = 32,//建模环绕模式
    KML=33,//kml航线模式
    FlyTo = 34,//飞向目标点模式
    RemoteControl = 35,//远程控制模式
    TrafficAccidents = 36,//交通快处模式
    Unknown = 0,
};

enum class DroneWorkState
{
    Pause = 1,       // 悬停
    Running = 2,     // 执行中
    Completed = 3,   // 完成
    Unusual = 4,     // 异常中止
    Unknown = 0,
};

enum class DroneComponentId
{
    NONE = 0,

    // 升级组件ID: 1000 ~ 1019
    UPGRADE_SERVER = 1000,
    UPGRADE_CLIENT = 1001,
    UPGRADE_NODE1 = 1002,
    UPGRADE_NODE2 = 1003,
    UPGRADE_NODE3 = 1004,
    UPGRADE_NODE4 = 1005,

    // 业务主控组件ID: 1020~1029
    SERVICE_MAIN_CONTROL = 1021,

    // 遥控器协议网关ID: 1030~1039
    PROTOCOL_GATEWAY_RC = 1031,

    // 系统服务组件ID:1040~1049
    SYSTEM_PACKAGE      = 1040,
    SYS_MANAGER_SKYLINK = 1041,
    SYS_MANAGER_VISION = 1042,
    SYS_MANAGER_SKYLINK_RC = 1043,
    SYS_MANAGER_660_RC = 1044,
    SYS_MANAGER_660_CAMERA = 1045,

    // 飞控网关 componentID: 1050~1059
    COMPONENT_TYPE_FCS_GATEWAY_SKYLINK = 1051,
    COMPONENT_TYPE_FCS_GATEWAY_VISION  = 1050,

    // mif componentID：1060~1069
    MIF=1060,

    // planner componentID: 1070~1079
    PLANNER=1070,

    // soa componentID: 1080~1089
    SOA=1080,

    // ai componentID: 1090~1099
    AI=1090,

    // mission manager componentID: 1100~1109
    MISSION_MANAGER=1100,

    // target estimation componentID: 1110~1119
    TARGET_ESTIMATION=1110,

    // camera componentID: 1120~1129
    CAMERA=1120,

    // radar componentID: 1280~1299
    RADAR=1280,
    RADAR_FRONT=1281,
    RADAR_BACK=1282,
    RADAR_UP=1283,
    RADAR_DOWN=1284,
    RADAR_LEFT=1285,
    RADAR_RIGHT=1286,


    // remoteID componentID: 1140~1149
    REMOTEL_ID=1140,

    // FCS componentID: 1150~1159
    FCS=1150,

    // battery componentID: 1160~1169
    BATTERY=1160,

    // gimbal componentID: 1170~1179
    GIMBAL=1170,

    // ESC componentID: 1180~1189
    ESC1=1180,
    ESC2=1181,
    ESC3=1182,
    ESC4=1183,

    // platform SM8475 componentID: 1190~1199
    PLATFORM_VISION=1190,

    // platform LC1881 componentID: 1200~1209
    PLATFORM_SKYLINK=1200,

    // Fill light componentID: 1210~1219
    FILL_LIGHT=1210,

    // Autel vision componentID: 1220~1229
    AUTEL_VISION=1220,

    // Log collector componentID: 1230~1239
    LOG_COLLECT_SKYLINK=1230,
    LOG_COLLECT_VISION=1231,
    LOG_COLLECT_CAMERA=1232,

    // Micro ftp componentID: 1240~1249
    MICRO_FTP_SKYLINK=1240,
    MICRO_FTP_VISION=1241,
    MICRO_FTP_CAMERA=1242,

    // AtService componentID: 1250~1259
    ATSERVICE_AIR=1250,
    ATSERVICE_RC=1251,

    // Night light componentID: 1260~1269
    NIGHT_LIGHT=1260,

    // Time sync componentID: 1270~1279
    TIME_SYNC_SKYLINK=1270,
    TIME_SYNC_VISION=1271,
    TIME_SYNC_CAMERA=1272,

    // APP componentID: 1300~1309
    APP=1300,

    // System Check componentID: 1310~1399
    SYSTEM_CHECK=1310,

    // Remote Control componentID：1400~1499
    REMOTE_CONTROL  = 1400,
    TRANSMIT_RC     = 1401,
    MCU_RC          = 1402,
    MOTOR_RC        =1403,

    // photo album componentID: 1500~1509
    ALBUM_MANAGER=1500,

    // Accessories proxy componentID: 1510~1515
    ACCPROXY=1510,

    //ntrip客户端（rtk功能）: 1516~1516
    NTRIP_CLIENT = 1516,

    //4G/5G模块的代理服务: 1517~1517
    LTE_AGENT = 1517,

    //MQTT代理服务: 1518~1518
    MQTT_AGENT = 1518,

    //RTMP客户端: 1519~1519
    RTMP_CLIENT = 1519,

    // 时间同步服务组件ID: 1520~1529
    TIME_SYNC_SERVER=1520,
    TIME_SYNC_CLIENT=1521,
    TIME_SYNC_NODE1=1522,
    TIME_SYNC_NODE2=1523,

    // 日志服务组件ID：1530-1539
    LOG_CLIENT =1530,

    // platform A810 componentID: 1540~1549
    PLATFORM_CAMERA=1540,

    // 上云API componentID: 1550~1559
    CLOUD_API_DRONE = 1550,  //飞机端上云API
    CLOUD_API_RC = 1551,  //遥控端上云API
    CLOUD_API_NEST = 1552,  //机巢端上云API
    // RTC客户端: 1560~1564
    RTC_CLIENT = 1560,
};

enum class DroneComponent
{
    //飞机端模块Type：1000~1099
    UNKNOWN = 0,
    SYSTEM_PACK                        = 1000, // system pack
    MIF                                = 1001, // MIF
    PLANNER                            = 1002, // PLANNER
    SOA                                = 1003, // SOA
    AISERVICE                          = 1004, // ai
    MISSION_MANAGER                    = 1005, // mission manager
    SERVICE_CONTROL                    = 1006, // service main control
    FCS_GATEWAY                        = 1007, // fcs gateway
    TARGET_ESTIMATION                  = 1008, // target estimation
    TARGET_CAMERA                      = 1009, // camera
    TARGET_RADAR                       = 1010, // radar
    TARGET_UPGRADE                     = 1011, // upgrade
    TARGET_REMOTEID                    = 1012, // remoteID
    TARGET_FCS                         = 1013, // FCS
    TARGET_BATTERY                     = 1014, // battery
    TARGET_GIMBAL                      = 1015, // gimbal
    TARGET_ESC                         = 1016, // ESC
    TYPE_SYSTEM_MANAGER                = 1017, // system manager
    TYPE_PLATFORM_VISION               = 1018, // platform VISION
    TYPE_PLATFORM_SKYLINK               = 1019, // platform SKYLINK
    TYPE_FILL_LIGHT                    = 1020, // Fill light
    TYPE_AUTEL_VISION                  = 1021, // Autel vision
    TYPE_LOG_COLLECTOR                 = 1022, // Log collector
    TYPE_MICRO_FTP                     = 1023, // Micro ftp
    TYPE_ATSERVICE_AIR                 = 1024, // AtService air
    TYPE_NIGHT_LIGHT                   = 1025, // Night light
    TYPE_TIME_SYNC                     = 1026, // Time sync
    TYPE_APP                           = 1027, // App
    TYPE_ALBUM_MANAGER                 = 1028, // photo album

    //遥控器端模块Type: 1100~1199
    RC = 1100,					//遥控器
    MCU = 1101,					//mcu
    TRANSMIT = 1102,				//transmit
    MOTOR = 1103,					//电机驱动板
    ATSERVICE_RC = 1104, 			//遥控At服务
    PROTOCOL_GATEWAY_RC = 1105, 	//遥控协议网关
    SYSTEM_MANAGER_RC = 1106, 	//遥控端系统服务
    // 飞机端遥控器端公共模块: 1200~1299
    SYSTEM_CHECK                        = 1200, // system check
    /*
    UNKNOWN = 0,
    SYSTEM_PACK = 1000,
    MIF = 1001,
    PLANNER = 1002,
    SOA = 1003,
    AISERVICE = 1004,
    MISSION_MANAGER = 1005,
    SERVICE_CONTROL = 1006,
    ALINRK_ROS = 1007,
    TARGET_ESTIMATION = 1008,
    TARGET_CAMERA = 1009,
    RADAR = 1010,
    TARGET_UPGRADE = 1011,
    TARGET_REMOTEID = 1012,
    TARGET_FCS = 1013,
    TARGET_BATTERY = 1014,
    TARGET_GIMBAL = 1015,
    TARGET_ESC = 1016,
    SYSTEM_MANAGER = 1017,
    PLATFORM_VISION = 1018,
    PLATFORM_SKYLINK = 1019,
    FILL_LIGHT = 1020,
    AUTEL_VISION = 1021,
    LOG_COLLECTOR = 1022,
    MICRO_FTP = 1023,
    ATSERVICE_AIR = 1024,
    NIGHT_LIGHT = 1025,
    TIME_SYNC = 1026,
    COMPONENT_RC = 1100,
    COMPONENT_MCU = 1101,
    COMPONENT_TRANSMIT = 1102,
    COMPONENT_MOTOR = 1103,
    AT_SERVICE = 1104,
    GATEWAY_RC = 1105,
    ALBUM_MANAGER = 1028,
    MCU_RC = 1101,
    TRANSMIT_RC = 1102,
    MOTOR = 1103,
    ATSERVICE_RC = 1104,
    PROTOCOL_GATEWAY_RC = 1105,
    COMPONENT_SYS_MANAGER_RC = 1106,
*/
};

enum class GPSLevel
{
    LEVEL0 = 0,//GPS 信号非常差
    LEVEL1 = 1,//GPS 信号很弱
    LEVEL2 = 2,//GPS 信号弱
    LEVEL3 = 3,//GPS 信号好
    LEVEL4 = 4,//GPS 信号很好
    LEVEL5 = 5,//GPS 信号非常强
    LEVEL_NONE = 6,//没有 GPS 信号，或 GPS 不可用
};

enum class GearLevel
{
    UNKNOWN = 0, //未知
    SMOOTH = 1,  //平稳档
    NORMAL = 2,  //普通档
    SPORT = 3,   //运动档
};

enum class CompassCalibrationStatus
{
    NONE = 0,//磁力计没有在校准
    STEP1 = 1,//第一步：开始校准，检查飞行器摆放位置：水平握住飞行器机翼，并以自身为中心旋转，直到4盏LED灯闪烁绿灯。
    ROTATE1 = 2,//第一步：开始转圈
    STEP2 = 3,//第二步：开始校准：使飞行器与地面垂直且机头朝下，双手握住机翼，并以自身为中心旋转，直到4盏LED灯变为绿色常亮。
    ROTATE2 = 4,//第二步：开始转圈
    STEP3 = 8,//第三步：检查飞机摆放位置：将飞机侧向旋转至绿灯亮起。
    ROTATE3 = 9,//第三步：开始转圈
    CALCULATING = 5,//第三步：开始转圈
    FAILED = 6,//校准失败。
    SUCCESSED = 7,//校准成功。
    UNKNOWN = 0xff,//未知状态。
};

enum class IMUCalibrationStep
{
    NONE = 0,
    STEP1 = 1,
    STEP2 = 2,
    STEP3 = 3,
    STEP4 = 4,
    STEP5 = 5,
    STEP6 = 6,
    SUCCESS = 7,
    FAILED = 8,
    UNKNOWN = 9,
};

enum class Environment
{
    NORMAL_BRIGHTNESS = 0,//正常的亮度说明视觉特征应该是可行的
    LOW_BRIGHTNESS = 1,//环境亮度对于某些视觉特征来说太低了
};

enum class BatteryPowerWarning
{
    NONE = 0,
    LOW = 1,
    SERIOUS = 2,
    SMART = 3,
};

enum class FlightControlTurnOnMotorStatus
{
    NO_ERROR = 0,                   //无错误
    IMU_LOSS = 1,			        //IMU异常
    CRITICASL_BATTERY = 2,           //电量严重不足
    BARO_LOSS = 3,                   //气压计异常
    REDZONE = 4,                     //禁飞区
    IOC_ERROR = 5,                   //IOC模式异常
    BEGINNER_NO_GPS = 6,             //新手模式下没有GPS信号
    DISARM_TILT_OVER_45DEG = 7,      //飞机倾角大于45度
    DISARM_IMU_LOSS = 8,			    //IMU异常
    IMU_IS_WARMING_UP = 9,           //IMU预热
    MAGNETOMETER_ISCALIBRATING = 10, //正在校准磁力计
    MULTIPLE_SENSORS_ERROR = 11,     //多个传感器异常
    GIMBAL_IS_NOT_READY = 12,        //云台未就绪
    UPGRADE_IS_ONGOING = 13,         //正在执行升级
    IMU_NEED_USER_CALIBRATION = 14,  //IMU需要用户校准
    ATTITUDE_INITIALIZATION = 15,	//姿态初始化中
    RTK_NOT_READY = 16,              //RTK未就绪
    DRONE_NONACTIVATED = 17,         //飞机未激活
};

enum class IMUCalibratoionWarning
{
    NONE = 0,//没有告警
    BEGIN = 1,//开始校准
    CALCULATING = 2,//校准中
    SAKING = 3,//机身晃动
    WRONGDIRECTION = 4,//朝向不对
};

enum class MainControllerNoflyZoneStatus
{
    FLYING = 0,
    LIMIT_APPROACHING = 1,
    LIMIT_REACH = 2,
    LIMIT_MAXHEIGHT = 3,
    INSIDE = 4,
    FLY_INSIDE = 5,
    FLY_STATUS_UNKNOW = 0xFF,
};

enum class CompassInterferenceLevel
{
    LEVEL0 = 0,
    LEVEL1 = 1,
    LEVEL2 = 2,
    LEVEL3 = 3,
    LEVEL4 = 4,
};
//遥控器飞行模式
enum class RcFlightMode
{
    UNKNOWN = 0,
    IOC = 1,//开关处于左边档位，代表IOC模式
    GPS = 2,//开关处于中间档位，代表GPS模式
    ATTI = 3,//开关处于右边档位，代表姿态模式
};

//遥控器按钮
enum class RCButtonType
{
    UNKNOWN = 0,
    GO_HOME = 1,//起飞/降落按钮
    HOVER = 2,//悬停按钮
    PHOTO_RECORD = 3,//拍照/录像按钮
    PHOTO = 4,//拍照
    RECORD = 5,//录像
    LEFT_CUSTOM = 6,//左侧自定义按钮
    RIGHT_CUSTOM = 7,//右侧自定义按钮
    ZOOM_IN = 8,//右侧滚轮zoom in
    ZOOM_OUT = 9,//右侧滚轮zoom out
    RC_LEFT_WHEEL = 10,//左侧滚轮
    VIDEO = 11,//录像
};

enum class RcButtonState
{
    UNKNOWN = 0,
    ROLL = 1,
    CLICK = 2,
    LONG_PRESS = 3,
    DOUBLE_CLICK = 4,
};

enum class DroneLedType
{
    NONE = 0,// 未知
    BOTTOM_LED = 1,// 下视
};

enum class DroneLedStatus
{
    UNKNOWN = 0,// 未知
    OPEN = 1,//打开
    AUTO = 2,//自动控制
    FLASH = 3,//闪烁
    CLOSE = 4,//关闭
};

enum class CalibrationType
{
    UNKNOWN = 0,
    IMU = 1,//飞机IMU校准
    COMPASS = 2,//飞机指南针校准
    GIMBAL_ANGLE = 3,//云台角度校准
};

enum class Cmd
{
    UNKNOWN = 0,
    START = 1,//开始
    STOP = 2,//结束
};

enum class CalibrationEvent
{
    UNKNOW                 = 0,  //无校准信息
    START                  = 1,  //开始校准
    SUCCESS                = 2,  //校准成功
    SAVE_DATA_FAILED       = 3,  //数据保存失败
    INVALID_LEANS          = 4,  //飞行器倾斜
    INVALID_SHAKE          = 5,  //飞行器晃动
    INVALID_MOTOR_WORKING  = 6,  //飞行器电机转动中
    TIMEOUT                = 7,  //校准超时
    NOGPS                  = 8,  //无GPS，无法进行校准
    WRONG_DIRECTION        = 9,  //飞行器朝向不对
    FAIL                   = 10, //校准失败
    CALCULATE              = 11, //校准数据计算中
    RESERVE_COMPASS_FAIL   = 12, //备用指南针校准失败
    MAIN_COMPASS_FAIL      = 13, //主指南针校准失败
};

enum class ImuCalibrationStep
{
    STEP0 = 0,//未开始进行校准。
    STEP1 = 1,//校准步骤1：水平朝上。
    STEP2 = 2,//校准步骤2：水平朝下。
    STEP3 = 3,//校准步骤3：右侧朝上侧放。
    STEP4 = 4,//校准步骤4：左侧朝上侧放。
    STEP5 = 5,//校准步骤5：竖直朝上。
    STEP6 = 6,//校准步骤6：竖直朝下。
};

enum class CompassCalibrationStep
{
    STEP0 = 0,//未开始进行校准
    STEP1 = 1,//第一步：开始校准，检查飞行器摆放位置：水平握住飞行器机翼，并以自身为中心旋转，直到4盏LED灯闪烁绿灯。
    ROTATE1 = 2,//第一步：开始转圈
    STEP2 = 3,//第二步：开始校准：使飞行器与地面垂直且机头朝下，双手握住机翼，并以自身为中心旋转，直到4盏LED灯变为绿色常亮。
    ROTATE2 = 4,//第二步：开始转圈
    STEP3 = 5,//第三步：检查飞机摆放位置：将飞机侧向旋转至绿灯亮起。
    ROTATE3 = 6,//第三步：开始转圈
};

enum class EventPriority
{
    UNKNOWN = 0,
    HINT = 1,
    MODE_EXIT = 2,
    EMERGENCY = 3,
    NORMAL = 4,
};

enum class DroneEvent
{
    UNKNOWN = 0,
    EVENT_CLICK_BATTERY_CONNECT_CONFIRM = 0x00000901,
};

enum class CleanNoFlyZoneType
{
    UNKNOWN = 0,
    ALL_FILE = 1,
    TEMPORARY_NOFLY = 2,
    AUTHORIZED_NOFLY = 3,
    ELECTRIC_FENCE_NOFLY = 4,
};

enum class WaringId
{
    /**
    * 未知
    */
    UNKNOWN = -1,

    /**
     * 飞机断开连接
     */
    AIRCRAFT_DISCONNECT = -2,

    /**
     * RID自检错误告警
     */
    RID_CHECK_ERROR = -4,

    /**
     * 遥控器指南针需要校准
     */
    REMOTE_COMPASS_NEED_CALIBRATION = -4,

    /**
     * 6km<=飞机距离 或 1km<=飞机和无人机高度差，告警等级为弱：提醒用户注意飞行安全
     * */
    ADSB_WARN_WEAK = -5,

    /**
     * 3km<=飞机距离<6km 且 飞机和无人机高度差<1km，告警等级为中：提醒用户注意避让。
     * */
    ADSB_WARN_MIDDLE = -6,

    /**
     * 飞机距离<3km 且 飞机和无人机高度差<1km，告警等级为强：显示为红色，提醒用户立即避让。
     * */
    ADSB_WARN_STRONG = -7,

    /**
     *  姿态控制异常
     */
    TILT_ANGLE_CONTROL_ABNORMAL = 0x0001,

    /**
     *  航向控制异常
     */
    HEADING_ANGLE_CONTROL_ABNORMAL = 0x0002,

    /**
     *  水平速度控制异常
     */
    HORIZONTAL_VELOCITY_CONTROL_ABNORMAL = 0x0003,

    /**
     *  垂直速度控制异常
     */
    VERTICAL_VELOCITY_CONTROL_ABNORMAL = 0x0004,

    /**
     *  俯仰或滚转角融合异常
     */
    TILT_ANGLE_FUSION_ABNORMAL = 0x0005,

    /**
     *  航向融合异常
     */
    HEADING_ANGLE_FUSION_ABNORMAL = 0x0006,

    /**
     *  水平速度融合异常
     */
    HORIZONTAL_VELOCITY_FUSION_ABNORMAL = 0x0007,

    /**
     *  垂直速度融合异常
     */
    VERTICAL_VELOCITY_FUSION_ABNORMAL = 0x0008,

    /**
     *  电压异常
     */
    BATTERY_ERROR = 0x0101,

    /**
     *  电池损坏
     */
    BATTERY_DAMAGE = 0x0102,

    /**
     *  电池无效
     */
    BATTERY_INVALID = 0x0103,

    /**
     *  电池关机
     */
    BATTERY_POWER_OFF = 0x0104,

    /**
     *  电池温度低
     */
    BATTERY_TEMPERATURE_LOW = 0x0105,

    /**
     *  电池温度高
     */
    BATTERY_TEMPERATURE_HIGH = 0x0106,

    /**
     *  严重低电
     */
    CRITICAL_BATTERY = 0x0107,

    /**
     *  低电量
     */
    LOW_BATTERY = 0x0108,

    /**
     *  智能低电
     */
    INTELLIGENCE_LOW_BATTERY = 0x0109,

    /**
     *  电芯压差大
     */
    BATTERY_VOLTAGE_PRESSURE_DIFFERENTIAL = 0x010A,

    /**
     *  电池过放
     */
    BATTERY_EXCESSIVE_DISCHARGE = 0x010B,

    /**
     *  电池电压不更新
     */
    BATTERY_VOLTAGE_NOTCHANGE = 0x010C,

    /**
     * 电池电芯电压低，电芯电压低于正常工作范围，限制飞行速度，请更换电池
     * 告警等级：2 紧急告警
     */
    LOW_BATTERY_VOLTAGE = 0x010D,

    /**
     * 起飞功率过大，起飞时持续3s功率大于阈值，暂停降落，请检查飞机负载情况
     * 告警等级：2 紧急告警
     */
    HIGH_TAKEOFF_POWER = 0x010E,

    /**
     * 飞行功率过大，功率大于阈值
     * 告警等级：2 紧急告警
     */
    HIGH_FLIGHT_POWER = 0x010F,


    /**
     *  空中部分停桨
     */
    PARTIAL_ROTOR_FAILURE = 0x0201,

    /**
     *  空中全部停桨
     */
    ALL_ROTOR_FAILURE = 0x0202,

    /**
     *  电调异常
     */
    ESC_ERROR = 0x0203,

    /**
     *  部分带桨
     */
    ROTOR_PARTIALLY_MOUNTED = 0x0204,

    /**
     *  接近动力上限
     */
    APPROACH_UPPER_LIMIT_SPEED = 0x0205,

    /**
     *  接近动力下限
     */
    APPROACH_LOWER_LIMIT_SPEED = 0x0206,

    /**
     *  全部不带桨
     */
    NO_ROTOR_MOUNTED = 0x0207,

    /**
     *  IMU异常
     */
    IMU_ABNORMAL = 0x0301,

    /**
     *  气压计异常
     */
    BAROMETER_ABNORMAL = 0x0302,

    /**
     *  磁力计异常
     */
    MAGNETOMETER_ABNORMAL = 0x0303,

    /**
     *  新手模式无GPS
     */
    BEGINNER_MODE_WITHOUT_GPS = 0x0304,

    /**
     *  IMU需要校准
     */
    IMU_CALIBRATION_REQUIRED = 0x0305,

    /**
     *  磁力计需要校准
     */
    MAGNETOMETER_CALIBRATION_REQUIRED = 0x0306,

    /**
     *  RTK未就绪
     */
    RTK_NOT_READY = 0x0307,

    /**
     *  云台未就绪
     */
    GIMBAL_NOT_READY = 0x0308,

    /**
     *  正在校准磁力计
     */
    MAGNETOMETER_CALIBRATING = 0x0309,

    /**
     * 电调板温度过高，标准飞行时高于85度，狂暴飞行时高于90，限制飞行速度，请降低飞行速度
     * 告警等级：2 紧急告警
     */
    HIGH_ESC_TEMPERATURE = 0x030B,

    /**
     *  飞机倾角过大
     */
    TILT_OVER = 0x0401,

    /**
     *  飞机失联
     */
    DRONE_LOST = 0x0402,

    /**
     *  检测到撞击
     */
    HIT_DETECTED = 0x0403,

    /**
     *  禁飞区
     */
    NFZ = 0x0404,

    /**
     *  到达限高区最大高度
     */
    REACH_MAX_HEIGHT_LIMIT_ZONE = 0x0405,

    /**
     *  到达限远距离
     */
    REACH_MAX_DISTANCE_OF_GEO_FENCE = 0x0406,

    /**
     *  到达限高高度
     */
    REACH_MAX_HEIGHT_OF_GEO_FENCE = 0x0407,

    /**
     *  正在升级
     */
    UPGRADING = 0x0408,

    /**
     *  姿态初始化中
     */
    ATTITUDE_INITIALIZING = 0x0409,

    /**
     *  飞机未激活
     */
    UAV_NOT_ACTIVATED = 0x040A,

    /**
     *  大风告警
     */
    LARGE_WIND_WARNING = 0x040B,

    /**
     *  起飞点不准
     */
    HOME_POINT_NOT_GOOD = 0x040C,

    /**
     *  GPS信号弱
     */
    GPS_WEAK = 0x040D,

    /**
     *  GPS遭受诱骗
     */
    GPS_ENSNARE = 0x040E,

    /**
     *  低电警报且RC_Loss
     */
    LOW_BATTERY_AND_RC_LOST = 0x0501,

    /**
     *  RC_Loss
     */
    RC_LOST = 0x0502,

    /**
     *  低电
     */
    GO_HOME_LOW_BATTERY = 0x0503,

    /**
     *  备降
     */
    ALTERNATIVE_LANDING = 0x0504,

    /**
     *  异地降落
     */
    REMOTE_LANDING = 0x0505,

    /**
     *  nav指令
     */
    FROM_NAV_CMD = 0x0506,

    /**
     *  取消航点任务并返航
     */
    CANCEL_WAYPOINT_MISSION_AND_RETURN = 0x0507,

    /**
     *  电压异常
     */
    ABNORMAL_VOLTAGE = 0x0508,

    /**
     *  RC按键
     */
    FROM_RC_BUTTON = 0x0509,

    /**
     *  禁飞区
     */
    NO_FLY_ZONE = 0x050A,

    /**
     *  航点任务结束后返航
     */
    WAYPOINT_MISSION_FINISHED = 0x050B,

    /**
     *  未触发
     */
    NO_REACTION = 0x050C,

    /**
     *  完成
     */
    EXIT_MISSION_COMPLETED = 0x050D,

    /**
     *  用户打杆退出
     */
    EXIT_MISSION_INTERRUPT = 0x050E,

    /**
     *  目标丢失
     */
    EXIT_MISSION_OBJECT_LOSING = 0x050F,

    /**
     *  特殊的暂停指令
     */
    EXIT_MISSION_SPECIAL_PAUSE = 0x0510,

    /**
     *  用户操作退出（遥控结束）
     */
    USER_MANIPULATION_RC = 0x0511,

    /**
     *  用户操作退出（APP结束）
     */
    USER_MANIPULATION_APP = 0x0512,

    /**
     *  禁飞区限制
     */
    EXIT_MISSION_NFZ = 0x0513,

    /**
     *  地理围栏限制
     */
    EXIT_MISSION_GEOFENCING = 0x0514,

    /**
     *  飞机上锁
     */
    EXIT_MISSION_ROTOR_LOCKED = 0x0515,

    /**
     *  视觉避障
     */
    EXIT_MISSION_OBSTACLE_AVOIDING = 0x0516,

    /**
     *  降落保护等的结束命令
     */
    EXIT_MISSION_VISION_MODE_TER = 0x0517,

    /**
     *  视觉模式
     */
    EXIT_MISSION_STARPOINT_MODE = 0X0518,

    /**
     *  姿态模式
     */
    EXIT_MISSION_ATTI_MODE = 0x0519,

    /**
     *  飞机未起飞
     */
    EXIT_MISSION_NOT_TAKE_OFF = 0x051A,

    /**
     *  跟踪模式出电子围栏
     */
    EXIT_MISSION_TRACK_MODE = 0x051B,

    /**
     *  云台堵转
     */
    GIMBAL_STALLING = 0x0601,

    /**
     *  云台IMU未校准
     */
    GIMBAL_IMU_NOT_CALIBRATED = 0x0602,

    /**
     *  云台IMU故障
     */
    GIMBAL_IMU_FAULT = 0x0603,

    /**
     *  云台过热
     */
    GIMBAL_OVERHEAT = 0x0604,

    /**
     *  云台与飞控通信中断
     */
    GIMBAL_AND_UAV_COMMUNICATION_DISCONNECT = 0x0605,

    /**
     *  云台电机自检失败
     */
    GIMBAL_MOTOR_SELF_CHECKING_FAILURE = 0x0606,

    /**
     *  激光模块故障
     */
    LASER_MODULE_FAILURE = 0x0607,

    /**
     *  云台达到限位
     */
    GIMBAL_MOTOR_REACH_LIMIT = 0x0608,

    /**
     *  云台电机未校准
     */
    GIMBAL_MOTOR_NOT_CALIBRATED = 0x0609,

    /**
     *  相机输入图像异常
     */
    CAMERA_IMAGE_ERROR = 0x0701,

    /**
     *  视觉初始化异常
     */
    VISION_INIT_ERROR = 0x0702,

    /**
     *  raw图处理异常
     */
    RAW_IMAGE_ERROR = 0x0703,

    /**
     *  distord图处理异常
     */
    DISTORD_IMAGE_ERROR = 0x0704,

    /**
     *  rectify图处理异常
     */
    RECTIFY_IMAGE_ERROR = 0x0705,

    /**
     *  pointcloud图处理异常
     */
    POINT_CLOUD_IMAGE_ERROR = 0x0706,

    /**
     *  distordresize图处理异常
     */
    DISTORDRESIZE_IMAGE_ERROR = 0x0707,

    /**
     *  亮度过低perception关闭
     */
    BRIGHTNESS_LOWW_PERCEPTION_CLOSE = 0x0708,

    /**
     *  SD卡错误
     */
    SD_CARD_ERROR = 0x0801,

    /**
     *  SD卡满了
     */
    SD_CARD_FULL = 0x0802,

    /**
     *  UFS满了
     */
    UFS_FULL = 0x0803,

    /**
     *  主摄探测失败
     */
    MAIN_CAMERA_DETECT_FAIL = 0x0804,

    /**
     *  长焦摄像头探测失败
     */
    LONG_FOCAL_CAMERA_DETECT_FAIL = 0x0805,

    /**
     *  上下视觉探测失败
     */
    UPPER_AND_LOWER_VISION_DETECT_FAIL = 0x0806,

    /**
     *  前后视觉探测失败
     */
    FRONT_AND_BACK_VISION_DETECT_FAIL = 0x0807,

    /**
     *  F401 查询版本失败
     */
    F401_CHECK_VERSION_FAIL = 0x0808,

    /**
     *  变焦镜头zoom群故障
     */
    ZOOM_LENS_ZOOM_ERROR = 0x0809,

    /**
     *  变焦镜头focus群故障
     */
    ZOOM_LENS_FOCUS_ERROR = 0x080a,

    /**
     *  F401 固件升级失败
     */
    F401_FIRMWARE_UPDATE_FAIL = 0x080b,

    /**
     *  红外摄像头打开失败
     */
    INFRARED_CAMERA_OPEN_FAIL = 0x080c,

    /**
     *  雷达过热
     */
    RADAR_OVERHEATING = 0x0901,

    /**
     *  雷达自检失败
     */
    RADAR_SELF_CHECK_ERROR = 0x0902,

    /**
     *  雷达PLL异常
     */
    RADAR_PLL_ERROR = 0x0903,

    /**
     *  雷达基带DONE超时
     */
    RADAR_DONE_TIMEOUT = 0x0904,

    /**
     *  雷达通讯异常
     */
    RADAR_COMMUNICATION_ERROR = 0x0905,

    /**
     *  PPS信号异常
     */
    PPS_SIGNAL_ERROR = 0x0906,

    /**
     *  飞机未起飞无法打点
     */
    MISSION_MANAGER_ERROR = 0x0d01,

    /**
     *  角度异常
     */
    MISSION_MANAGER_ANGULAR_ANOMALY = 0x0d02,

    /**
     *  高度异常
     */
    MISSION_MANAGER_HEIGHT_ANOMALY = 0x0d03,

    /**
     *  飞向点在禁飞区
     */
    MISSION_MANAGER_FLY_TO_NOFLY_ZONE = 0x0d04,

    /**
     *  激光异常
     */
    MISSION_MANAGER_LASER_ANOMALY = 0x0d05,

    /**
     * MissionManager 收到 Notify 后 Copy Mission file 成功
     */
    MISSION_FILE_COPY_SUCCESS = 0x0d13,

    /**
     * MissionManager 收到 Notify 后 Copy Mission file 失败
     */
    MISSION_FILE_COPY_FAIL = 0x0d14,


    /**
     * 去普通航点过程中卡住，直接拍照
     * 告警等级：1 普通告警
     */
    STUCK_IN_WAYPOINT_PHOTO = 0x0D28,

    /**
     * 接近禁飞区，警示区告警
     * 告警等级：1 普通告警
     */
    APPROACHING_NO_FLY_ZONE_WARNING = 0x0D29,

    /**
     * 靠近禁飞区，缓冲区告警
     * 告警等级：2 紧急告警
     */
    NEAR_NO_FLY_ZONE_BUFFER_WARNING = 0x0D2A,

    /**
     * 飞机接近不可飞区告警
     * 告警等级：1 普通告警
     * 距离小于2km
     */
    AIRCRAFT_APPROACHING_NO_FLY_ZONE_WARNING = 0x0D2C,

    /**
     * 飞机位于不可飞区告警
     * 告警等级：2 紧急告警
     * 禁止起飞
     */
    AIRCRAFT_IN_NO_FLY_ZONE_WARNING = 0x0D2D,

    /**
     * 飞机返航告警
     * 告警等级：2 紧急告警
     * 飞机在不可飞区且已经起飞
     */
    AIRCRAFT_RETURN_TO_NO_FLY_ZONE_WARNING = 0x0D2E,

    /**
     * 飞机返航告警
     * 告警等级：1 普通告警
     * 飞机将飞离可飞区
     */
    AIRCRAFT_RETURN_FROM_NO_FLY_ZONE_WARNING = 0x0D2F,


    /**
     *  遭受射频干扰
     */
    RADIO_FREQUENCY_INTERFERENCE = 0x0a80,

    /**
     *  GPS遭受干扰
     */
    GPS_SUFFERS_INTERFERENCE = 0x0a81,

    /**
     *  任务飞行异常
     */
    MISSION_FLIGHT_ANOMALY = 0x0b06,

    /**
     *  飞控网关异常
     */
    FLIGHT_CONTROL_GATEWAY_ABNORMAL = 0x0b07,

    /**
     *  mif视觉定位失效
     */
    MIF_VISUAL_LOCALIZATION_FAILURE = 0x0b08,

    /** planner状态异常 = 相机挂掉,返航绕障失效
     *
     */
    EMM_EXIT_RETURN_HOME_OBS = 0x0D07,

    /**
     * 视觉点云异常， 手动避障系统异常
     */
    EMM_EXIT_SEMI_AUTO_OBS = 0x0D08,

    /**
     * 去雾告警
     */
    CAMERA_DEMIST = 0x0709,

    /**
     * 雷达未自标定
     */
    RADAR_NOT_CALIB = 0x0907,

    /**
     * 夜间无雷达避障
     */
    RADAR_NOT_NIGHT = 0x0D09,

    /**
     * 前视镜头有脏污
     */
    DIRTY_FRONT_LENS = 0x070A,

    /**
     * 后视镜头有脏污
     */
    DIRTY_REAR_LENS = 0x070B,

    /**
     * 上视镜头有脏污
     */
    DIRTY_UPPER_LENS = 0x070C,

    /**
     * 下视镜头有脏污
     */
    DIRTY_DOWN_LENS = 0x070D,

    /**
     * 飞机进入低功耗模式，红外关闭
     * 飞机停留2分钟后自动进入低功耗
     * 飞机进入低功耗模式，红外关闭
     * 提示：飞机已进入低功耗模式，红外关闭。起飞后将退出低功耗模式。
     * 告警等级：1 普通告警
     * 告警ID：0x078F
     */
    LOW_POWER_MODE_INFRARED_OFF = 0x078F,


    /**
     * 飞机RTK浮点解
     */
    RTK_NOT_FIX = 0x0451,

    /**
     * 遥控器需要校准
     */
    RC_CALIBRATION_REQUIRED = 0x00010000,

    /**
     * 右摇杆未居中
     */
    RC_RIGHT_ROCKER_EXCEPTION = 0x00010001,

    /**
     * 左摇杆未居中
     */
    RC_LEFT_ROCKER_EXCEPTION = 0x00010002,

    /**
     * 右拨轮未居中
     */
    RC_RIGHT_WHEEL_EXCEPTION = 0x00010003,

    /**
     * 左拨轮未居中
     */
    RC_LEFT_WHEEL_EXCEPTION = 0x00010004,

    /**
     * 电池充电过温
     */
    RC_BATTERY_TEMP_HOT = 0x00010005,

    /**
     * 电池不在位
     */
    BATTERY_NO_REIGN = 0x040F,

    /**
     * 1号机臂在位检测不通过
     */
    BOOM_NO_REIGN_1 = 0x0410,

    /**
     * 2号机臂在位检测不通过
     */
    BOOM_NO_REIGN_2 = 0x0411,

    /**
     * 3号机臂在位检测不通过
     */
    BOOM_NO_REIGN_3 = 0x0412,

    /**
     * 4号机臂在位检测不通过
     */
    BOOM_NO_REIGN_4 = 0x0413,

    /**
     * 无法解锁:电池在位检测不通过
     */
    //@Deprecated = "use BATTERY_NO_REIGN")
    BATTERY_NOT_IN_POSITION = 0x040F,

    /**
     * 无法解锁:1号机臂在位检测不通过
     */
    //@Deprecated = "BOOM_NO_REIGN_1")
    LEFT_HEAD_ARM_NOT_IN_POSITION = 0x0410,

    /**
     * 无法解锁:2号机臂在位检测不通过
     */
    //@Deprecated = "BOOM_NO_REIGN_2")
    RIGHT_HEAD_ARM_NOT_IN_POSITION = 0x0411,

    /**
     * 无法解锁:3号机臂在位检测不通过
     */
    //@Deprecated = "BOOM_NO_REIGN_3")
    LEFT_TAIL_ARM_NOT_IN_POSITION = 0x0412,

    /**
     * 无法解锁:4号机臂在位检测不通过
     */
    //@Deprecated = "BOOM_NO_REIGN_4")
    RIGHT_TAIL_ARM_NOT_IN_POSITION = 0x0413,

    /**
     * 无法解锁:电池未生效
     */
    BATTERY_IS_INVALID = 0x0418,

    /**
     * 无法解锁:电池数据异常
     */
    BATTERY_DATA_ABNORMAL = 0x0419,

    /**
     * 无法解锁:电池不匹配
     */
    BATTERY_NOT_MATCHED = 0x041A,

    /**
     * 无法解锁:RemoteID未生效
     */
    REMOTE_ID_INVALID = 0x041B,

    EMERGENCY_LANDING_MODE = 0x041C, // H/M:飞机进入3奖紧急降落模式 尽快在草丛上方降落

    /**
     * IMU 加热中
     */
    IMU_HEATING = 0x030A,

    /**
     * 机巢相关告警
     */
    MOTOR_POWER_UNUSUAL = 0X1001,//	电机电源异常
    STEER_POWER_UNUSUAL = 0X1002,//	舵机电源异常
    AIR_ONE_UNUSUAL = 0X2001,//	严重	空调1异常
    AIR_TWO_UNUSUAL = 0X2002,//	严重	空调2异常
    UP_TEMP_HUM_SENSOR_UNUSUAL = 0X2003,//  上舱温湿度传感器通讯异常
    DOWN_TEMP_HUM_SENSOR_UNUSUAL = 0X2004,//   下舱水浸传感器异常
    VIBRATE_SENSOR_UNUSUAL = 0X2005,//   //   振动传感器异常
    BACKUP_BATTERY_COMMUNICATE_UNUSUAL = 0X2006,//    备用电池通讯异常
    METEOROLOGICAL_STATION_UNUSUAL = 0X2007,//     气象站通讯异常
    CHARGE_MAIN_MODULE_UNUSUAL = 0X2008,//     充电主模块通讯异常
    CHARGE_VICE_MODULE_UNUSUAL = 0X2009,//        充电副模块通讯异常
    FAN_ONE_UNUSUAL = 0X200A,//      散热风扇1转速异常
    FAN_TWO_UNUSUAL = 0X200B,//     散热风扇2转速异常
    FAN_THREE_UNUSUAL = 0X200C,//    散热风扇3转速异常
    FAN_FOUR_UNUSUAL = 0X200D,//     散热风扇4转速异常
    AIR_ONE_FAN_FIVE_UNUSUAL = 0X200E,//   空调1风扇5转速异常
    AIR_ONE_FAN_SIX_UNUSUAL = 0X200F,//      空调1风扇6转速异常
    AIR_TWO_FAN_SEVEN_UNUSUAL = 0X2010,//     空调2风扇7转速异常
    AIR_TWO_FAN_EIGHT_UNUSUAL = 0X2011,//      空调2风扇8转速异常
    BATTERY_COMMUNICATE_UNUSUAL = 0X2012,//       机巢-飞机 电池通讯异常
    WATER_UNUSUAL = 0X2013,//    水浸告警
    VIBRATE_UNUSUAL = 0X2014,//   机巢异常振动告警
    LAND_LIGHT_UNUSUAL = 0X2015,//    着陆灯异常
    UPS_POWER_COMMUNICATE = 0X2016,//   UPS电源通讯异常
    UPS_POWER_UNUSUAL = 0X2017,//    UPS电源异常
    POWER_ADAPTER_COMMUNICATE_UNUSUAL = 0X2018,//   电源适配器通讯异常
    POWER_ADAPTER_UNUSUAL = 0X2019,//    电源适配器异常
    MOTOR_DRIVE_BOARD_COMMUNICATE_UNUSUAL = 0X201A,//    电机驱动板通讯失败
    MOTOR_DRIVE_BOARD_RESET_UNUSUAL = 0X201B,//    电机驱动板异常复位
    CABIN_OPEN_BLOCK = 0X3001,//   开门时舱门阻塞
    CABIN_CLOSE_BLOCK = 0X3002,//   关门时舱门阻塞
    CABIN_OPEN_UNUSUAL = 0X3003,//    开门异常
    CABIN_CLOSE_UNUSUAL = 0X3004,//    关门异常
    X_ROD_PULL_BLOCK = 0X3005,//   X杆归中时阻塞
    X_ROD_PUSH_BLOCK = 0X3006,//   X杆释放时阻塞
    X_ROD_PULL_UNUSUAL = 0X3007,//    X杆归中异常
    X_ROD_PUSH_UNUSUAL = 0X3008,//    X杆释放异常
    Y_ROD_PULL_BLOCK = 0X3009,//   Y杆归中时阻塞
    Y_ROD_PUSH_BLOCK = 0X300A,//   Y杆释放时阻塞
    Y_ROD_PULL_UNUSUAL = 0X300B,//    Y杆归中异常
    Y_ROD_PUSH_UNUSUAL = 0X300C,//    Y杆释放异常
    Z_ROD_PUSH_BLOCK = 0X300D,//       Z杆竖起异常
    Z_ROD_PULL_BLOCK = 0X300E,//       Z杆倒下异常
    LIMIT_SWITCH_UNUSUAL = 0X300F,//  限位开关异常
    CABIN_MOTOR_UNUSUAL = 0X3010,//    舱门电机异常
    X_ROD_MOTOR_UNUSUAL = 0X3011,//    X杆电机异常
    Y_ROD_MOTOR_UNUSUAL = 0X3012,//    Y杆电机异常
    Z_ROD_MOTOR_ONE_UNUSUAL = 0X3013,//   Z杆 = 拨桨杆)舵机1异常
    Z_ROD_MOTOR_TWO_UNUSUAL = 0X3014,//   Z杆 = 拨桨杆)舵机2异常
    Z_ROD_MOTOR_THREE_UNUSUAL = 0X3015,//   Z杆 = 拨桨杆)舵机3异常
    Z_ROD_MOTOR_FOUR_UNUSUAL = 0X3016,//   Z杆 = 拨桨杆)舵机4异常
    MOTOR_DRIVER_RESET = 0X3020,//	严重	电机驱动板复位	电机驱动板复位（看门狗复位，断电复位）

    CHARGE_OTC = 0X4001,//  充电过温
    CHARGE_UNDER_TEMP = 0X4002,//  充电欠温
    CHARGE_OVER_CURRENT = 0X4003,//    充电过流
    CHARGE_UNUSUAL = 0X4004,//   无人机充电异常
    U_BOARD_WRITE_READ_UNUSUAL = 0x5001,//   U盘读写异常
    WIFI_START_UNUSUAL = 0x5002,//   WIFI启动异常
    RTK_COMMUNICATE_UNUSUAL = 0x5003,//   RTK通信异常
    POWER_BOARD_COMMUNICATE = 0x5004,//    电源板通信异常
    GIGABIT_NETWORK_CARD_UNUSUAL = 0x5005,//   千兆网卡异常
    HUNDRED_NETWORK_CARD_UNUSUAL = 0x5006,//   百兆网卡异常
    SURVEILLANCE_CAMERA_UNUSUAL = 0x5007,//   监控摄像头异常 = 接百兆网卡)
    SYSTEM_REBOOT_UNUSUAL = 0x5008,//  系统异常重启
    SYSTEM_OVER_TEMP = 0x5009,//   系统温度过高
    SYSTEM_OVER_SPU = 0x5010,//   系统CPU负载过高
    SYSTEM_OVER_MEMORY_OCCUPY = 0x5011,//   系统内存占用过高
    SYSTEM_OVER_MEMORY_USE = 0x5012,//  系统存储空间使用过高
    APP_REBOOT_UNUSUAL = 0x5013,//  APK应用异常重启
    NETWORK_UNUSUAL = 0x5014,//    网络异常
    NEST_RADIO_FREQUENCY_INTERFERENCE = 0x5015,//  射频干扰
    TRANSMIT_CP_COMMUNICATE_UNUSUAL = 0x5016,//    图传CP通信异常
    NETWORK_DELAY_TOO_HIGH = 0x5017,//  空口网络延时过高
    VIDEO_CODE_FAILED = 0x6001,//  视频编解码异常
    DOWNLOAD_FAILED = 0X6002,//  从相机下载文件失败
    UPLOAD_FAILED = 0X6003,//  上传文件到指挥中心失败
    CAMERA_CONNECT_FAILED = 0X6004,//  巢外摄像头登录异常
    WEBRTC_CONNECT_FAILED = 0X6005,//  webrtc连接异常
    WARNING_AREA = 0x0D18,//飞机进入警示区
    ENHANCE_WARNING_AREA = 0x0D19,//飞入增强警示区
    SYSTEM_WARING_1881 = 0x0B09,//1881异常重启

    SYSTEM_MEMORY_INSUFFICIENT = 0x0b01, // 系统内存不足
    HIGH_CPU_LOAD = 0x0b02, // CPU负载过高
    LOW_DISK_IO_SPEED = 0x0b03, // 磁盘IO速率过低
    HIGH_CPU_TEMPERATURE = 0x0b04, // CPU温度过高
    CPU_SCHEDULING_EXCEPTION = 0x0b05, // CPU调度异常
    REMOTE_CONTROLLER_1881_REBOOT = 0x0b09, // 遥控器1881 异常重启
    REMOTE_CONTROLLER_1881_HIGH_CPU_TEMPERATURE = 0x0b0a, // 遥控器1881 CPU温度过高
    REMOTE_CONTROLLER_1881_HIGH_CPU_LOAD = 0x0b0b, // 遥控器1881 CPU负载过高
    REMOTE_CONTROLLER_1881_HIGH_MEMORY_USAGE = 0x0b0c, // 遥控器1881 内存使用过高


    //add 20131227
    //已有 BATTERY_NOT_IN_POSITION = 0x040F, //ModelH 电池在位检测不通过
    //已有 ARM1_NOT_IN_POSITION = 0x0410, //ModelH 1号机臂在位检测不通过
    //已有 ARM2_NOT_IN_POSITION = 0x0411, //ModelH 2号机臂在位检测不通过
    //已有 ARM3_NOT_IN_POSITION = 0x0412, //ModelH 3号机臂在位检测不通过
    //已有 ARM4_NOT_IN_POSITION = 0x0413, //ModelH 4号机臂在位检测不通过
    //已有 BATTERY_NOT_IN_EFFECT = 0x0418, //ModelH 电池未生效
    //已有 BATTERY_DATA_ERROR = 0x0419, //ModelH 电池数据异常
    //已有 BATTERY_MISMATCHED = 0x041A, //ModelH/M 电池不匹配
    //已有 REMOTE_ID_NOT_IN_EFFECT = 0x041B, //Model系列 RemoteID未生效
    //已有 IMU_NOT_REACH_SET_TEMPERATURE = 0x030A,//Model系列 IMU未达到预定温度
    //已有 ESC_BOARD_TEMP_TOO_HIGH = 0x030B, //Model系列 电调板温度过高
    //已有BATTERY_VOLTAGE_LOW = 0x010D, //Model系列 电池电芯电压低
    //已有 TAKEOFF_POWER_EXCESSIVE = 0x010E,//Model系列 起飞功率过大
    //已有 FLIGHT_POWER_EXCESSIVE = 0x010F,//Model系列 飞行功率过大

    //RTK天线未连接
    RTK1_ANTENNA_NOT_CONNECTED = 0x0414, //ModelH 1号RTK天线未连接
    RTK2_ANTENNA_NOT_CONNECTED = 0x0415, //ModelH 2号RTK天线未连接

    //RTK天线短路
    RTK1_ANTENNA_SHORT_CIRCUIT = 0x0416, //ModelH 1号RTK天线短路
    RTK2_ANTENNA_SHORT_CIRCUIT = 0x0417, //ModelH 2号RTK天线短路

    //电池寿命已达上限
    BATTERY_LF_LIFE_END = 0x0112,//Model H/M  H:左电池寿命已达上限 M:前电池寿命已达上限
    BATTERY_RB_LIFE_END = 0x0113,//Model H/M  H:右电池寿命已达上限 M:后电池寿命已达上限

    //电池温度偏高
    BATTERY_LF_TEMPERATURE_HIGH = 0x0116,//Model H/M  H:左电池温度偏高  M:前电池温度偏高
    BATTERY_RB_TEMPERATURE_HIGH = 0x0117,//Model H/M  H:右电池温度偏高  M:后电池温度偏高

    //电池温度过高
    BATTERY_LF_TEMPERATURE_TOO_HIGH = 0x0110,//Model H/M  H:左电池温度过高  M:前电池温度过高
    BATTERY_RB_TEMPERATURE_TOO_HIGH = 0x0111,//Model H/M  H:右电池温度过高  M:后电池温度过高

    //电池温度偏低
    BATTERY_LF_TEMPERATURE_LOW = 0x011A,//Model H/M  H:左电池温度偏低 M:前电池温度偏低
    BATTERY_RB_TEMPERATURE_LOW = 0x011B,//Model H/M  H:右电池温度偏低 M:后电池温度偏低

    //池温度过低
    BATTERY_LF_TEMPERATURE_TOO_LOW = 0x0114,//Model H/M  H:左电池温度过低 M:前电池温度过低
    BATTERY_RB_TEMPERATURE_TOO_LOW = 0x0115,//Model H/M  H:右电池温度过低 M:后电池温度过低

    //电池自动加热中
    BATTERY_LF_AUTO_HEATING = 0x0118,//Model H/M  H:左电池自动加热中 M:前电池自动加热中
    BATTERY_RB_AUTO_HEATING = 0x0119,//Model H/M  H:右电池自动加热中 M:后电池自动加热中

    //电池低温低电
    BATTERY_LF_LOW_TEMP_VOLTAGE = 0x011C,//Model H/M  H:左电池低温低电 M:前电池低温低电
    BATTERY_RB_LOW_TEMP_VOLTAGE = 0x011D,//Model H/M  H:右电池低温低电 M:后电池低温低电

    //电池压差过大
    BATTERY_LF_VOLTAGE_DIFF_LARGE = 0x011E,//Model H/M  H:左电池压差过大 M:前电池压差过大
    BATTERY_RB_VOLTAGE_DIFF_LARGE = 0x011F,//Model H/M  H:右电池压差过大 M:后电池压差过大

    //MissionManager
    MISSION_ALTITUDE_DISTANCE_EXCEED_MAX = 0x0544, //任务文件航点有超出限高限远

    MISSION_FLIGHT_DISTANCE_EXCEED_MAX = 0x0545,//任务文件航点总航程，超出作业能力范围

    MISSION_START_POSITION_TOO_FAR = 0x0546,//任务文件任务起点距离当前位置太远

    MISSION_FLIGHT_TIME_TOO_LONG = 0x0547,//任务文件任务作业总时长太长

    MISSION_FLY_CONTROL_NOT_RESPONSE = 0x0548,//飞控没有响应起飞指令

    MISSION_INVALID_LNG_LAT = 0x0549,//经纬度非法

    //飞控
    FLY_LOCK_MISSION_EXCEPTION = 0x041D, //无法解锁：飞行任务异常（MissionManager无心跳或者禁止解锁）

    FLY_LOCK_UOM_UNACTIVATED = 0x041E, // 无法解锁：UOM未激活（UOM未注册）

    DRONE_SHAKING_TOO_MUCH = 0x041F,  //飞机震动过大 = 结构异常或者动力平衡差异导致共振)

    //禁飞区
    NO_FLY_ZONE_WARNING = 0x0D6, //触发禁飞区，退出当前自动任务

    //MissionManager
    MISSION_EXIT_FOR_NFZ = 0X0D16,    //触发禁飞区，退出当前自动任务
    MISSION_KML_UNZIP_ERROR = 0x0D25, //kml任务文件解压失败
    MISSION_INVALID_GIMBAL_PITCH = 0x0D26,    //航线任务动作gimbal_pitch非法
    MISSION_STUCK_IN_FIRST_POINT = 0x0D27,    //去首个航点过程中卡住，直接返航
    EMM_MANUAL_FORMATION_ALT_TOO_LOW = 0x0D31, // 手动编队时控制高度不能低于30米
    MISSION_EXIT_FOR_NO_GPS = 0x051C, //无GPS退出航线任务
    MISSION_EXIT_FOR_NO_FILE = 0x051D,    //无任务文件退出航线任务
    MISSION_EXIT_FOR_FLY_POSITION_ERROR = 0x051E,   //获取飞控位姿消息失败，退出航线任务
    MISSION_EXIT_FOR_GPS_TO_NED = 0x051F,    //GPS转NED失败，退出航线任务
    MISSION_EXIT_FOR_PARSER_ERROR = 0x0520,  //解析任务文件失败，退出航线任务
    MISSION_EXIT_FOR_OPERATE_FILE_ERROR = 0x0521, //任务文件操作失败
    AUTO_LAND_FOR_GEO_BARRIER = 0x0534,    //超过地理围栏，自动降落
    MISSION_FILE_NOT_FOUND = 0x0540,    //没有找到对应的任务文件
    MISSION_FILE_PARSER_ERROR = 0x0541, //任务文件解析错误
    MISSION_FILE_GUID_ERROR = 0x0542,    //任务文件guid解析错误
    MISSION_WAYPOINT_IN_NFZ = 0x0543,     //任务文件航点在禁飞区或者限飞区
    CAMERA_LOW_POWER_WARN = 0x0825,     //相机低功耗告警
};

enum class TrackWorkState
{
    EXIT_FOLLOW = 0,//退出跟随
    CHECK_STATUS = 1,//检测状态
    TARGET_FOLLOW_STATUS = 2,//目标跟随状态(云台动，飞机不动)
    PLAN_FOLLOW_STATUS = 3,//规划跟随状态(云台动，飞机动)
    UNKNOWN = -1,
};

enum class AiServiceStatus
{
    UNKNOWN = 0, //无,没有启动
    AI_RECOGNITION = 1,//AI识别
    INTELLIGENT_TRACKING = 2,//智能跟踪
};

enum class BatteryInPlace
{
    UNREADY = 0,  // 未就绪，未工作
    READY,        // 已就绪
};

//蜂群任务状态
enum class SwarmManagerStatus
{
    WAIT_INIT = 0,       //初始状态，尚未进入蜂群任务模式
    WAIT_START = 1,      //已上传区域，等待开始
    TAKEOFF_RALLY = 2,   //起飞集结
    FLY_TO_AREA = 3,     //飞向区域
    EXPLORING = 4,       //区域搜索
    DROP_LOADING = 5,    //弃投准备返航
    RETURN_HOME = 6,     //返航
    FINISH = 7,          //结束
};

//飞机正常运行时，状态为0
//收到收桨指令后，状态变为1
//一次收桨流程结束后，接下来5s内会持续发送收桨结果(成功/失败)，然后就转为正常运行装态
enum class RetractPaddleStatus {
    NONE = 0,  //未处于收桨流程，正常工作状态
    INPROGRESS = 1,  //收桨进行中（正在执行收桨动作）
    SUCCESS = 2,  //收桨成功
    FAILED = 3,  //收桨失败
};

enum class LampLanguageCommandType {
    LampLanguageCommandUnknow = 0,
    GetLogLampLanguage = 1, //获取日志
    UpgradeServiceLampLanguage = 2, //升级服务
    DirectCtrlLampLanguage = 3, //直接控制机臂灯，控制类型见枚举 LAMPLNG_DIRECT_CTRL
};

enum class LamplngGetLogCmd {
    LamplngGetLogCommandStop = 0,     // 获取日志停止
    LamplngGetLogCommandStart = 1,    //获取日志开始
};

enum class LamplngUpgradeServiceCmd {
    LamplngUpgradeServiceClose = 0,    //关闭灯语
    LamplngUpgradeServiceStart = 1,    //升级开始
    LamplngUpgradeServiceSuccess = 2,  // 升级成功
    LamplngUpgradeServiceFailed = 3,   //升级失败
};

enum class LamplngDirectCtrl {
    LampngAllOff = 0,         //前后臂灯都关闭
    LampngFrontOffBackOn = 1, //前臂灯关,后臂灯开
    LampngFrontOnBackOff = 2, //前壁灯开,后臂灯关
    LampngAllOn = 3,          //前后臂灯都开
};

enum class EmRcStartHardwareState
{
    Disable = 0, // 关闭遥控器定频上报
    Enable = 1,  // 开启遥控器定频上报
};

} // namespace AutelMobileSdk

#endif
