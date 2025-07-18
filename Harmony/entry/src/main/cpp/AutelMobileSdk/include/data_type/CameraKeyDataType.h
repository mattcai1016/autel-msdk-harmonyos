#ifndef CAMERA_KEY_DATA_TYPE_H
#define CAMERA_KEY_DATA_TYPE_H

#include <vector>
#include <list>
#include <string>
#include <cstdint>
#include "CameraBaseType.h"
#include "Common.h"

namespace AutelMobileSdk
{
//存储状态
enum class CardStatusEnum
{
    READY = 0,
    ERROR,
    LOW_SPEED,
    PROTECTED,
    FULL,
    NO_CARD,
    UNKNOWN_FILESYSTEM,
    LOOP_RECORD_LACK_OF_SPACE,
    FORMATTING,
    FORMAT_FAIL,
    FORMAT_SUCCESS,
    UNKNOWN,
};

enum class VideoCompressProfileEnum
{
    LINE = 0,
    MAIN,
    UNKNOWN,
};
enum class VideoBitrateEnum
{
    VBR = 0,
    CBR,
    UNKNOWN,
};
enum class VideoStandardEnum
{
    PAL = 0,
    NTSC,
    UNKNOWN,
};
enum class ResistanceBlinkEnum
{
    AUTO = 0,
    TYPE_50HZ,
    TYPE_60HZ,
    CLOSE,
    UNKNOWN,
};

enum class WorkMode
{
    RECORD = 0,
    PHOTO = 1,
    UNKNOWN = 0xff,
};

//镜头信息
struct AUTELSDK_API CameraInfo {
    int cameraId = 0;  //相机镜头id（红外、可见光、夜视等），来源于相机能力集
    float fovH = 0;  // 镜头水平Fov
    float fovV = 0;  // 镜头垂直Fov
    double pixelSize = 0;	//相机像元间距
    double focalLength = 0;    //相机焦距
    uint32_t zoomFactor = 0;     //相机变焦倍数，真实值 * 100

    //重载==
    bool operator ==(const CameraInfo& other) const
    {
        return cameraId == other.cameraId
               && fovH == other.fovH
               && fovV == other.fovV
               && pixelSize == other.pixelSize
               && focalLength == other.focalLength
               && zoomFactor == other.zoomFactor;
    }

    std::string ToString() const;
};
//相机系统状态
struct AUTELSDK_API CameraStatus
{
    std::string deviceType;//设备类型
    CameraSystemState systemState = CameraSystemState::Unknown;// 系统状态
    CameraWorkMode currentMode = CameraWorkMode::Unknown;// 当前模式
    CameraPattern pattern = CameraPattern::Unknown;           //智能模式
    DisplayMode displayMode = DisplayMode::Unknown;// 当前显示模式
    RecordMode recordMode = RecordMode::Unknown;              // 录像子模式
    TakePhotoMode photoTakingMode = TakePhotoMode::Unknown;   // 拍照子模式
    StorageType storageType = StorageType::Unknown;           // 存储设备类型
    float fovH = 0;                                           // 镜头水平Fov
    float fovV = 0;                                           // 镜头垂直Fov
    double pixelSize = 0;                                     // 相机像元间距
    double focalLength = 0;                                   // 相机焦距
    uint32_t photoIntervalMin = 0;                            // 最小拍照间隔，单位毫秒
    std::vector<CameraInfo> listCameraInfo; //镜头信息列表

    //重载==
    bool operator ==(const CameraStatus& other) const
    {
        return deviceType == other.deviceType
               && systemState == other.systemState
               && currentMode == other.currentMode
               && pattern == other.pattern
               && displayMode == other.displayMode
               && recordMode == other.recordMode
               && photoTakingMode == other.photoTakingMode
               && storageType == other.storageType
               && fovH == other.fovH
               && fovV == other.fovV
               && pixelSize == other.pixelSize
               && focalLength == other.focalLength
               && photoIntervalMin == other.photoIntervalMin
               && listCameraInfo == other.listCameraInfo;
    }

    std::string ToString() const;
};

struct AUTELSDK_API CameraDeviceInfo
{
    int identifyCode = 0;                                     // 识别码，系统启动时生成的随机数，在系统重启前不会变化，用于客户端识别是否连接到其他相机
    std::string deviceType;
    std::string deviceModel;
    int protocolVersion = 0;
    std::string manufacturer;
    std::string firmwareVersion;
    std::string serialNumber;
    std::string hardwareId;
    std::string lensModel;
    std::string lensSoftVersion;

    std::string ToString() const;
};

struct AUTELSDK_API ParameterPointInfo
{
    int x = 0;
    int y = 0;

