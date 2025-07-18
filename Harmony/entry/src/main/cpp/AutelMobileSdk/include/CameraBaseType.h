#ifndef CAMERA_BASE_TYPE_H
#define CAMERA_BASE_TYPE_H

namespace AutelMobileSdk
{
enum class LensType
{
    Zoom = 0,        // 变焦
    Thermal,         // 红外
    WideAngle,       // 广角
    TeleZoom,        // 长焦
    TeleThermal,     // 红外焦
    NightVision,     // 夜视
    Visible,
    Telephoto,
};

enum class FlightMode
{
    Manual = 0,
    Task,
};

enum class RecordMode
{
    Unknown = 0xff,
    Standard = 0,
    SlowMotion = 1,       // 慢动作
    UltraPixel = 2,       // 超感光
    HDR = 3,
    LinkedZoom = 4,
    SuperNightVideo = 5,  // 超级夜视
};

enum class GimbalType
{
    XL802,
    XL801,
    XL811,
    XL821,
    XL822,
    XL705,
    XL709,
    XL715,
    XL716,
    XL730,
    XL732,
    XL753,
    Unknown = 0xff,
};

// 相机的界面模式
enum class CameraPattern
{
    ManualFlight = 0,         // 手动飞行
    MissionFlight = 1,        // 任务飞行
    IntelligentTracking = 2,  // 智能跟踪=和手势识别,指点飞行
    TimeLapse = 3,            // 延时摄影
    SurroundingFlight = 4,    // 环绕飞行
    Panorama = 5,             // 全景拍照
    MissionRecord = 6,        // 任务录制
    MissionPolice = 7,        // 交警项目
    LowPower = 8,             // 低功耗
    ShortVideo = 9,           // 短片模式
    Portrait = 10,            // 人像模式
    Night = 11,               // 夜景模式
    Major = 12,               // 专业模式
    Unknown = -1,
};

// 光圈大小
enum class Lris
{
    Lris_1_8 = 0,
    Lris_2_0 = 1,
    Lris_2_2 = 2,
    Lris_2_5 = 3,
    Lris_2_8 = 4,
    Lris_3_2 = 5,
    Lris_3_5 = 6,
    Lris_4_0 = 7,
    Lris_4_5 = 8,
    Lris_5_0 = 9,
    Lris_5_6 = 10,
    Lris_6_3 = 11,
    Lris_7_1 = 12,
    Lris_8_0 = 13,
    Lris_9_0 = 14,
    Lris_10 = 15,
    Lris_11 = 16,
};

// 边拍边录
enum class VideoPiv
{
    Time_3s = 3,
    Time_5s = 5,
    Time_10s = 10,
    Time_30s = 30,
    Time_60s = 60,
};

// 快门速度
enum class ShutterSpeed
{
    ShutterSpeed_30S = 0,
    ShutterSpeed_25S,
    ShutterSpeed_20S,
    ShutterSpeed_15S,
    ShutterSpeed_13S,
    ShutterSpeed_10S,
    ShutterSpeed_9S,
    ShutterSpeed_8S,
    ShutterSpeed_6S,
    ShutterSpeed_5S,
    ShutterSpeed_4S,
    ShutterSpeed_3P2S,  // 3.2s
    ShutterSpeed_3S,
    ShutterSpeed_2P5S,
    ShutterSpeed_2S,
    ShutterSpeed_1P6S,
    ShutterSpeed_1P3S,
    ShutterSpeed_1S,
    ShutterSpeed_1P25,
    ShutterSpeed_1P67,
    ShutterSpeed_1_2,   // 1/2
    ShutterSpeed_2P5,
    ShutterSpeed_1_3,
    ShutterSpeed_1_4,
    ShutterSpeed_1_5,
    ShutterSpeed_1_6P25,  // 1/6.25
    ShutterSpeed_1_8,
    ShutterSpeed_1_10,
    ShutterSpeed_1_12P5,
    ShutterSpeed_1_15,
    ShutterSpeed_1_20,
    ShutterSpeed_1_24,
    ShutterSpeed_1_25,
    ShutterSpeed_1_30,
    ShutterSpeed_1_40,
    ShutterSpeed_1_48,
    ShutterSpeed_1_50,
    ShutterSpeed_1_60,
    ShutterSpeed_1_80,
    ShutterSpeed_1_100,
    ShutterSpeed_1_120,
    ShutterSpeed_1_160,
    ShutterSpeed_1_200,
    ShutterSpeed_1_240,
    ShutterSpeed_1_320,
    ShutterSpeed_1_400,
    ShutterSpeed_1_500,
    ShutterSpeed_1_640,
    ShutterSpeed_1_800,
    ShutterSpeed_1_1000,
    ShutterSpeed_1_1200,
    ShutterSpeed_1_1250,
    ShutterSpeed_1_1600,
    ShutterSpeed_1_2000,
    ShutterSpeed_1_2400,
    ShutterSpeed_1_2500,
    ShutterSpeed_1_3200,
    ShutterSpeed_1_4000,
    ShutterSpeed_1_5000,
    ShutterSpeed_1_6000,
    ShutterSpeed_1_8000,
    ShutterSpeed_1_10000,
    ShutterSpeed_Unknow,
};

// 相机工作模式
enum class CameraMode
{
    Single = 0,              // 单拍
    Record = 1,              // 录像
    Burst = 2,               // 连拍  3/5  = 默认3张
    Timelapse = 3,           // 延时，定时拍
    Aeb = 4,                 // 自动曝光 3/5  = 默认3张
    Panorama = 5,            // 全景模式
    SlowMotionRecord = 6,    // 慢动作录影
    RecordVideoLooping = 7,  // 循环录影
    MotionDelayShot = 8,     // 移动延时摄影
    Hdr = 9,                 // hdr
    Mfnr = 10,               // 纯净夜拍
    Unknown = 0xff,
};

// 相机曝光模式
enum class ExposureMode
{
    Auto = 0,     // 自动曝光模式
    Shutter = 1,  // 快门优先模式（x008\xb012相机不支持）
    Aperture = 2, // 光圈优先模式 =xb012相机不支持
    Manual = 3,   // 手动曝光模式
};

// 相机曝光补偿值
enum class ExposureCompensation
{
    N30,  // 相机曝光补偿值为 -3.0ev。
    N27,  // 相机曝光补偿值为 -2.7ev。
    N23,  // 相机曝光补偿值为 -2.3ev
    N20,  // 相机曝光补偿值为 -2.0ev。
    N17,  // 相机曝光补偿值为 -1.7ev。
    N13,  // 相机曝光补偿值为 -1.3ev。
    N10,  // 相机曝光补偿值为 -1.0ev。
    N07,  // 相机曝光补偿值为 -0.7ev。
    N03,  // 相机曝光补偿值为 -0.3ev。
    N00,  // 相机曝光补偿值为 0.0ev。
    P03,  // 相机曝光补偿值为 +0.3ev。
    P07,  // 相机曝光补偿值为 +0.7ev。
    P10,  // 相机曝光补偿值为 +1.0ev。
    P13,  // 相机曝光补偿值为 +1.3ev。
    P17,  // 相机曝光补偿值为 +1.7ev。
    P20,  // 相机曝光补偿值为 +2.0ev。
    P23,  // 相机曝光补偿值为 +2.3ev。
    P27,  // 相机曝光补偿值为 +2.7ev。
    P30,  //相机曝光补偿值为 +3.0ev。
};

// 感光度可选值
enum class ImageISO
{
    ISO_100 = 100,
    ISO_200 = 200,
    ISO_400 = 400,
    ISO_800 = 800,
    ISO_1600 = 1600,
    ISO_2400 = 2400,
    ISO_3200 = 3200,
    ISO_4800 = 4800,
    ISO_6400 = 6400,
    ISO_12800 = 12800,
    ISO_17200 = 17200,
    ISO_21600 = 21600,
    ISO_25600 = 25600,
    ISO_30400 = 30400,
    ISO_34800 = 34800,
    ISO_39600 = 39600,
    ISO_44000 = 44000,
    ISO_48000 = 48000,
    ISO_52000 = 52000,
    ISO_56000 = 56000,
    ISO_60000 = 60000,
    ISO_64000 = 64000,
    ISO_Unkown = -1,
};

// ISO感光度选择模式
enum class IsoMode
{
    Auto = 0,
    Manual = 1
};

// 追踪目标
enum class SmartTrackTarget
{
    Background = 0,    // 背景
    Animal = 1,        // 动物
    Boat = 2,          // 船只
    Car = 3,           // 小汽车
    Person = 4,        // 人
    Rider = 5,         // 骑手
    LargeVehicle = 6,  // 大卡
    Bbox = 7,          // 盒子
    Bike = 8,          // 自行车
    Motorcycle = 9,    // 摩托车
    FourWheeler = 10,  // 四轮车
    Uav = 11,          // 无人机
};

// 热成像辐射天气条件目标
enum class ThermalSkyCondition
{
    Clear = 0,     // 清澈
    Scattered = 1, // 疏云
    Cloudy = 2,    // 多云
};

// 热成像辐射温度单位
enum class ThermalTemperatureUnit
{
    Centigrade = 0, //摄氏度
    Fahrenheit = 1, //华氏度
};

// LED状态
enum class ThermalLedState
{
    Off = 0, // 关闭
    On = 1,  // 打开
};

// 画中画位置
enum class PipPosition
{
    LeftUp = 0,      // 画中画在左上角
    MiddleUp = 0,    // 画中画在顶部中间
    RightUp = 0,     // 画中画在右上角
    LeftMiddle = 0,  // 画中画在左边中间
    Central = 0,     // 画中画在正中
    RightMiddle = 0, // 画中画在右边中间
    LeftDown = 0,    // 画中画在左下角
    MiddleDown = 0,  // 画中画在底部中间
    RightDown = 1,   // 画中画在右下角
};

// 红外视频存储
enum class ThermalVideoSaveMode
{
    Visible = 0,                  //保存可见光的视频
    InfraredRadiation = 1,        //保存红外辐射视频
    InfraredRadiationVisible = 2, //同时保存红外辐射视频和可见光视频
};

// 热成像伪彩信息
enum class ThermalColor
{
    WhiteHot = 0,        // 白热
    BlackHot = 1,        // 冷热
    RainBow = 2,         // 彩虹
    RainHc = 3,          // 增强彩虹
    IronBow = 4,         // 铁红
    Lava = 5,            // 熔岩
    Arctic = 6,          // 极光
    GlowBow = 7,         // 灼热
    GradedFire = 8,      // 渐变
    HotTest = 9,         // 热探测
    DoubleRainbow = 10,  // 双彩虹
    ColorWheel = 11,     // 色环
    Unknown = -1
};

// 热成像色表
enum class ThermalPalette
{
    HotMetal = 0,
    WhiteHot = 0,
    Rainbow = 1,
};

// 视频格式
enum class VideoFormat
{
    Mov = 0,
    Mp4 = 1,
    Tiff = 2,
    Unknown = 0xff,
};

// 照片格式
enum class PhotoFormat
{
    Jpg = 0,
    Dng = 1,
    Jpgdng = 2,
    Rjpeg = 3,
    Rjpegtiff = 4,
    Unknown = 0xff,
};

// 显示模式
enum class DisplayMode
{
    Visible = 0,     // 可见光
    Picture = 1,     // 画中画
    Infrared = 2,    // 红外
    Overlap = 3,     // 融合
    Unknown = 0xff,
};

// 视频压缩格式
enum class VideoCompressStandard
{
    H264 = 0,
    H265 = 1,
    UNKNOWN = 0xff,
};

// 存储类型
enum class StorageType
{
    SdCard = 0,
    Emmc = 1,
    Unknown = 0xff,
};

enum class PhotoResolutionType
{
    PR_8000_6000,   // 8000x6000
    PR_6912_5184,
    PR_4000_3000,
    PR_1920_1200,
    PR_1920_1080,
    PR_4096_3072,
    PR_8192_6144,
    PR_640_512,
    PR_3840_2160,
    PR_5472_3648,
    PR_5472_3076,
    PR_UNKNOWN,
};

enum class VideoResolutionType
{
    VR_4000_3000 = 0,  // 12M, 4000x3000
    VR_1920_1200,      // 1200p, 1920x1200
    VR_1920_1080,      // 1080p, 1920x1080
    VR_7680_4320,      // 8K, 7680x4320
    VR_3840_2160,      // 4K, 3840x2160
    VR_640_512,        // 640*512, 640x512
    VR_UNKNOWN,
};

enum class TakePhotoMode
{
    Unknown = 0xff,
    Single = 0,       // 单拍
    Bust = 1,         // 连拍
    Interval = 2,     // 定时拍
    AEB = 3,          // AEB
    Hypersen = 4,     // 夜景
    Panorama = 5,     // 全景
    Matrix = 6,       // 超清矩阵
    HDR = 7,
    LinkedZoom = 8,
    NightShot = 9,
};

enum class VideoZoomType
{
    Default = 0,
    VR_8K_25 = 1,          // VR_8K_7680_4320
    SuperNightVideo = 2,   // 夜视
};

enum class VideoStandard
{
    PAL = 0,
    NTSC = 1,
    Unknown = 0xff,
};
//白平衡模式
enum class WhiteBalance
{
    Auto = 0,
    Sunny = 1,         // 日光
    Cloudy = 2,        // 阴天
    Incandescent = 3,  // 白炽灯
    Fluorescent = 4,   // 荧光灯
    Custom = 5,        // 自定义 自定义 色温，mode设置为custom时有效，范围 2000 - 10000，步长为 100
    Unknown = 0xff,
};

enum class DefogMode
{
    Close = 0,
    Open = 1,
    Max
};

enum class Defog
{
    Close = 0,
    Low = 1,
    Mid = 2,
    High = 3,
};

enum class VideoTransMissionMode
{
    LowLatency = 1,    // 流畅
    HighQuality = 2,   // 高清
    Super = 3,         // 2.7k 超高清 Super
    Unknown = 255,
};

enum class IRTempMode
{
    TempModeNone = 0,      // ⽆
    TempModeCenter = 1,    // 中⼼测温
    TempModeHot = 2,       // 热测温
    TempModeCold = 3,      // 冷测温
    TempModeTouch = 4,     // 点击位置测温
    TempModeRegion = 5,    // 区域测温
    TempModeTrack = 6,     // 跟踪测温
    TempModeUser1 = 7,     // ⽤户1测温
    TempModeUser2 = 8,     // ⽤户2测温
};

enum class CameraSystemState
{
    Idle = 0,
    Recording = 1,    // 正在录像
    TakingPhoto = 2,  // 正在拍照
    Unready = 3,      // 相机不可用
    Unknown = 0xff,
};

enum class CameraWorkMode
{
    Record = 0,      // 录像
    Photo = 1,       // 拍照
    Unknown = 0xff,
};

enum class ThermalImageMode
{
    MANUAL = 0,
    AUTO1 = 1,
    AUTO2 = 2,
    UNKNOWN = 0xFF,
};

enum class TemperatureMode
{
    NONE = 0,        // 无           
    CENTER = 1,      // 中心测温     
    HOT = 2,         // 热测温       
    COLD = 3,        // 冷测温       
    TOUCH = 4,       // 点击位置测温 
    REGION = 5,      // 区域测温     
    TRACK = 6,       // 跟踪测温     
    USER1 = 7,       // 用户1测温    
    USER2 = 8,       // 用户2测温    
    UNKNOWN = 0xFF,
};

enum class CameraEncrypt
{
    CLOSE = 0,
    OPEN = 1,
    ALL = 2,
};

enum class ApertureMode
{
    AUTO = 0,
    MANUAL = 1,
};

enum class ShutterMode
{
    AUTO = 0,
    MANUAL = 1,
};

enum class TakePhotoStatus
{
    START = 0,
    END = 1,
    UNKNOWN = 0xff,
};
//录像状态
enum class RecordStatus
{
    UNKNOWN = 0xff,
    START = 0,//开始
    RECORDING = 1,//正在录像
    END = 2,//结束录像
};

enum class RecordVideoFile
{
    UNKNOWN = 0,
    SUCCESS = 1,
    WRITE_ERROR = 2,
    BUFFER_FULL = 3,
    NO_SPACE = 4,
    NOT_SUPPORT = 5,
    SD_REMOVE = 6,
    SPLIT = 7,
    OTHER_FAILED = 8,
};

enum class PanoramaShootStatus
{
    UNKNOWN = 0,
    STOP = 1,
    SHOOTING = 2,
    JOINING = 3,
};

enum class Panorama
{
    HORIZONTAL = 1,
    VERTICAL = 2,
    WIDE_ANGLE = 3,
    SPHERICAL = 4,
};

enum class CameraAfAe
{
    UNKNOWN = 0,
    CENTER = 1,
    SPOT = 2,
};

enum class Temperature
{
    HOT = 0,
    COLD = 1,
};

enum class MotionDelayShoot
{
    UNKNOWN = 0,
    STOP = 1,
    PAUSE = 2,
    TAKING = 3,
    JOINING = 4,
};
//拍照曝光
enum class Exposure
{
    OVEREXPOSURE = 0,//过曝
    UNDEREXPOSURE = 1,//欠曝
};
//AF对焦状态
enum class AFStateEnum
{
    FOCUS_START = 0,//开始对焦
    FOCUSING = 1,//对焦中
    FOCUS_COMPLETE = 2,//对焦完成
};

enum class CardStatus
{
    READY = 0,
    ERROR = 1,
    LOW_SPEED = 2,
    PROTECTED = 3,
    FULL = 4,
    NO_CARD = 5,
    UNKNOWN_FILESYSTEM = 6,
    LOOP_RECORD_LACK_OF_SPACE = 7,
    FORMATTING = 8,
    FORMAT_FAIL = 9,
    FORMAT_SUCCESS = 10,
    UNKNOWN = 0XFF,
};

enum class FocusMode
{
    AF = 1,
    MF = 2,
    UNKNOWN = 0xff,
};

enum class AFLensFocusMode
{
    AVERAGE = 0,
    CENTER = 1,
    SPOT = 2,
    UNKNOWN = 0xff,
};

enum class CameraPreviewResolution
{
    H480 = 0,            // 预览图尺寸为 640x480
    H720 = 1,            // 预览图尺寸为 960x720
    H1080 = 2,           // 预览图尺寸为 1440x1080
    UNKNOWN = 0xFF,
};

enum class ThermalColorEnum
{
    WHITE_HOT = 0,      // 白热
    BLACK_HOT = 1,      // 冷热
    RAINBOW = 2,        // 彩虹
    RAIN_HC = 3,        // 增强彩虹
    IRON_BOW = 4,       // 铁红
    LAVA = 5,           // 溶岩
    ARCTIC = 6,         // 极光
    GLOW_BOW = 7,       // 灼热
    GRADED_FIRE = 8,    // 渐变
    HOTTEST = 9,        // 热探测
    //    DOUBLE_RAINBOW = 11,// 双彩虹
    //    COLOR_RING = 12,// 色环
    UNKNOWN = 0xFF,
};

enum class IsothermEnum
{
    CLOSE = 0,          // 关闭
    PEOPLE = 1,         // 搜人
    FIRE = 2,           // 搜火
    CUSTOMIZE = 3,      // 自定义
    UNKNOWN = 0xFF,
};

enum class ThermalGainEnum
{
    HIGH = 0,           // 高增益
    LOW = 1,            // 低增益
    AUTO = 2,           // 自动
    UNKNOWN = 0xFF,
};

enum class PhotoFormatEnum
{
    JPG = 0,
    DNG = 1,
    JPGDNG = 2,
    RJPEG = 3,
    RJPEGTIFF = 4,
    UNKNOWN = 0xFF,
};

enum class VideoFormatEnum
{
    MOV = 0,            // video format defines MOV
    MP4 = 1,            // video format defines MP4
    TIFF = 2,           // video format defines TIFF
    UNKNOWN = 0xFF,
};

enum class AntiflickerEnum
{
    AUTO = 0,               // 自动
    FIFTY_HZ = 1,           // 50hz
    SIXTY_HZ = 2,            // 60hz
    CLOSE = 3,              // 关闭
    UNKNOWN = 0xFF,         // 未知
};

enum class CameraWorkModeEnum
{
    RECORD = 0,         // 录像
    PHOTO = 1,          // 拍照
    UNKNOWN = 0xFF,
};

enum class TakePhotoModeEnum
{
    UNKNOWN = 0xFF,
    SINGLE = 0,             // 单拍
    BUST = 1,               // 连拍
    INTERVAL = 2,           // 定时拍
    AEB = 3,                // AEB
    HYPERSEN = 4,           // 夜景
    PANORAMA = 5,           // 全景
    MATRIX = 6,             // 超清矩阵
    HDR = 7,                // HDR  为了获取HDR下支持的模式
    LinkedZoom = 8,         // LinkedZoom  为了获取LinkedZoom下支持的模式
    NightShot = 9,          // NightShot  为了获取NightShot下支持的模式
};

enum class RecordModeEnum
{
    UNKNOWN = 0xFF,
    STANDARD = 0,               // 标准
    SLOW_MOTION = 1,            // 慢动作
    ULTRA_PIXEL = 2,            // 超感光
    HDR = 3,                    // HDR  为了获取HDR下支持的模式
    LinkedZoom = 4,             // LinkedZoom  为了获取LinkedZoom下支持的模式
    SuperNightVideo = 5,        // 超级夜视
};

enum class ImageStyleEnum
{
    STANDARD = 0,           // 标准
    CUSTOM = 1,             // 自定义
    LANDSCAPE = 2,          // 风光
    SOFT = 3,               // 中性
    FAIR = 4,               // 白皙
    CONTRAST = 5,           // 反差色
    JAPAN = 6,              // 日系
    MOISTURE = 7,           // 水嫩
    FRESH = 8,              // 清新
    GOLDVIBES = 9,          // 黑金
    GOLDVIBES03 = 10,       // 黑金03
    GOLDVIBES04 = 11,       // 黑金04
    GOLDVIBES05 = 12,       // 黑金05
    BW = 13,                // 黑白
    NOSTALGIC = 14,         // 怀旧
    NATUREJ = 15,           // 人像自然J
    HKMOVIE01 = 16,         // 港风电影01
    ANTIAUITY01 = 17,       // 古风01
    BRIGHT = 18,            // 明亮
    CLASSICLUT = 19,        // 经典LUT
    UNKNOWN = 0xFF,
};

enum class WhiteBalanceEnum
{
    AUTO = 0,               // 自动
    SUNNY = 1,              // 日光
    CLOUDY = 2,             // 阴天
    INCANDESCENT = 3,       // 白炽灯
    FLUORESCENT = 4,        // 荧光灯
    CUSTOM = 5,             // 自定义 自定义 色温，Mode设置为Custom时有效，范围 2000 - 10000，步长为 100
    UNKNOWN = 0xFF,
};

enum class DefogEnum
{
    DEFOG_CLOSE = 0,    // 关
    DEFOG_LOW = 1,      // 弱
    DEFOG_MID = 2,      // 中
    DEFOG_HIGH = 3,     // 强
};

enum class FocusModeEnum
{
    AF = 1,
    MF = 2,
    UNKNOWN = 0xFF,
};

enum class AFLensFocusModeEnum
{
    AVERAGE = 0,    // 平均对焦
    CENTER = 1,     // 中心对焦
    SPOT = 2,
    UNKNOWN = 0xFF, // 点对焦
};

enum class CameraGearEnum
{
    AUTO = 0,
    MANUAL,
    SHUTTER_PRIORITY,
    APERTURE_PRIORITY,
    UNKNOWN,
};

enum class GimbalRotateDirectionEnum
{
    CLOCKWISE = 0,
    COUNTER_CLOCKWISE = 1,
};

enum class ImageColorEnum
{
    NONE = 0,
    LOG,
    VIVID,
    BLACK_WHITE,
    ART,
    FILM,
    BEACH,
    DREAM,
    CLASSIC,
    NOSTALGIC,
    UNKNOWN,
};

enum class ShutterModeEnum
{
    AUTO = 0,
    MANUAL,
};

enum class ApertureModeEnum
{
    AUTO = 0,
    MANUAL,
};

enum class PatternModeEnum
{
    MANUAL = 0,
    MISSION_FLY,
    DELAY_SHOOT,
    VISION_ORBIT,
    PANORAMIC,
    MISSION_RECORDER,
    UNKNOWN,
};

enum class ISOModeEnum
{
    AUTO = 0,
    MANUAL = 1,
};
}

#endif
