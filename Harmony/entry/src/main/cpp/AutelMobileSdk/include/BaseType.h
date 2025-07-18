#ifndef BASE_TYPE_H
#define BASE_TYPE_H

#include <cstdint>

namespace AutelMobileSdk
{
enum class SdkModule
{
    Linkage = 0,
    Protocol,
    SdkManagement,
    DeviceManagement,
    KeyManagement,
    RtkManagement,
    FlightMisson,
    FileService,
    MediaPlayer,
    Gimbal,
    DataStorage,
    Authority,
    Camera,
    App,
    Api,
    Networking,
    MaxNum,
};

enum class DeviceType
{
    WifiDev = 0,
    UsbHostDev = 1,
    RemoterDev = 3,        // 摇控器
    DroneDev = 4,          // 飞机
    NestDev = 5,           // 机巢设备
    UsbAccessoryDev = 5,
    SwitchMode = 6,        // 切换遥控器模式
    UnknownDev = 0xff,
};

enum class ComponentType
{
    Unknown = 0,             // 未知
    Common = 1,              // 通用接口
    Mission = 2,             // 飞行任务管理
    AiService = 3,           // AI
    Camera = 4,              // 相机
    RadarVisionFusion = 5,   // radar vision fusion
    FlightController = 6,    // 飞行控制
    FlightParams = 7,        // 飞行参数读取和设置
    Battery = 8,             // 电池
    Gimbal = 9,              // 云台
    Vision = 10,             // 视觉
    RemoteController = 11,   // 摇控器
    Alink = 12,              // Alink 图传频段
    RemoteId = 13,           // remoteID
    Nest = 14,               // 机巢
    SystemManager = 17,      // SystemManager
    MissionManager = 19,     // MissionManager
    AccessoriesProxy = 20,   // Accessories proxy
    RtkProxy = 21,           // RTK proxy
    RadarProxy = 22,         // Radar
    NtripProxy = 23,         // Ntrip
    Lte_Module = 24,         // 4G/5G模组
    Mqtt = 25,               // MQTT
    UtmissProperty = 26,     // utmiss
    RtmpProxy = 27,          // Rtmp
    CommandCenterProxy = 28, // 指挥中心
    WifiProxy = 29,          // WIFI
    SecurityData = 31,       // 安全数据
    Payload = 32,            // 荷载
    UpgradeService = 1000,   // 升级服务
    CloudApi = 1550,         // 上云API
    // 上云API componentID: 1550~1559
    // CloudApiDrone = 1550, //飞机端上云API
    // CloudApiRc = 1551,    //遥控端上云API
    CloudApiNest = 1552,     // 机巢端上云API
    Rtc = 1560,              // RTC
    RcAtService = 1600,      // 遥控器ATService
    RcHidden = 9999,         // 遥控器
};

enum class AuthorityState
{
    Disable = -1,
    Restricted = 0,
    Normal = 1,
};

enum class TimeMode
{
    // UTC全称为Coordinated Universal Time世界协调时，是一个时间体系。
    // GMT全称为Greenwich Mean Time格林尼治平太阳时间，可以指一个时区。
    // GMT的计算是基于地球自转，一个周期约为86, 400.002秒，它随着地球自转周期的变化而变化。
    // UTC基于SI标准的原子时间，一个周期为精确的86, 400.00秒，由于潮汐力等因素，地球自转周期在慢慢变长，当差别到±0.9秒时，就把协调世界时向前拨1秒或向后拨1秒这样就和GMT时间（地球自转）相同了。
    // 东八区表示为UTC + 8全球通用，英联邦国家则更倾向于使用GMT + 8。因此，UTC更为标准，在科学和工程中换算时间也是用UTC系统。

    LOCAL_TIME = 0,
    UTC_TIME,
    GMT_TIME,
};

enum class FilePathType
{
    UNKNOWN = 0,
    AUTEL_FTP_PATH,
    AUTEL_ABSOLUTE_FTP_PATH,
};

// 文件类型
enum class FileType
{
    OTA = 0,                      // 升级文件
    ELEVATION = 1,                // 高程文件
    FIXED_NO_FLY_ZONE = 2,        // 固定禁飞区域
    TEMP_NO_FLY_ZONE = 3,         // 临时禁飞区域
    AUTHORIZED_ZONE = 4,          // 授权区文件
    ELECTRIC_BARRIER = 5,         // 电子围栏
    MISSION = 6,                  // 任务文件
    ALBUM = 7,                    // 相册文件
    MISSION_AUDIO = 8,            // 喊话器文件
    UNKNOWN = -1,
};

enum class VideoType
{
    VISIBLE_LIGHT_WIDE_ANGLE = 0,       // 可见光广角/变焦
    VISIBLE_LIGHT_LONG_ZOOM,            // 可见光长焦
    THERMAL_VISION,                     // 红外
    NIGHT_VISION,                       // 夜视
};

enum class MediaSourceType
{
    FILE = 0,
    URL_RTSP,
    URL_RTMP,
    URL_RTP,
    URL_HTTP,
    URL_HTTPS,
    STREAM,
    UNKNOWN,
};

enum class TransmitProtoType
{
    Tcp = 0,
    Udp = 1,
};

enum class VideoDisplayMode
{
    STRETCH = 0,
    KEEP_WIDTH_HEIGHT_RATIO,
};

enum SDKErrorType
{
    UNKNOWN = 0,
    INTERFACE_ERROR,
    DEVICE_ONLINE_OFFLINE_ABNORMAL,
    VIDEO_STREAM_ABNORMAL,
};

enum class RcOperateMode
{
    AMERICA_HAND = 0,
    CHINESE_HAND,
    JAPANESE_HAND,
};

enum class PlayState
{
    STOP,
    PAUSE,
    PLAYING,
    FINISH
};

enum class UavComponentType
{
  COMPONENT_ID_UNKNOW = 0,
  COMPONENT_ID_DISCOVERY = 1,
  COMPONENT_ID_HANDSHAKE = 2,
  COMPONENT_ID_ACCESS = 3,
  COMPONENT_ID_SYSTEM = 4,
  COMPONENT_ID_CHANNEL = 5,
  COMPONENT_ID_FACTORY = 6,
  COMPONENT_ID_STREAM = 7,
  COMPONENT_ID_TIMESYNC = 8,
  COMPONENT_ID_POWER = 101,
  COMPONENT_ID_LOGGER = 102,
  COMPONENT_ID_UPGRADE = 103,
  COMPONENT_ID_PAYLOAD_CAMERA = 104,
  COMPONENT_ID_PAYLOAD_GIMBAL = 105,
  COMPONENT_ID_SDK_SUB = 201,
  COMPONENT_ID_SMC = 202,
  COMPONENT_ID_FLY_CONTROL_SERVICE = 203,
  COMPONENT_ID_UAV_WARNING = 204,
  COMPONENT_ID_POSITION = 205,
  COMPONENT_ID_WAYPOINT = 206,
  COMPONENT_ID_PAYLOAD_BDS_GPS = 207,
};

using DisplayWinHandle = void*;
const unsigned int INVALID_DEVICE_ID = 0xffffffff;
using ObjectId = unsigned int;
using DeviceId = unsigned int;
}

#endif