    std::string ToString() const;
};

struct AUTELSDK_API ParameterRectInfo
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    std::string ToString() const;
};
//存储状态
struct AUTELSDK_API CardStatusBean
{
    CardStatusEnum storageStatus = CardStatusEnum::NO_CARD;//存储状态
    int64_t totalSpace = 0;// SD卡总容量，以KB为单位
    int64_t freeSpace = 0;// SD卡剩余容量，以KB为单位
    int64_t remainRecordTime = 0;//剩余录像时间，以秒为单位
    int64_t remainCaptureNum = 0;//剩余拍照张数

    //重载==
    bool operator ==(const CardStatusBean& other) const
    {
        return storageStatus == other.storageStatus
               && totalSpace == other.totalSpace
               && freeSpace == other.freeSpace
               && remainRecordTime == other.remainRecordTime
               && remainCaptureNum == other.remainCaptureNum;
    }

    std::string ToString() const;
};

struct AUTELSDK_API PixelResolution
{
    int width = 0;
    int height = 0;

    VideoResolutionType ToVideoResolutionType() const;
    PhotoResolutionType ToPhotoResolutionType() const;

    //重载==
    bool operator ==(const PixelResolution& other) const
    {
        return width == other.width
               && height == other.height;
    }

    std::string ToString() const;
};

struct AUTELSDK_API VideoResolutionInfo
{
    PixelResolution videoResolution;
    int fps = 0;//帧率

    //重载==
    bool operator ==(const VideoResolutionInfo& other) const
    {
        return videoResolution == other.videoResolution
               && fps == other.fps;
    }

    std::string ToString() const;
};

struct AUTELSDK_API VideoEncoderConfigBean
{
    int streamId = 0;
    VideoCompressStandard encoding = VideoCompressStandard::H264;
    VideoResolutionInfo resolution;
    int quality = 0;
    int govLength = 0;
    VideoCompressProfileEnum profile = VideoCompressProfileEnum::LINE;
    VideoBitrateEnum bitrateType = VideoBitrateEnum::CBR;
    int bitrate = 0;
    bool slow = true;

    std::string ToString() const;
};

struct AUTELSDK_API VideoPhotoStorageInfo
{
    WorkMode mode = WorkMode::UNKNOWN;
    std::vector<int> ids;

    std::string ToString() const;
};

struct AUTELSDK_API VideoPhotoStorage
{
    int id = 0;
    bool enable = true;

    std::string ToString() const;
};

struct AUTELSDK_API VideoPhotoStorageListInfo
{
    WorkMode mode = WorkMode::UNKNOWN;
    std::vector<VideoPhotoStorage> ids;

    std::string ToString() const;
};

struct AUTELSDK_API CameraEncryptSetInfo
{
    CameraEncrypt mode = CameraEncrypt::CLOSE;
    std::string key;

    std::string ToString() const;
};
//快门速度
struct AUTELSDK_API ShutterSpeedInfo
{
    int numerator = 0;//分子
    int denominator = 0;//分母

    //重载==
    bool operator ==(const ShutterSpeedInfo& other) const
    {
        return numerator == other.numerator
               && denominator == other.denominator;
    }

    std::string ToString() const;
};

struct AUTELSDK_API ProfessionalParamInfo
{
    int cameraID = 0;//相机镜头id（红外、可见光、夜视等），来源于相机能力集
    IsoMode isoMode = IsoMode::Auto;//ISO模式
    ApertureMode apertureMode = ApertureMode::MANUAL;//光圈模式
    ShutterMode shutterMode = ShutterMode::MANUAL;//快门模式
    int isoValue = 0;// ISO值
    double apertureValue = 0;// 光圈值
    ShutterSpeedInfo shutterSpeed;// 快门速度
    double exposureValue = 0;// 曝光值
    WhiteBalance whiteMode = WhiteBalance::Unknown;//白平衡模式
    int colorTemperature = 0;//白平衡色温值
    int zoomValue = 0;//真实值 * 100

    //重载==
    bool operator ==(const ProfessionalParamInfo& other) const
    {
        return cameraID == other.cameraID
               && isoMode == other.isoMode
               && apertureMode == other.apertureMode
               && shutterMode == other.shutterMode
               && isoValue == other.isoValue
               && apertureValue == other.apertureValue
               && shutterSpeed == other.shutterSpeed
               && exposureValue == other.exposureValue
               && whiteMode == other.whiteMode
               && colorTemperature == other.colorTemperature
               && zoomValue == other.zoomValue;
    }


    std::string ToString() const;
};
//拍照图片的分辨率
struct AUTELSDK_API PhotoResolutionInfo
{
    int width = 0;
    int height = 0;
    //重载==
    bool operator ==(const PhotoResolutionInfo& other) const
    {
        return width == other.width
               && height == other.height;
    }

