#ifndef SDK_API_MANAGER_H
#define SDK_API_MANAGER_H

#include "ICamera.h"
#include "IGimbal.h"
#include "IFlightControl.h"
#include "IFlightMission.h"
#include "IFlightParams.h"
#include "IDeviceMng.h"
#include "IAirLink.h"
#include "IVision.h"
#include "IAlbum.h"
#include "ISetting.h"
#include "IMisc.h"
#include "IMissionManager.h"
#include "IAutelKeyFactory.h"
#include "ISwarmManager.h"
#include "IRCDeviceOperator.h"
#include "IAIService.h"
#include "IFileService.h"
#include "IAITrack.h"
#include "INest.h"
#include "IRtk.h"
#include "ILte.h"
#include "IUpgrade.h"
#include "IPayload.h"
#include "SdkConfig.h"

namespace AutelMobileSdk
{

class IMediaPlayerFactory;
class AUTELSDK_API SdkApiManager
{
public:
    static SdkApiManager& GetInstance();

public:
    void Init(bool isDebugMode);
    void RegisterApp();
    bool IsRegistered();
    void Destroy();

    std::string GetSdkVersion() const;
    std::string GetSdkFullVersion() const;
    bool IsSdkValidate(AuthorityState state) const;
    GimbalType GetGimbalType() const;

    std::shared_ptr<ICamera> GetCameraFunction();
    std::shared_ptr<IGimbal> GetGimbalFunction();
    std::shared_ptr<IFlightControl> GetFlightControlFunction();
    std::shared_ptr<IFlightMission> GetFlightMissionFunction();
    std::shared_ptr<IFlightParams> GetFlightParamsFunction();
    std::shared_ptr<IDeviceMng> GetDeviceFunction();
    std::shared_ptr<IMediaPlayerFactory> GetMediaPlayerFunction();
    std::shared_ptr<IAirLink> GetAirLinkFunction();
    std::shared_ptr<IVision> GetVisionFunction();
    std::shared_ptr<ISetting> GetSettingFunction();
    std::shared_ptr<IAlbum> GetAlbumFunction();
    std::shared_ptr<IMisc> GetMiscFunction();
    std::shared_ptr<IMissionManager> GetMissionManagerFunction();
    std::shared_ptr<IAutelKeyFactory> GetKeyFactoryFunction();
    std::shared_ptr<IRCDeviceOperator> GetRCDeviceFunction();
    std::shared_ptr<IAIService> GetAIServiceFunction();
    std::shared_ptr<IFileService> GetFileServiceFunction();    
    std::shared_ptr<IAITrack> GetAITrackFunction();
    std::shared_ptr<INest> GetNestFunction();
    std::shared_ptr<IRtk> GetRtkFunction();
    std::shared_ptr<ILte> GetLteFunction();
    std::shared_ptr<IUpgrade> GetUpgradeFunction();
    std::shared_ptr<IPayload> GetPayloadFunction();

    std::shared_ptr<ISwarmManager> GetSwarmFunction();

private:
    SdkApiManager(){};
    SdkApiManager(const SdkApiManager&) = delete;
    SdkApiManager(SdkApiManager&&) = delete;
    SdkApiManager& operator=(const SdkApiManager&) = delete;
    SdkApiManager& operator=(SdkApiManager&&) = delete;
};

} // namespace AutelMobileSdk

extern "C" AUTELSDK_API AutelMobileSdk::SdkApiManager* GetSdkApiManager();
extern "C" AUTELSDK_API void InitSdkApiManager(int32_t iDebugMode);
extern "C" AUTELSDK_API void DestroySdkApiManager();


#endif
