#ifndef ICAMERA_SUPPORT_H
#define ICAMERA_SUPPORT_H

#include <list>
#include <vector>
#include <string>

#include "CameraBaseType.h"
#include "CameraKeyDataType.h"
#include "Common.h"

namespace AutelMobileSdk
{
class AUTELSDK_API ICameraSupport
{
public:
    ICameraSupport();
    ICameraSupport(const ICameraSupport&) = delete;
    ICameraSupport(ICameraSupport&&) = delete;
    ICameraSupport operator=(const ICameraSupport&) = delete;
    ICameraSupport operator=(ICameraSupport&&) = delete;

    virtual ~ICameraSupport();
public:
    /**
     * 返回当前支持的有效视频分辨率和帧率列表
     * @param lensType lens type enum
     * @param flightMode flight mode enum
     * @param recordMode recording mode enum
     * @return video resolution frame data list
     */
    virtual std::list<VideoResolutionFrame> GetResolutionAndFrameRate(LensType lensType, FlightMode flightMode, RecordMode recordMode);

    /**
    * 返回支持HDR对应的相片分辨率列表
    * @param flightMode flight mode enum
    * @param photoFormat photo output format enum
    * @param mode camera mode enum
    * @return list of all photo resolution list
    */
    virtual std::list<PhotoResolutionType> GetHDRSupportPhoto(FlightMode flightMode, PhotoFormat photoFormat, CameraMode cameraMode);

    /**
    * 返回当前有效的相机模式(CameraMode).
    * @param lensType lens type enum
    * @param flightMode flight mode enum and by default manual
    * @param mode take photo mode enum and by default unknown
    * @return camera mode list
    */
    virtual std::vector<CameraMode> GetCameraModeRange(LensType lensType, FlightMode flightMode = FlightMode::Manual, TakePhotoMode takePhotoMode = TakePhotoMode::Unknown);

    /**
    * 返回手动变焦的 min max step的数值范围   "Default": {"Min": 1,"Max": 50,"Step": 1 }
    * @return range with min, max and step value
    */
    virtual IntRange GetManualFocus();

    /**
    * 返回相机变焦的尺寸
    * @param lensType lens type enum
    * @return range with min, max and step value
    */
    virtual IntRange GetPhotoZoom(LensType lensType);

    /**
    * 返回视频变焦的尺寸
    * @param lensType lens type enum
    * @param videoZoomType video zoom type and by default as Default enum
    * @return range with min, max and step value
    */
    virtual IntRange GetVideoZoom(LensType lensType, VideoZoomType videoZoomType = VideoZoomType::Default);

    /**
    * 返回水印和时间戳的取值列表
    * @param lensType lens type enum
    * @param photoFormat photo output format enum
    * @return time stamp in integer value
    */
    virtual int GetWatermarkTimestamp(LensType lensType, PhotoFormat photoFormat);

    /**
    * 返回当前有效的相机曝光模式(ExposureMode).
    * @return Exposure modes in list
    */
    virtual std::vector<ExposureMode> GetExposureModeRange();

    /**
    * 返回当前有效的曝光补偿范围(ExposureExposureCompensation).
    * @return exposure compensations in list
    */
    virtual std::vector<ExposureCompensation> GetExposureCompensationRange();

    /**
    * 返回当前有效的相机ISO范围 (ImageISO).
    * @param isPhoto photo or not defined with boolean
    * @param pattern camera pattern enum and by default Manual flight
    * @param mode Take photo mode enum by default Unknown
    * @return image ISO enums list
    */
    virtual std::vector<ImageISO> GetImageISOList(bool isPhoto = true, CameraPattern pattern = CameraPattern::ManualFlight,
        TakePhotoMode mode = TakePhotoMode::Unknown);

    /**
    * 返回当前有效的相机ISO模式列表 (ISOMode).
    * @return image ISO enums list
    */
    virtual std::list<IsoMode> GetPhotoISOModeRange();

    /**
    * 返回当前有效的相机ISO模式列表 (ISOMode).
    * @return ISOMode list
    */
    virtual std::list<IsoMode> GetVideoISOModeRange();

    /**
    * 返回当前有效的相机快门速度范围
    * @param isPhoto photo or not
    * @param mode take photo mode enum and by default unknown
    * @return ShutterSpeeds list
    */
    virtual std::vector<ShutterSpeed> GetShutterList(bool isPhoto, int fps, TakePhotoMode mode = TakePhotoMode::Unknown);

    /**
    * 返回当前相机光圈可设置的范围
    * @return Lris enum list
    */
    virtual std::vector<Lris> GetApertureRange();

    /**
    * 返回当前相机视频格式可选择的范围
    * @param lensType lens type enum
    * @return video format enum list
    */
    virtual std::list<VideoFormat> GetVideoFileFormatRange(LensType lensType);

    /**
    * 返回当前相机录像时拍照间隔的可选择的范围
    * @param lensType lens type enum
    * @return video piv enum list
    */
    virtual std::list<VideoPiv> GetPicInVideoIntervalRange(LensType lensType);

    /**
    * 返回当前相机视频标准可选择的范围
    * @param lensType lens type enum
    * @return video standard
    */
    virtual std::list<VideoStandard> GetVideoStandardRange(LensType lensType);

    /**
    * 返回当前相机拍照图片格式可选择范围.
    * @param lensType lens type enum
    * @param mode take photo mode state
    * @return photo formatted enum list
    */
    virtual std::list<PhotoFormat> GetPhotoFileFormatRange(LensType lensType, TakePhotoMode mode);