    std::string ToString() const;
};
//拍照文件信息
struct AUTELSDK_API PhotoFileInfo
{
    CameraWorkMode currentMode = CameraWorkMode::Unknown;//当前模式
    std::string filePath;// 文件路径
    std::string thumbnailPath;// 缩略图路径
    int64_t fileModifyTime = 0;// 文件修改时间
    int64_t fileSize = 0;//拍照图片大小
    int fileFormat = 0;//拍照图片格式
    PhotoResolutionInfo photoResolution;//拍照图片的分辨率
    int cameraId = 0;

    //重载==
    bool operator ==(const PhotoFileInfo& other) const
    {
        return currentMode == other.currentMode
               && filePath == other.filePath
               && thumbnailPath == other.thumbnailPath
               && fileModifyTime == other.fileModifyTime
               && fileSize == other.fileSize
               && fileFormat == other.fileFormat
               && photoResolution == other.photoResolution
               && cameraId == other.cameraId;
    }

    std::string ToString() const;
};
//拍照状态
struct AUTELSDK_API TakePhotoStatusInfo
{
    TakePhotoMode currentMode = TakePhotoMode::Unknown;//当前模式
    TakePhotoStatus state = TakePhotoStatus::UNKNOWN;//状态
    //重载==
    bool operator ==(const TakePhotoStatusInfo& other) const
    {
        return currentMode == other.currentMode
               && state == other.state;
    }

    std::string ToString() const;
};
//录像状态上报
struct AUTELSDK_API RecordStatusInfo
{
    CameraWorkMode currentMode = CameraWorkMode::Unknown;//当前模式
    RecordStatus state = RecordStatus::UNKNOWN;//状态
    int currentRecordTime = 0;//当前录像已录像时间，以秒为单位

    //重载==
    bool operator ==(const RecordStatusInfo& other) const
    {
        return currentMode == other.currentMode
               && state == other.state
               && currentRecordTime == other.currentRecordTime;
    }
    std::string ToString() const;
};
//录像文件信息
struct AUTELSDK_API RecordFileInfo
{
    RecordStatus currentMode = RecordStatus::UNKNOWN;// 当前模式
    RecordVideoFile state = RecordVideoFile::UNKNOWN;//状态
    std::string filePath;//文件路径
    std::string thumbnailPath;// 缩略图路径
    int64_t fileModifyTime = 0;//录像文件修改时间
    int64_t fileSize = 0;//文件大小
    int fileFormat = 0;//视频格式
    int videoDuration = 0;//视频时长
    VideoResolutionInfo videoResolution;//视频文件的分辨率
    VideoCompressStandard videoCompressionStandard = VideoCompressStandard::H264;//视频文件的压缩标准
    int cameraId = 0;//录像镜头id

    //重载==
    bool operator ==(const RecordFileInfo& other) const
    {
        return currentMode == other.currentMode
               && state == other.state
               && filePath == other.filePath
               && thumbnailPath == other.thumbnailPath
               && fileModifyTime == other.fileModifyTime
               && fileSize == other.fileSize
               && fileFormat == other.fileFormat
               && videoDuration == other.videoDuration
               && videoResolution == other.videoResolution
               && videoCompressionStandard == other.videoCompressionStandard
               && cameraId == other.cameraId;
    }

    std::string ToString() const;
};
//全景拍照状态
struct AUTELSDK_API PanoramaStatusInfo
{
    PanoramaShootStatus state = PanoramaShootStatus::UNKNOWN;// 全景拍照当前状态
    Panorama type;//全景拍照类型
    int totalStep = 0;//总步骤
    int currentStep = 0;//全景拍照当前步数
    float proportion = 0;//全景拍照当前完成比例

    //重载==
    bool operator ==(const PanoramaStatusInfo& other) const
    {
        return state == other.state
               && type == other.type
               && totalStep == other.totalStep
               && currentStep == other.currentStep
               && proportion == other.proportion;
    }

    std::string ToString() const;
};
//延时摄影状态
struct AUTELSDK_API DelayShotStatusInfo
{
    int remainTime = 0;// 剩余时间，以秒为单位
    int countDown = 0;//拍摄下一张照片的倒计时，以秒为单位
    int captured = 0;//已拍照张数

    //重载==
    bool operator ==(const DelayShotStatusInfo& other) const
    {
        return remainTime == other.remainTime
               && countDown == other.countDown
               && captured == other.captured;
    }

    std::string ToString() const;
};
// AE/AF状态
struct AUTELSDK_API CameraAFAEStatusInfo
{
    int doNotUse = 0;
    CameraAfAe aeStatus = CameraAfAe::UNKNOWN;//相机AE状态
    CameraAfAe afStatus = CameraAfAe::UNKNOWN;//相机AF状态

    //重载==
    bool operator ==(const CameraAFAEStatusInfo& other) const
    {
        return aeStatus == other.aeStatus
               && afStatus == other.afStatus;
    }

    std::string ToString() const;
};

