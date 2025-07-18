#ifndef ICAMERA_H
#define ICAMERA_H

#include <memory>
#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "CameraKeyDataType.h"

namespace AutelMobileSdk
{
class AUTELSDK_API ICamera
{
public:
    // ==========参数查询、设置，指令执行操作类接口==========
    // 查询相机设备信息
    virtual ErrorCode GetCameraDeviceInfo(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraDeviceInfo>> listener, int retryCount = 0) = 0;

    // 存储设备类型
    virtual ErrorCode GetStorageType(uint32_t deviceId, std::shared_ptr<CompletionListener<StorageType>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetStorageType(uint32_t deviceId, StorageType storageType, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 查询SD卡存储状态
    virtual ErrorCode GetSDCardStatus(uint32_t deviceId, std::shared_ptr<CompletionListener<CardStatusBean>> listener, int retryCount = 0) = 0;

    // 查询MMC机载闪存存储状态
    virtual ErrorCode GetMMCStatus(uint32_t deviceId, std::shared_ptr<CompletionListener<CardStatusBean>> listener, int retryCount = 0) = 0;

    // 视频编码器配置
    virtual ErrorCode GetVideoEncoderConfig(uint32_t deviceId, std::shared_ptr<CompletionListener<VideoEncoderConfigBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetVideoEncoderConfig(uint32_t deviceId, const VideoEncoderConfigBean& videoEncoderConfigBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视频源配置
    virtual ErrorCode GetVideoSourceConfig(uint32_t deviceId, std::shared_ptr<CompletionListener<VideoSourceConfigBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetVideoSourceConfig(uint32_t deviceId, const VideoSourceConfigBean& videoSourceConfigBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机档位
    virtual ErrorCode GetCameraGear(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraGearEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraGear(uint32_t deviceId, CameraGearEnum cameraGearEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机模式
    virtual ErrorCode GetCameraMode(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraWorkModeInfoBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraMode(uint32_t deviceId, const CameraWorkModeInfoBean& cameraWorkModeInfoBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 拍照参数
    virtual ErrorCode GetTakePhotoParameters(uint32_t deviceId, std::shared_ptr<CompletionListener<TakePhotoParametersBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTakePhotoParameters(uint32_t deviceId, const TakePhotoParametersBean& takePhotoParametersBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 录像参数
    virtual ErrorCode GetRecordParameters(uint32_t deviceId, std::shared_ptr<CompletionListener<RecordParametersBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRecordParameters(uint32_t deviceId, const RecordParametersBean& recordParametersBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 测光点
    virtual ErrorCode GetMeteringPoint(uint32_t deviceId, std::shared_ptr<CompletionListener<MeteringPointBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetMeteringPoint(uint32_t deviceId, const CameraWorkModeInfoBean& cameraWorkModeInfoBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像风格
    virtual ErrorCode GetImageStyle(uint32_t deviceId, std::shared_ptr<CompletionListener<ImageStyleBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetImageStyle(uint32_t deviceId, const CameraWorkModeInfoBean& cameraWorkModeInfoBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 白平衡参数
    virtual ErrorCode GetWhiteBalance(uint32_t deviceId, std::shared_ptr<CompletionListener<WhiteBalanceBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetWhiteBalance(uint32_t deviceId, const CameraWorkModeInfoBean& cameraWorkModeInfoBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像颜色参数
    virtual ErrorCode GetImageColor(uint32_t deviceId, std::shared_ptr<CompletionListener<ImageColorEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetImageColor(uint32_t deviceId, const CameraWorkModeInfoBean& cameraWorkModeInfoBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像曝光参数
    virtual ErrorCode GetImageExposure(uint32_t deviceId, std::shared_ptr<CompletionListener<double>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetImageExposure(uint32_t deviceId, double imageExposure, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像感光度
    virtual ErrorCode GetImageIso(uint32_t deviceId, std::shared_ptr<CompletionListener<int64_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetImageIso(uint32_t deviceId, int imageIso, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // AELock
    virtual ErrorCode GetAELock(uint32_t deviceId, std::shared_ptr<CompletionListener<bool>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetAELock(uint32_t deviceId, bool aELock, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 快门速度
    virtual ErrorCode GetShutterSpeed(uint32_t deviceId, std::shared_ptr<CompletionListener<ShutterSpeedBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetShutterSpeed(uint32_t deviceId, const ShutterSpeedBean& shutterSpeedBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 快门模式
    virtual ErrorCode GetShutterMode(uint32_t deviceId, std::shared_ptr<CompletionListener<ShutterModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetShutterMode(uint32_t deviceId, ShutterModeEnum shutterModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 聚焦信息模式
    virtual ErrorCode GetFocusInfoMode(uint32_t deviceId, std::shared_ptr<CompletionListener<FocusModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetFocusInfoMode(uint32_t deviceId, FocusModeEnum focusModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 自动聚焦模式
    virtual ErrorCode GetAFMeterMode(uint32_t deviceId, std::shared_ptr<CompletionListener<AFLensFocusModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetAFMeterMode(uint32_t deviceId, FocusModeEnum focusModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 点聚焦坐标组
    virtual ErrorCode GetCameraFocusSpotArea(uint32_t deviceId, std::shared_ptr<CompletionListener<AFLensFocusModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraFocusSpotArea(uint32_t deviceId, const MeteringPointBean& meteringPointBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 手动变焦
    virtual ErrorCode GetCameraMFObjectDistance(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraMFObjectDistance(uint32_t deviceId, int mFObjectDistance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 自动辅助对焦使能
    virtual ErrorCode GetCameraAFAssistFocusEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraAFAssistFocusEnable(uint32_t deviceId, int aFAssistFocusEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 手动辅助对焦使能
    virtual ErrorCode GetCameraMFAssistFocusEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraMFAssistFocusEnable(uint32_t deviceId, int mFAssistFocusEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 光圈大小
    virtual ErrorCode GetApertureSize(uint32_t deviceId, std::shared_ptr<CompletionListener<double>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetApertureSize(uint32_t deviceId, double apertureSize, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 光圈模式
    virtual ErrorCode GetApertureMode(uint32_t deviceId, std::shared_ptr<CompletionListener<PatternModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetApertureMode(uint32_t deviceId, ApertureModeEnum apertureModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 数码/热成像变焦信息
    virtual ErrorCode GetZoomFactor(uint32_t deviceId, std::shared_ptr<CompletionListener<int64_t>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetZoomFactor(uint32_t deviceId, int zoomFactor, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机界面模式
    virtual ErrorCode GetPatternMode(uint32_t deviceId, std::shared_ptr<CompletionListener<PatternModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPatternMode(uint32_t deviceId, PatternModeEnum patternModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // PIV录像状态
    virtual ErrorCode GetRecordPiv(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraRecordPivInfoBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRecordPiv(uint32_t deviceId, const CameraRecordPivInfoBean& cameraRecordPivInfoBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // HDR配置
    virtual ErrorCode GetHDR(uint32_t deviceId, std::shared_ptr<CompletionListener<bool>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetHDR(uint32_t deviceId, bool hDR, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 透雾功能配置
    virtual ErrorCode GetDefog(uint32_t deviceId, std::shared_ptr<CompletionListener<DefogBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetDefog(uint32_t deviceId, const DefogBean& defogBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ROI配置
    virtual ErrorCode GetROI(uint32_t deviceId, std::shared_ptr<CompletionListener<ROIBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetROI(uint32_t deviceId, const ROIBean& rOIBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 感光度模式
    virtual ErrorCode GetISOMode(uint32_t deviceId, std::shared_ptr<CompletionListener<ISOModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetISOMode(uint32_t deviceId, const RecordPacketBean& recordPacketBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 录像分段打包大小
    virtual ErrorCode GetRecordPacket(uint32_t deviceId, std::shared_ptr<CompletionListener<RecordPacketBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRecordPacket(uint32_t deviceId, ISOModeEnum iSOModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 水印
    virtual ErrorCode GetWatermark(uint32_t deviceId, std::shared_ptr<CompletionListener<WatermarkBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetWatermark(uint32_t deviceId, const WatermarkBean& watermarkBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像伪彩信息
    virtual ErrorCode GetThermalColor(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalColorEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalColor(uint32_t deviceId, ThermalColorEnum thermalColorEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像模式
    virtual ErrorCode GetThermalMode(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalImageBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalMode(uint32_t deviceId, const ThermalImageBean& thermalImageBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像增强
    virtual ErrorCode GetThermalEnhance(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalEnhanceBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalEnhance(uint32_t deviceId, const ThermalEnhanceBean& thermalEnhanceBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像去噪
    virtual ErrorCode GetThermalDenoising(uint32_t deviceId, std::shared_ptr<CompletionListener<bool>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalDenoising(uint32_t deviceId, bool thermalDenoising, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像增益
    virtual ErrorCode GetThermalGain(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalGainEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalGain(uint32_t deviceId, ThermalGainEnum thermalGainEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像等温线
    virtual ErrorCode GetThermalIsotherm(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalIsothermBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalIsotherm(uint32_t deviceId, const ThermalIsothermBean& thermalIsothermBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度属性
    virtual ErrorCode GetThermalTemperature(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalTempAttrBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalTemperature(uint32_t deviceId, const ThermalTempAttrBean& thermalTempAttrBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度告警属性
    virtual ErrorCode GetThermalTemperatureAlarm(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalTempAlarmBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalTemperatureAlarm(uint32_t deviceId, const ThermalTempAlarmBean& thermalTempAlarmBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像辐射率
    virtual ErrorCode GetThermalRadiance(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetThermalRadiance(uint32_t deviceId, int thermalRadiance, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机拍照分辨率信息
    virtual ErrorCode GetTakePhotoResolution(uint32_t deviceId, std::shared_ptr<CompletionListener<PhotoResolutionEnumInfo>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTakePhotoResolution(uint32_t deviceId, const PhotoResolutionEnumInfo& photoResolutionEnumInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机录像分辨率信息
    virtual ErrorCode GetRecordResolution(uint32_t deviceId, std::shared_ptr<CompletionListener<VideoResolutionInfo>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRecordResolution(uint32_t deviceId, const VideoResolutionInfo& videoResolutionBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机拍照图片类型
    virtual ErrorCode GetPhotoFileFormat(uint32_t deviceId, std::shared_ptr<CompletionListener<PhotoFormatEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetPhotoFileFormat(uint32_t deviceId, PhotoFormatEnum photoFormatEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机AEB拍照Count
    virtual ErrorCode GetTakePhotoAebCount(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTakePhotoAebCount(uint32_t deviceId, int takePhotoAebCount, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机Bust拍照Count
    virtual ErrorCode GetTakePhotoBustCount(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTakePhotoBustCount(uint32_t deviceId, int takePhotoBustCount, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机Timelapse拍照间隔
    virtual ErrorCode GetTakePhotoTimeLapse(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetTakePhotoTimeLapse(uint32_t deviceId, int takePhotoTimeLapse, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 录像文件类型
    virtual ErrorCode GetRecordFileFormat(uint32_t deviceId, std::shared_ptr<CompletionListener<VideoFormatEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRecordFileFormat(uint32_t deviceId, VideoFormatEnum videoFormatEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 录像文件编码类型
    virtual ErrorCode GetRecordFileEncodeFormat(uint32_t deviceId, std::shared_ptr<CompletionListener<VideoCompressStandard>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetRecordFileEncodeFormat(uint32_t deviceId, VideoCompressStandard videoCompressStandard, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视频字幕开关
    virtual ErrorCode GetCameraSubtitleKey(uint32_t deviceId, std::shared_ptr<CompletionListener<bool>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraSubtitleKey(uint32_t deviceId, bool subtitleKey, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取相机基本参数
    virtual ErrorCode GetGetBaseParamMsg(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraBaseParamBean>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetGetBaseParamMsg(uint32_t deviceId, const CameraBaseParamBean& cameraBaseParamBean, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 抗闪烁模式
    virtual ErrorCode GetCameraAntiflicker(uint32_t deviceId, std::shared_ptr<CompletionListener<AntiflickerEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraAntiflicker(uint32_t deviceId, AntiflickerEnum antiflickerEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 拍照录像时自动关闭机臂灯
    virtual ErrorCode GetCameraTurnOffArmLight(uint32_t deviceId, std::shared_ptr<CompletionListener<bool>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraTurnOffArmLight(uint32_t deviceId, bool turnOffArmLight, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 联动变焦开关
    virtual ErrorCode GetCameraLinkageZoom(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraLinkageZoom(uint32_t deviceId, int32_t linkageZoom, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 丝滑变焦
    virtual ErrorCode GetSmoothZoom(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetSmoothZoom(uint32_t deviceId, int smoothZoom, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视觉图传
    virtual ErrorCode GetCameraVisualTransfer(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraVisualTransfer(uint32_t deviceId, int visualTransfer, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机工作模式
    virtual ErrorCode GetCameraWorkMode(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraWorkModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWorkMode(uint32_t deviceId, CameraWorkModeEnum cameraWorkModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机拍照子模式
    virtual ErrorCode GetCameraWorkModeTakePhoto(uint32_t deviceId, std::shared_ptr<CompletionListener<TakePhotoModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWorkModeTakePhoto(uint32_t deviceId, TakePhotoModeEnum takePhotoModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机录像子模式
    virtual ErrorCode GetCameraWorkModeVideo(uint32_t deviceId, std::shared_ptr<CompletionListener<RecordModeEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWorkModeVideo(uint32_t deviceId, RecordModeEnum recordModeEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像风格类型
    virtual ErrorCode GetCameraImageStyleType(uint32_t deviceId, std::shared_ptr<CompletionListener<ImageStyleEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraImageStyleType(uint32_t deviceId, ImageStyleEnum imageStyleEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像风格亮度
    virtual ErrorCode GetCameraImageStyleBrightness(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraImageStyleBrightness(uint32_t deviceId, int imageStyleBrightness, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像风格对比度
    virtual ErrorCode GetCameraImageStyleContrast(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraImageStyleContrast(uint32_t deviceId, int imageStyleContrast, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像风格饱和度
    virtual ErrorCode GetCameraImageStyleSaturation(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraImageStyleSaturation(uint32_t deviceId, int imageStyleSaturation, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像风格色度
    virtual ErrorCode GetCameraImageStyleHue(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraImageStyleHue(uint32_t deviceId, int imageStyleHue, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图像风格锐度
    virtual ErrorCode GetCameraImageStyleSharpness(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraImageStyleSharpness(uint32_t deviceId, int imageStyleSharpness, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 白平衡参数模式
    virtual ErrorCode GetCameraWhiteBalanceType(uint32_t deviceId, std::shared_ptr<CompletionListener<WhiteBalanceEnum>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWhiteBalanceType(uint32_t deviceId, WhiteBalanceEnum whiteBalanceEnum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 白平衡参数色温
    virtual ErrorCode GetKeyCameraWhiteBalanceColorTemp(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetKeyCameraWhiteBalanceColorTemp(uint32_t deviceId, int whiteBalanceColorTemp, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // PIV录像状态是否开启
    virtual ErrorCode GetCameraPivEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraPivEnable(uint32_t deviceId, int32_t pivEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // PIV录像状态间隔时间
    virtual ErrorCode GetCameraPivInterval(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraPivInterval(uint32_t deviceId, int pivInterval, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 透雾功能配置是否开启
    virtual ErrorCode GetCameraDehazeEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraDehazeEnable(uint32_t deviceId, int dehazeEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 透雾功能配置，透雾强度
    virtual ErrorCode GetCameraDehazeStrength(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraDehazeStrength(uint32_t deviceId, int dehazeStrength, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像模式类型
    virtual ErrorCode GetCameraIrImageModeType(uint32_t deviceId, std::shared_ptr<CompletionListener<ThermalImageMode>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrImageModeType(uint32_t deviceId, int irImageModeType, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像模式对比度
    virtual ErrorCode GetCameraIrImageModeContrast(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrImageModeContrast(uint32_t deviceId, int irImageModeContrast, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像模式亮度
    virtual ErrorCode GetCameraIrImageModeLum(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrImageModeLum(uint32_t deviceId, int irImageModeLum, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像增强 使能
    virtual ErrorCode GetCameraIrEnhanceEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrEnhanceEnable(uint32_t deviceId, int irEnhanceEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像图像增强 强度
    virtual ErrorCode GetCameraIrEnhanceStrength(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrEnhanceStrength(uint32_t deviceId, int irEnhanceStrength, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度属性 测温模式
    virtual ErrorCode GetCameraIrTempAttrType(uint32_t deviceId, std::shared_ptr<CompletionListener<TemperatureMode>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempAttrType(uint32_t deviceId, int irTempAttrType, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度属性 指点测温坐标
    virtual ErrorCode GetCameraIrTempAttrTouch(uint32_t deviceId, std::shared_ptr<CompletionListener<ParameterPointInfo>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempAttrTouch(uint32_t deviceId, int irTempAttrTouch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度属性 区域测温
    virtual ErrorCode GetCameraIrTempAttrRegion(uint32_t deviceId, std::shared_ptr<CompletionListener<ParameterRectInfo>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempAttrRegion(uint32_t deviceId, int irTempAttrRegion, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度属性 限制测温
    virtual ErrorCode GetCameraIrTempAttrLimitTemp(uint32_t deviceId, std::shared_ptr<CompletionListener<ParameterRectInfo>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempAttrLimitTemp(uint32_t deviceId, int irTempAttrLimitTemp, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度告警属性 使能
    virtual ErrorCode GetCameraIrTempAlarmEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempAlarmEnable(uint32_t deviceId, int32_t irTempAlarmEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度告警属性 高温度阈值
    virtual ErrorCode GetCameraIrTempAlarmHotThreshold(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempAlarmHotThreshold(uint32_t deviceId, int irTempAlarmHotthred, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温度告警属性 低温温度阈值
    virtual ErrorCode GetCameraIrTempAlarmColdThreshold(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempAlarmColdThreshold(uint32_t deviceId, int irTempAlarmColdthred, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 电子防抖开关
    virtual ErrorCode GetCameraElectronicAntiShaking(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraElectronicAntiShaking(uint32_t deviceId, int32_t electronicAntiShaking, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 任务文件夹名称
    virtual ErrorCode GetCameraSaveMapTaskName(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraSaveMapTaskName(uint32_t deviceId, std::string saveMapTaskName, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 用户自定义文件夹名称
    virtual ErrorCode GetCameraSaveMapUserDirName(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraSaveMapUserDirName(uint32_t deviceId, std::string saveMapUserDirName, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 快速变焦
    virtual ErrorCode GetCameraTypeXoomFixedFactor(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraTypeXoomFixedFactor(uint32_t deviceId, int typeXoomFixedFactor, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机数据加密开关
    virtual ErrorCode GetCameraTypeEncryptEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;

    // 相机自定义调试
    virtual ErrorCode GetCameraDebugEvent(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraDebugEvent(uint32_t deviceId, int debugEvent, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视觉相机录像开关
    virtual ErrorCode GetCameraRecordEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraRecordEnable(uint32_t deviceId, int32_t recordEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视觉相机录像帧率
    virtual ErrorCode GetCameraRecordFps(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraRecordFps(uint32_t deviceId, int recordFps, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视觉相机录像时长
    virtual ErrorCode GetCameraRecordDuration(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraRecordDuration(uint32_t deviceId, int recordDuration, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视觉相机录像保存数量
    virtual ErrorCode GetCameraRecordNumber(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraRecordNumber(uint32_t deviceId, int recordNumber, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机能力集版本号获取
    virtual ErrorCode GetCameraCapabilityVersion(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraCapability>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraCapabilityVersion(uint32_t deviceId, CameraCapability capabilityVersion, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机开关
    virtual ErrorCode GetCameraEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraEnable(uint32_t deviceId, int32_t enable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机水印GPS开关
    virtual ErrorCode GetCameraWatermarkGpsEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWatermarkGpsEnable(uint32_t deviceId, int32_t watermarkGpsEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机水印SN开关
    virtual ErrorCode GetCameraWaterMarkSnEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWaterMarkSnEnable(uint32_t deviceId, int32_t waterMarkSnEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机视觉开关
    virtual ErrorCode GetCameraVisualEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraVisualEnable(uint32_t deviceId, int32_t visualEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 拍照录像超感光开关
    virtual ErrorCode GetCameraUltraPixelEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraUltraPixelEnable(uint32_t deviceId, int32_t ultraPixelEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图传视频编码类型 需要和录像视频编码类型区分
    virtual ErrorCode GetCameraTransferPayLoadType(uint32_t deviceId, std::shared_ptr<CompletionListener<VideoCompressStandard>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraTransferPayLoadType(uint32_t deviceId, VideoCompressStandard transferPayLoadType, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 实时传输模式
    virtual ErrorCode GetCameraTransferMode(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraTransferMode(uint32_t deviceId, int transferMode, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图传流gop
    virtual ErrorCode GetCameraTransferGop(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraTransferGop(uint32_t deviceId, int transferGop, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
   
    // 图传流seI使能
    virtual ErrorCode GetCameraTransferSeiEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraTransferSeiEnable(uint32_t deviceId, int transferSeiEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 图传视频编码类型 需要和录像视频编码类型区分
    virtual ErrorCode GetCameraPreviewResolution(uint32_t deviceId, std::shared_ptr<CompletionListener<CameraPreviewResolution>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraPreviewResolution(uint32_t deviceId, CameraPreviewResolution previewResolution, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 水印机型显示开关
    virtual ErrorCode GetCameraWaterMarkDroneSwitch(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWaterMarkDroneSwitch(uint32_t deviceId, int s32Switch, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 水印位置: 0-左上，1-左下，2-右上，3-右下
    virtual ErrorCode GetCameraWaterMarkLayout(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraWaterMarkLayout(uint32_t deviceId, int waterMarkLayout, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    
    // 热成像温宽拉伸开关
    virtual ErrorCode GetCameraIrTempSpanEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempSpanEnable(uint32_t deviceId, int spanEnable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温宽拉伸热点温度(摄氏度*10)
    virtual ErrorCode GetCameraIrTempSpanHotThreshold(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempSpanHotThreshold(uint32_t deviceId, int spanHot, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 热成像温宽拉伸冷点温度(摄氏度*10)
    virtual ErrorCode GetCameraIrTempSpanColdThreshold(uint32_t deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraIrTempSpanColdThreshold(uint32_t deviceId, int spanCold, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 视频/拍照存储类型获取
    virtual ErrorCode GetCameraVideoPictureStorageType(uint32_t deviceId, const VideoPhotoStorageInfo& info, std::shared_ptr<CompletionListener<VideoPhotoStorageListInfo>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SetCameraVideoPictureStorageType(uint32_t deviceId, const VideoPhotoStorageListInfo& videoPhotoStorageListInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
 
    // 重启相机
    virtual ErrorCode RebootCamera(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // SD卡格式化
    virtual ErrorCode FormatSDCard(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // MMC机载闪存格式化
    virtual ErrorCode FormatMMC(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 恢复出厂设置
    virtual ErrorCode ResetCamera(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 开始拍照
    virtual ErrorCode StartTakePhoto(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止拍照
    virtual ErrorCode StopTakePhoto(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 开始录像
    virtual ErrorCode StartRecord(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 停止录像
    virtual ErrorCode StopRecord(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // FFC快门
    virtual ErrorCode CameraFfc(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 相机数据加密设置
    virtual ErrorCode SetEncryptionType(uint32_t deviceId, const CameraEncryptSetInfo& encryptInfo, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // ==========消息监听类接口==========
    // 相机状态消息上报
    virtual ErrorCode ListenCameraStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CameraStatus>> listener) = 0;
    virtual void CancelListenCameraStatus(uint32_t deviceId, ObjectId objectId) = 0;

    virtual ErrorCode ListenKeyDisplayMode(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<int>> listener) = 0;
    virtual void CancelListenKeyDisplayMode(uint32_t deviceId, ObjectId objectId) = 0;

    virtual ErrorCode ListenStorageStatusReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CardStatusBean>> listener) = 0;
    virtual void CancelListenStorageStatusReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 专业参数信息上报
    virtual ErrorCode ListenProfessionalParamInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<ProfessionalParamInfo>> listener) = 0;
    virtual void CancelListenProfessionalParamInfo(uint32_t deviceId, ObjectId objectId) = 0;

    // 拍照文件信息上报
    virtual ErrorCode ListenPhotoFileInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<PhotoFileInfo>> listener) = 0;
    virtual void CancelListenPhotoFileInfo(uint32_t deviceId, ObjectId objectId) = 0;

    // 拍照状态上报
    virtual ErrorCode ListenTakePhotoStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<TakePhotoStatusInfo>> listener) = 0;
    virtual void CancelListenTakePhotoStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // 录像状态上报
    virtual ErrorCode ListenRecordStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<RecordStatusInfo>> listener) = 0;
    virtual void CancelListenRecordStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // 录像文件信息上报
    virtual ErrorCode ListenRecordFileInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<RecordFileInfo>> listener) = 0;
    virtual void CancelListenRecordFileInfo(uint32_t deviceId, ObjectId objectId) = 0;

    // SD卡状态上报
    virtual ErrorCode ListenSDCardStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CardStatusBean>> listener) = 0;
    virtual void CancelListenSDCardStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // MMC状态上报
    virtual ErrorCode ListenMMCStatusInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CardStatusBean>> listener) = 0;
    virtual void CancelListenMMCStatusInfo(uint32_t deviceId, ObjectId objectId) = 0;

    // 定时拍倒计时上报
    virtual ErrorCode ListenIntervalShotStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<int>> listener) = 0;
    virtual void CancelListenIntervalShotStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // 全景状态上报
    virtual ErrorCode ListenPanoramaStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<PanoramaStatusInfo>> listener) = 0;
    virtual void CancelListenPanoramaStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // 延时摄影状态上报
    virtual ErrorCode ListenDelayShotStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<DelayShotStatusInfo>> listener) = 0;
    virtual void CancelListenDelayShotStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // 重置相机状态上报
    virtual ErrorCode ListenResetCameraState(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<bool>> listener) = 0;
    virtual void CancelListenResetCameraState(uint32_t deviceId, ObjectId objectId) = 0;

    // AE/AF状态改变
    virtual ErrorCode ListenAeAfStatusChange(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CameraAFAEStatusInfo>> listener) = 0;
    virtual void CancelListenAeAfStatusChange(uint32_t deviceId, ObjectId objectId) = 0;

    // 温度报警事件
    virtual ErrorCode ListenTempAlarm(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<TempAlarmInfo>> listener) = 0;
    virtual void CancelListenTempAlarm(uint32_t deviceId, ObjectId objectId) = 0;

    // 移动延时摄影状态
    virtual ErrorCode ListenMotionDelayShotStatus(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<MotionDelayShotInfo>> listener) = 0;
    virtual void CancelListenMotionDelayShotStatus(uint32_t deviceId, ObjectId objectId) = 0;

    // 相机曝光状态
    virtual ErrorCode ListenPhotoExposure(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<Exposure>> listener) = 0;
    virtual void CancelListenPhotoExposure(uint32_t deviceId, ObjectId objectId) = 0;

    // 任务录制航点信息上报
    virtual ErrorCode ListenMissionRecordWaypoint(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<MissionRecordWaypointInfo>> listener) = 0;
    virtual void CancelListenMissionRecordWaypoint(uint32_t deviceId, ObjectId objectId) = 0;

    // AF相机对焦状态上报
    virtual ErrorCode ListenAFState(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<AFStateEnum>> listener) = 0;
    virtual void CancelListenAFState(uint32_t deviceId, ObjectId objectId) = 0;

    // 相机模式切换上报
    virtual ErrorCode ListenCameraModeSwitch(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CameraModeSwitchInfo>> listener) = 0;
    virtual void CancelListenCameraModeSwitch(uint32_t deviceId, ObjectId objectId) = 0;

    // 显示模式切换上报
    virtual ErrorCode ListenDisplayModeSwitch(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<DisplayMode>> listener) = 0;
    virtual void CancelListenDisplayModeSwitch(uint32_t deviceId, ObjectId objectId) = 0;

    // 红外相机温度信息上报
    virtual ErrorCode ListenInfraredCameraTempInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<InfraredCameraTempInfo>> listener) = 0;
    virtual void CancelListenInfraredCameraTempInfo(uint32_t deviceId, ObjectId objectId) = 0;

    // 存储状态信息上报
    virtual ErrorCode ListenStorageStatusInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<StorageStatusInfo>> listener) = 0;
    virtual void CancelListenStorageStatusInfo(uint32_t deviceId, ObjectId objectId) = 0;

    // 点测光上报
    virtual ErrorCode ListenLocationMeterInfo(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<MeteringPointInfo>> listener) = 0;
    virtual void CancelListenLocationMeterInfo(uint32_t deviceId, ObjectId objectId) = 0;

    // 白平衡参数上报
    virtual ErrorCode ListenWhiteBalanceReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<WhiteBalanceInfo>> listener) = 0;
    virtual void CancelListenWhiteBalanceReport(uint32_t deviceId, ObjectId objectId) = 0;

    // AELock信息上报
    virtual ErrorCode ListenAeLockReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<bool>> listener) = 0;
    virtual void CancelListenAeLockReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 聚焦信息上报
    virtual ErrorCode ListenFocusReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<FocusInfo>> listener) = 0;
    virtual void CancelListenFocusReport(uint32_t deviceId, ObjectId objectId) = 0;

    // HDR信息上报
    virtual ErrorCode ListenHdrReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<bool>> listener) = 0;
    virtual void CancelListenHdrReport(uint32_t deviceId, ObjectId objectId) = 0;

    // ROI配置上报
    virtual ErrorCode ListenRoiReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<ROIInfo>> listener) = 0;
    virtual void CancelListenRoiReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 相机拍照分辨率信息上报
    virtual ErrorCode ListenPhotoResolutionReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<PhotoResolutionInfo>> listener) = 0;
    virtual void CancelListenPhotoResolutionReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 相机录像分辨率信息上报
    virtual ErrorCode ListenVideoResolutionReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<VideoResolutionInfo>> listener) = 0;
    virtual void CancelListenVideoResolutionReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 解密进度上报
    virtual ErrorCode ListenCameraEncryptProgressReportReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CameraEncryptProgressReportInfo>> listener) = 0;
    virtual void CancelListenCameraEncryptProgressReportReport(uint32_t deviceId, ObjectId objectId) = 0;

    // 相机图传信息上报
    virtual ErrorCode ListenCameraTransferInfoReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CameraTransferInfo>> listener) = 0;
    virtual void CancelListenCameraTransferInfoReport(uint32_t deviceId, ObjectId objectId) = 0;

    // EIS参数上报
    virtual ErrorCode ListenCameraEisReport(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<CameraEisReportInfo>> listener) = 0;
    virtual void CancelListenCameraEisReport(uint32_t deviceId, ObjectId objectId) = 0;
};
}  // namespace AutelMobileSdk

#endif