    /**
    * 返回当前相机快拍张数可选择范围
    * @param lensType lens type enum
    * @return count list send
    */
    virtual std::list<int> GetPhotoBurstCountRange(LensType lensType);

    /**
        * 返回当前相机AEB拍摄张数可选择范围.
        * @return photo count list send
        */
    virtual std::list<int> GetPhotoAEBCaptureCountRange();

    /**
    * 返回当前相机定时拍摄时间可选择范围.
    * @param lensType lens type enum
    * @return lens type list
    */
    virtual std::list<int> GetPhotoIntervalParamRange(LensType lensType = LensType::Zoom);

    /**
    * 返回当前相机白平衡可选择范围.
    * @return white balances enum list
    */
    virtual std::vector<WhiteBalance> GetWhiteBalanceList();

    /**
    * 返回当前相机白平衡自定义色温值范围.
    * @return range step int value
    */
    virtual IntRange GetCustomColorTemperatureRange();

    /**
    * 返回当前相机透雾模式范围.
    * @return defog mode enum list
    */
    virtual std::list<DefogMode> GetDehazeModeRange();

    /**
    * 返回当前相机透雾使能状态可选择范围.
    * @return defog mode enum list
    */
    virtual std::list<Defog> GetDehazeSettingSwitchRange();

    /**
    * 返回当前相机透雾使能状态可选择范围.
    * @return defog mode enum list
    */
    virtual std::list<Defog> GetDehazeSettingSwitchMergeRange();

    /**
    * 返回当前相机抗闪烁模式可选择范围.
    * @return anti flicker range list
    */
    virtual std::list<int> GetAntiFlickerRange();

    /**
    * transferMode 是图传的清晰度: 1 是流畅 720p, 2是高清 1080p, 3是超高清  2.7K
    * @return video transmission mode enum list
    */
    virtual std::list<VideoTransMissionMode> GetTransferMode();

    /**
    * 返回当前相机图像分辨率可选择范围.
    * @param lensType lens type enum
    * @param flightMode flight mode enum
    * @param mode take photo mode enum and by default unknown
    * @return photo resolution enum list
    */
    virtual std::list<PhotoResolutionValue> GetPhotoResolution(LensType lensType, FlightMode flightMode, TakePhotoMode mode);

    /**
    * 返回当前相机图像分辨率可选择范围.无对应枚举 返回UNKNOWN后 重新获取相册分辨率列表
    * @param lensType lens type enum
    * @param flightMode flight mode enum
    * @param mode take photo mode enum and by default unknown
    * @return photo resolution list
    */
    virtual std::list<PhotoResolutionValue> GetPhotoResolutionTwice(LensType lensType, FlightMode flightMode, TakePhotoMode mode);

    /**
    * 回当前相机锐度可选择范围.
    * @param mode take photo mode enum and by default unknown
    * @return list of integer
    */
    virtual std::list<int> GetSharpnessRange(TakePhotoMode mode);

    /**
    *  返回当前相机对比度可选择范围.
    *  @param mode take photo mode enum and by default unknown
    *  @return list of integer
    */
    virtual std::list<int> GetContrastRange(TakePhotoMode mode);

    /**
    *  返回当前相机饱和度可选择范围.
    *  @param mode take photo mode enum and by default unknown
    *  @return list of integer
    */
    virtual std::list<int> GetSaturationRange(TakePhotoMode mode);

    /**
    *  返回当前相机对焦模式可选择范围.
    *  @param mode take photo mode enum and by default unknown
    *  @return list of integer
    */
    virtual std::list<int> GetLensFocusModeRange(CameraMode mode);

    /**
    *  返回当前相机支持的热成像伪彩信息.
    *  @return thermal color enum list
    */
    virtual std::list<ThermalColor> SupportedIrColor();

    /**
    * 返回热成像图测温模式.
    * @return IR temp mode enum
    */
    virtual std::list<IRTempMode> GetThermalIRTempMode();

    /**
    * 返回热成像图像模式.
    * @return Ir image mode object
    */
    virtual IrImageMode GetThermalIrImageMode();

    /**
    * 返回热成像图像增强.
    * @return range step int value object
    */
    virtual IntRange GetThermalIrImageEnhance();

    /**
    * 返回热成像图像去噪.
    * @return list of integer
    */
    virtual std::list<int> GetThermalIrNr();

    /**
    * 返回热成像图像去噪.
    * @return Ir gain object
    */
    virtual IrGain GetIrGain();

    /**
    * 返回热成像等温线.
    * @return list of integer
    */
    virtual std::list<int> GetIrIsoThermMode();

    /**
    * 返回热成像温度告警.
    * @return IR hot cold value
    */
    virtual IRHotColdValue GetIrTempAlarm();

    /**
    * 返回热成像辐射.
    * @return range step int value object
    */
    virtual IntRange GetIrNrEmit();

    /**
    * 返回当前相机支持的视频文件压缩标准.
    * @return video compress standard enum
    */
    virtual std::list<VideoCompressStandard> GetVideoFileCompressionStandard();

    /**
    * 返回当前相机支持的存储类型.
    * @param lensType lens type enum
    * @return storage type enums list
    */
    virtual std::list<StorageType> GetStorageType(LensType lensType);

    /**
    * Getting version of camera
    */
    virtual std::string GetVersion();

    /**
    *  @return 返回当前类型相机的ID.
    *  @param 相机类型
    *  @param 云台类型
    */
    virtual int GetCameraID(LensType lensType, std::string gimbal);

    /**
    *  @return 返回当前类型相机的播放器端口ID.
    */
    virtual int GetPlayerID(LensType lensType);

protected:
};
}

#endif