struct AUTELSDK_API TempAlarmInfo
{
    Temperature status = Temperature::COLD;//0高温，1低温
    int hotTemp = 0;//高温告警点温度;单位摄氏度*10
    uint32_t hotX = 0;//高温报警X坐标，以图像宽比例 [0..100]
    uint32_t hotY = 0;//高温报警Y坐标，以图像高比例 [0..100]
    int coldTemp = 0;//低温告警点温度;单位摄氏度*10.
    uint32_t coldX = 0;//低温报警X坐标，以图像宽比例 [0..100]
    uint32_t coldY = 0;//低温报警Y坐标，以图像高比例 [0..100]
    int cameraId = 0;//镜头id

    //重载==
    bool operator ==(const TempAlarmInfo& other) const
    {
        return status == other.status
               && hotTemp == other.hotTemp
               && hotX == other.hotX
               && hotY == other.hotY
               && coldTemp == other.coldTemp
               && coldX == other.coldX
               && coldY == other.coldY
               && cameraId == other.cameraId;
    }

    std::string ToString() const;
};
//移动延时摄影状态
struct AUTELSDK_API MotionDelayShotInfo
{
    MotionDelayShoot status = MotionDelayShoot::UNKNOWN;// 状态
    int photoTime = 0;//已拍照时长，单位秒
    int totalPhotoTime = 0;//总的需要拍照的时长，单位秒
    int photoNum = 0;//已拍照张数
    int totalPhotoNum = 0;//总的需要拍照的张数

    //重载==
    bool operator ==(const MotionDelayShotInfo& other) const
    {
        return status == other.status
               && photoTime == other.photoTime
               && totalPhotoTime == other.totalPhotoTime
               && photoNum == other.photoNum
               && totalPhotoNum == other.totalPhotoNum;
    }

    std::string ToString() const;
};
//任务录制航点信息
struct AUTELSDK_API MissionRecordWaypointInfo
{
    std::string filePath;// 照片路径
    double latitude = 0;//经度
    double longitude = 0;//纬度
    double altitude = 0;//从飞控读取的绝对高度(海拔高度)
    double heading = 0;//从飞控读取的机头朝向
    double cameraPitch = 0;//从飞控读取的云台Pitch角
    double cameraYaw = 0;//从飞控读取的云台Yaw角
    int zoom = 0; //相机变焦倍数
    double cameraRoll = 0;//从飞控读取的云台Roll角
    double height = 0;//从飞控读取的相对高度
    int cameraId = 0;

    //重载==
    bool operator ==(const MissionRecordWaypointInfo& other) const
    {
        return filePath == other.filePath
               && latitude == other.latitude
               && longitude == other.longitude
               && altitude == other.altitude
               && heading == other.heading
               && cameraPitch == other.cameraPitch
               && cameraYaw == other.cameraYaw
               && zoom == other.zoom
               && cameraRoll == other.cameraRoll
               && height == other.height
               && cameraId == other.cameraId;
    }

    std::string ToString() const;
};
//相机模式切换信息
struct AUTELSDK_API CameraModeSwitchInfo
{
    CameraWorkMode currentMode = CameraWorkMode::Unknown;// 当前模式
    int32_t recordMode = 0;// 录像子模式
    TakePhotoMode photoTakingMode;// 拍照子模式

    //重载==
    bool operator ==(const CameraModeSwitchInfo& other) const
    {
        return currentMode == other.currentMode
               && recordMode == other.recordMode
               && photoTakingMode == other.photoTakingMode;
    }

    std::string ToString() const;
};

struct AUTELSDK_API InfraredCameraTempInfo
{
    int averageTemp = 0;// 平均温度;单位摄氏度*10
    int centerTemp = 0;// 中心温度;单位摄氏度*10
    int hotTemp = 0;// 热点温度;单位摄氏度*10
    int coldTemp = 0;// 冷点温度;单位摄氏度*10
    int touchTemp = 0;// 指点温度;单位摄氏度*10
    uint32_t hotX = 0;//热点X坐标，以图像宽比例 【0-100】
    uint32_t hotY = 0;//热点Y坐标，以图像高比例 【0-100】
    uint32_t coldX = 0;//冷点X坐标，以图像宽比例 【0-100】
    uint32_t coldY = 0;//冷点X坐标，以图像高比例 【0-100】
    uint32_t zoomValue = 0;//真实值 * 100
    int cameraId = 0; //镜头id

    //重载==
    bool operator ==(const InfraredCameraTempInfo& other) const
    {
        return averageTemp == other.averageTemp
               && centerTemp == other.centerTemp
               && hotTemp == other.hotTemp
               && coldTemp == other.coldTemp
               && touchTemp == other.touchTemp
               && hotX == other.hotX
               && hotY == other.hotY
               && coldX == other.coldX
               && coldY == other.coldY
               && zoomValue == other.zoomValue
               && cameraId == other.cameraId;
    }

    std::string ToString() const;
};

struct AUTELSDK_API StorageStatusInfo
{
    StorageType storageType = StorageType::Unknown;// 存储设备类型
    CardStatus sDCardStatus = CardStatus::UNKNOWN;// SD卡状态
    int64_t totalSpace = 0;// SD卡总容量，以KB为单位
    int64_t freeSpace = 0;// SD卡剩余容量，以KB为单位
    CardStatus mmcStatus = CardStatus::UNKNOWN;// eMMC状态
    int64_t mmcTotalSpace = 0;// eMMC总容量，以KB为单位
    int64_t mmcFreeSpace = 0;// eMMC卡剩余容量，以KB为单位
    int64_t remainRecordTime = 0;// 当前选定的存储设备的剩余录像时间，以秒为单位
    int64_t remainCaptureNum = 0;// 当前选定的存储设备的剩余拍照张数

    //重载==
    bool operator ==(const StorageStatusInfo& other) const
    {
        return storageType == other.storageType
               && sDCardStatus == other.sDCardStatus
               && totalSpace == other.totalSpace
               && freeSpace == other.freeSpace
               && mmcStatus == other.mmcStatus
               && mmcTotalSpace == other.mmcTotalSpace
               && mmcFreeSpace == other.mmcFreeSpace
               && remainRecordTime == other.remainRecordTime
               && remainCaptureNum == other.remainCaptureNum;
    }

    std::string ToString() const;
};

struct AUTELSDK_API MeteringPointInfo
{
    int x = 0;//点聚焦坐标，X范围(0 - 100)
    int y = 0;//点聚焦坐标，y范围(0 - 100)

    //重载==
    bool operator ==(const MeteringPointInfo& other) const
    {
        return x == other.x && y == other.y;
    }

    std::string ToString() const;
};
//白平衡参数
struct AUTELSDK_API WhiteBalanceInfo
{
    WhiteBalance mode = WhiteBalance::Unknown;//白平衡模式
    int colorTemperature = 0;//Mode设置为Custom时有效，范围 2000 - 10000，步长为 100

    //重载==
    bool operator ==(const WhiteBalanceInfo& other) const
    {
        return mode == other.mode
               && colorTemperature == other.colorTemperature;
    }

    std::string ToString() const;
};
/*
struct FocusInfo
{
    FocusMode mode = FocusMode::UNKNOWN;
    AFLensFocusMode meterMode = AFLensFocusMode::UNKNOWN;
    int spotAreaX = 0;
    int spotAreaY = 0;
    int objectDistance = 0;
    bool aFAssistFocusEnable = true;
    bool mFAssistFocusEnable = true;


    //重载==
    bool operator ==(const FocusInfo& other) const
    {
        return mode == other.mode
               && meterMode == other.meterMode
               && spotAreaX == other.spotAreaX
               && spotAreaY == other.spotAreaY
               && objectDistance == other.objectDistance
               && aFAssistFocusEnable == other.aFAssistFocusEnable
               && mFAssistFocusEnable == other.mFAssistFocusEnable;
    }

    std::string ToString() const;
};
*/
struct AUTELSDK_API RoiRegionInfo
{
    bool enable = 0;//是否开启
    int priority = 0;//ROI区域缩影，范围[0-7].
    int strength = 0;//强度
    double recX = 0;//ROI区域起点X坐标.
    double recY = 0;//ROI区域起点Y坐标.
    double rectWith = 0;//ROI区域宽度.
    double rectHeight = 0;//ROIROI区域高度.

    //重载==
    bool operator ==(const RoiRegionInfo& other) const
    {
        return enable == other.enable
               && priority == other.priority
               && strength == other.strength
               && recX == other.recX
               && recY == other.recY
               && rectWith == other.rectWith
               && rectHeight == other.rectHeight;
    }

    std::string ToString() const;
};
//ROI配置
struct AUTELSDK_API ROIInfo
{
    bool enable = true;
    std::vector<RoiRegionInfo> roiRegionList;

    //重载==
    bool operator ==(const ROIInfo& other) const
    {
        return enable == other.enable
               && roiRegionList == other.roiRegionList;
    }
    std::string ToString() const;
};
//解密进度
struct AUTELSDK_API CameraEncryptProgressReportInfo
{
    int totalCount = 0;//总数
    int completeCount = 0;//已经完成数量

    //重载==
    bool operator ==(const CameraEncryptProgressReportInfo& other) const
    {
        return totalCount == other.totalCount
               && completeCount == other.completeCount;
    }

    std::string ToString() const;
};
//相机图传信息
struct AUTELSDK_API CameraTransferInfo
{
    int cameraId = 0;// 相机id
    int transferMode = 0;//  图传模式  1（流畅）/2（高清）/3（2.7K）
    int transferPayloadType = 0;//  图传编码类型 0（H264)/1(H265)
    int fps = 0;//  图传帧率       帧数/秒
    int bitrate = 0;//  图传码率       kbps
    int sendIFrameNum = 0;//  发送的关键帧数  帧数/分钟
    int requestIFrameNum = 0;//  请求的关键帧数  个数/分钟
    bool transferEnable = true;//  图传开关（0-图传关闭，1-图传开启）

    //重载==
    bool operator ==(const CameraTransferInfo& other) const
    {
        return cameraId == other.cameraId
               && transferMode == other.transferMode
               && transferPayloadType == other.transferPayloadType
               && fps == other.fps
               && bitrate == other.bitrate
               && sendIFrameNum == other.sendIFrameNum
               && requestIFrameNum == other.requestIFrameNum
               && transferEnable == other.transferEnable;
    }

    std::string ToString() const;
};

struct AUTELSDK_API CameraEisReportInfo
{
    int zoomValue = 0;
    double leftAngle = 0;
    double rightAngle = 0;
    double topAngle = 0;
    double bottomAngle = 0;
    double left = 0;
    double right = 0;
    double top = 0;
    double bottom = 0;

    //重载==
    bool operator ==(const CameraEisReportInfo& other) const
    {
        return zoomValue == other.zoomValue
               && leftAngle == other.leftAngle
               && rightAngle == other.rightAngle
               && topAngle == other.topAngle
               && bottomAngle == other.bottomAngle
               && left == other.left
               && right == other.right
               && top == other.top
               && bottom == other.bottom;
    }

    std::string ToString() const;
};

struct AUTELSDK_API ThermalImageBean
{
    ThermalImageMode imageMode = ThermalImageMode::UNKNOWN;     // 图像模式
    int contrast = 0;                                                   // 对比度0~255
    int lum = 0;                                                        // 亮度0~511
    std::string ToString() const;
};

struct AUTELSDK_API ThermalEnhanceBean
{
    bool enable = true;        // 使能
    int strength = 0;          // 强度1~8
    std::string ToString() const;
};

struct AUTELSDK_API ThermalTempAlarmBean
{
    bool enable = true;        // 报警使能
    int hotThred = 0;          // 超过温度阈值就告警，单位摄氏度*10
    int coldThred = 0;         // 低于温度阈值就告警，单位摄氏度*10
    std::string ToString() const;
};

struct AUTELSDK_API ThermalTempAttrBean
{
    TemperatureMode tempMode = TemperatureMode::UNKNOWN;       // 测温模式
    int touchX = 0;                                                    // 指点测温x坐标,以yuv图像宽比例计算
    int touchY = 0;                                                    // 指点测温Y坐标
    int regionX = 0;                                                   // 区域测温x坐标
    int regionY = 0;                                                   // 区域测温Y坐标
    int regionW = 0;                                                   // 区域测温宽
    int regionH = 0;                                                   // 区域测温高
    int limitTempX = 0;                                                // 限制测温小画面x坐标
    int limitTempY = 0;                                                // 限制测温小画面y坐标
    int limitTempW = 0;                                                // 限制测温小画面宽
    int limitTempH = 0;                                                // 限制测温小画面高
    std::string ToString() const;
};

struct AUTELSDK_API ThermalIsothermBean
{
    IsothermEnum mode = IsothermEnum::UNKNOWN;      // 模式
    int hotThred = 0;                               // 自定义模式时高阈值
    int coldThred = 0;                              // 自定义模式时低阈值

    std::string ToString() const;
};

struct AUTELSDK_API PhotoResolutionEnumInfo
{
    int width = 0;
    int height = 0;

    //    int PR_4000_3000;
    //    PR_1920_1200;
    //    PR_1920_1200;
    //    PR_1920_1080;
    //    PR_1920_1080;
    //    PR_4096_3072;
    //    PR_4096_3072;
    //    PR_8192_6144;
    //    PR_8192_6144;
    //    PR_640_512;
    //    PR_640_512;
    //    PR_3840_2160;
    //    PR_3840_2160;
    //    PR_5472_3648;
    //    PR_5472_3648;
    //    PR_5472_3076;
    //    PR_5472_3076;
    //    PR_UNKNOWN;
    std::string ToString() const;
};

struct AUTELSDK_API WatermarkBean
{
    int enableTime = 0;
    bool enableCustom = true;
    std::string custom;

    std::string ToString() const;
};

struct AUTELSDK_API CameraRecordPivInfoBean
{
    bool enable = true;    // 是否开启
    int interval = 0;      // 间隔时间

    std::string ToString() const;
};

struct AUTELSDK_API ImageStyleBean
{
    ImageStyleEnum style = ImageStyleEnum::UNKNOWN;           // 图像风格
    int brightness = 0;             // 亮度，-3 - +3
    int contrast = 0;               // 对比度，-3 - +3
    int saturation = 0;             // 饱和度，-3 - +3
    int hue = 0;                    // 色度，-3 - +3
    int sharpness = 0;              // 锐度，-3 - +3

    std::string ToString() const;
};

struct AUTELSDK_API DefogBean
{
    bool enable = true;
    DefogEnum strength = DefogEnum::DEFOG_CLOSE;

    std::string ToString() const;
};

struct AUTELSDK_API FocusInfoBean
{
    FocusModeEnum mode = FocusModeEnum::UNKNOWN;                       // 聚焦模式
    AFLensFocusModeEnum meterMode = AFLensFocusModeEnum::UNKNOWN;      // 自动聚焦模式
    int spotAreaX = 0;                                                 // 点聚焦坐标，X范围(0 - 100)
    int spotAreaY = 0;                                                 // 点聚焦坐标，y范围(0 - 100)
    int objectDistance = 0;                                            // 物距，单位mm，分三个段(每段10个刻度)：[ 10cm - 1m ]、[ 1m - 10m ] [ 10m - 100m ], 特殊值 0：微距， -1：无穷远
    bool aFAssistFocusEnable = true;                                   // 辅助对焦使能,1:使能 0：关闭
    bool mFAssistFocusEnable = true;                                   // 辅助对焦使能,1:使能 0：关闭

    //重载==
    bool operator ==(const FocusInfoBean& other) const
    {
        return mode == other.mode
               && meterMode == other.meterMode
               && spotAreaX == other.spotAreaX
               && spotAreaY == other.spotAreaY
               && objectDistance == other.objectDistance
               && aFAssistFocusEnable == other.aFAssistFocusEnable
               && mFAssistFocusEnable == other.mFAssistFocusEnable;
    }

    std::string ToString() const;
};

typedef FocusInfoBean FocusInfo;

struct AUTELSDK_API CameraBaseParamBean
{
    StorageType storageType = StorageType::Unknown;                              // 存储设备类型
    CardStatusBean sdStatus;                                                     // SD卡状态
    CardStatusBean mmcStatus;                                                    // 闪存卡状态
    WatermarkBean waterMark;                                                     // 水印
    bool hdrStatus = true;                                                       // HDR状态
    PhotoFormatEnum picType = PhotoFormatEnum::UNKNOWN;                          // 图片类型
    PhotoResolutionEnumInfo resolution;                                          // 图片分辨率
    int burstCount = 0;                                                          // 在Burst模式下每秒钟拍照数
    int interval = 0;                                                            // 在Timelapse模式下拍照持续时间，以秒为单位
    int aebCount = 0;                                                            // 在AEB模式下一次抓多少图片
    CameraRecordPivInfoBean pivStatus;                                           // Piv状态
    VideoFormatEnum fileFormat = VideoFormatEnum::UNKNOWN;                       // 文件格式
    bool enableSubtitle = true;                                                  // 字幕开关
    VideoResolutionInfo resolutionInfo;                                          // 录像分辨率
    VideoCompressStandard encoding = VideoCompressStandard::UNKNOWN;     // 视频编码类型
    ImageStyleBean imageStyleInfo;                                               // 图像风格
    bool aeLock = true;                                                          // AE锁
    DefogBean dehazeInfo;                                                        // 雾透信息
    VideoStandardEnum videoStandard = VideoStandardEnum::UNKNOWN;                // 视频制式
    ResistanceBlinkEnum antiFlicker = ResistanceBlinkEnum::UNKNOWN;              // 抗闪烁
    FocusInfoBean focusInfo;                                                     // 相机聚焦信息
    ThermalColorEnum color = ThermalColorEnum::UNKNOWN;                          // 热成像伪彩信息
    ThermalImageBean irImageModeInfo;                                            // 热成像图像模式
    ThermalEnhanceBean irEnhanceInfo;                                            // 图像增强
    bool irNr = true;                                                             // 图像去噪
    ThermalGainEnum gain = ThermalGainEnum::UNKNOWN;                             // 图像增益
    ThermalIsothermBean irIsoThermInfo;                                          // 等温线
    int irTempEmit = 0;                                                          // 热成像辐射率

    std::string ToString() const;
};

struct AUTELSDK_API VideoSourceConfigBean
{
    int rotation = 0;
    VideoStandardEnum videoStandard = VideoStandardEnum::UNKNOWN;
    ResistanceBlinkEnum antiFlicker = ResistanceBlinkEnum::UNKNOWN;
    bool enable3DNR = true;
    std::string ToString() const;
};

struct AUTELSDK_API CameraWorkModeInfoBean
{
    CameraWorkModeEnum workMode = CameraWorkModeEnum::UNKNOWN;
    TakePhotoModeEnum photoMode = TakePhotoModeEnum::UNKNOWN;
    RecordModeEnum videoMode = RecordModeEnum::UNKNOWN;
    std::string ToString() const;
};

struct AUTELSDK_API PhotoResolutionBean
{
    PixelResolution videoResolution;
    int fps = 0;

    std::string ToString() const;
};

struct AUTELSDK_API TakePhotoParametersBean
{
    PhotoFormatEnum picType = PhotoFormatEnum::UNKNOWN;
    PixelResolution resolution;
    int delaySeconds = 0;
    int gimbalRollingStep = 0;
    GimbalRotateDirectionEnum gimbalRollingDirection = GimbalRotateDirectionEnum::CLOCKWISE;
    bool enableHDR = true;
    int burstCount = 0;
    int interval = 0;
    int duration = 0;
    bool composeVideo = true;
    PhotoResolutionBean resolutionInfo;
    int aebCount = 0;

    std::string ToString() const;
};

struct AUTELSDK_API RecordParametersBean
{
    VideoFormatEnum fileFormat = VideoFormatEnum::UNKNOWN;
    bool enableAudio = true;
    bool enableSubtitle = true;
    bool enablePiv = true;
    int interval = 0;
    int maxRecordTime = 0;
    PhotoResolutionBean resolutionInfo;

    std::string ToString() const;
};

struct AUTELSDK_API MeteringPointBean
{
    int x = 0;
    int y = 0;
    std::string ToString() const;
};

struct AUTELSDK_API WhiteBalanceBean
{
    WhiteBalanceEnum mode = WhiteBalanceEnum::UNKNOWN;
    int colorTemperature = 0;

    std::string ToString() const;
};

struct AUTELSDK_API ShutterSpeedBean
{
    int numerator = 0;
    int denominator = 0;
    std::string ToString() const;
};

struct AUTELSDK_API RoiRegionBean
{
    bool enable = true;
    int priority = 0;
    int strength = 0;
    double rectX = 0;
    double rectY = 0;
    double rectWidth = 0;
    double rectHeight = 0;
    std::string ToString() const;
};

struct AUTELSDK_API ROIBean
{
    bool enable = true;
    std::list<RoiRegionBean> roiRegionList;
    std::string ToString() const;
};

struct AUTELSDK_API RecordPacketBean
{
    StorageType format = StorageType::Unknown;
    int recordPacket = 0;
    std::string ToString() const;
};

struct AUTELSDK_API Contrast
{
    int min = 0;
    int max = 0;
    int step = 0;

    std::string ToString() const;
};

struct AUTELSDK_API Lum
{
    int min = 0;
    int max = 0;
    int step = 0;

    std::string ToString() const;
};

// 整数范围基础类型，多个相机参数复用此类型，不要随意修改
struct AUTELSDK_API IntRange
{
    int min = 0;
    int max = 0;
    int step = 0;

    std::string ToString() const;
};

// 热成像图像模式
struct AUTELSDK_API IrImageMode
{
    std::list<int> mode;
    IntRange contrast;
    IntRange lum;

    std::string ToString() const;
};

struct AUTELSDK_API PhotoResolutionValue
{
    int  width = 0;
    int height = 0;

    std::string ToString() const;
};

struct AUTELSDK_API FloatRange
{
    float min = 0;
    float max = 0;
    float step = 0;

    std::string ToString() const;
};

struct AUTELSDK_API DigitalZoomScale
{
    float min = 0;
    float max = 0;
    float step = 0;

    std::string ToString() const;
};

struct AUTELSDK_API IntThreshold
{
    int min = 0;
    int max = 0;

    std::string ToString() const;
};

struct AUTELSDK_API Frame
{
    int rate = 0;
    bool isHdrEnable = true;

    std::string ToString() const;
};

struct AUTELSDK_API VideoResolutionFrame
{
    VideoResolutionType videoResolution;
    std::list<Frame> fpsList;

    std::string ToString() const;
};

struct AUTELSDK_API IrGain
{
    IntRange highGain;
    IntRange lowGain;

    std::string ToString() const;
};

using IRValue = IntRange;

struct AUTELSDK_API IRHotColdValue
{
    IRValue highValue;
    IRValue lowValue;

    std::string ToString() const;
};

struct AUTELSDK_API CameraCapability
{
    std::string version;
    std::string filePath;

    std::string ToString() const;
};

struct AUTELSDK_API CameraUtil
{
    static void GetPhotoSize(PhotoResolutionType resolution, int& width, int& height);
    static void GetVideoSize(VideoResolutionType resolution, int& width, int& height);
    static void GetPhotoSizeType(int width, int height, PhotoResolutionType& resolution);
    static void GetVideoSizeType(int width, int height, VideoResolutionType& resolution);
};
} // namespace AutelMobileSdk
#endif
