#ifndef IRTK_H
#define IRTK_H

#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "RtkKeyDataType.h"

namespace AutelMobileSdk
{   
class AUTELSDK_API IRtk
{
public:
    // ======= 设置类接口 =======
    // 获取RTK定位是否开启
    virtual ErrorCode GetRtkLocationEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    // 设置RTK定位是否开启
    virtual ErrorCode SetRtkLocationEnable(uint32_t deviceId, int32_t param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取RTK数据源类型
    virtual ErrorCode GetRtkSignalType(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    // 设置RTK数据源类型
    virtual ErrorCode SetRtkSignalType(uint32_t deviceId, int32_t signalType, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 设置RTK开关
    virtual ErrorCode SetRtkBaseStationOnOffMsg(uint32_t deviceId, bool enable,std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 设置RTK基站模式消息
    virtual ErrorCode SetRtkBaseStationModeMsg(uint32_t deviceId, const RtkWorkModeCommand & param,std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 设置NTRIP模块是否开启
    virtual ErrorCode GetNtripModuleEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    // 设置NTRIP模块是否开启
    virtual ErrorCode SetNtripModuleEnable(uint32_t deviceId, int32_t param, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取NTRIP服务器域名
    virtual ErrorCode GetNtripDomainName(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;
    // 设置NTRIP服务器域名
    virtual ErrorCode SetNtripDomainName(uint32_t deviceId, std::string domainName, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取Ntrip挂载点
    virtual ErrorCode GetNtripMountPoint(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;
    // 设置Ntrip挂载点
    virtual ErrorCode SetNtripMountPoint(uint32_t deviceId, std::string mountPoint, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取Ntrip用户名
    virtual ErrorCode GetNtripUserName(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;
    // 设置Ntrip用户名
    virtual ErrorCode SetNtripUserName(uint32_t deviceId, std::string userName, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;

    // 获取Ntrip密码
    virtual ErrorCode GetNtripPassword(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;
    // 设置Ntrip密码
    virtual ErrorCode SetNtripPassword(uint32_t deviceId, std::string password, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    
    // 设置Ntrip服务器端口
    virtual ErrorCode SetNtripPort(uint32_t deviceId, std::string port, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    // 获取Ntrip服务器端口
    virtual ErrorCode GetNtripPort(uint32_t deviceId, std::shared_ptr<CompletionListener<std::string>> listener, int retryCount = 0) = 0;
    
    // ======= 通知类接口 =======
    // RTK基站信息上报 (见: INest::ListenNestSystemRtkReport)

    // RTCM数据发送 (暂未完成)
    virtual ErrorCode ListenRtkBaseStationRtcmDataNtfy(uint32_t deviceId, ObjectId obejctId, std::string rtcmData, std::shared_ptr<KeyListener<RtkRtcmData>> listener, int retryCount = 0) = 0;
    // 取消RTCM数据发送
    virtual ErrorCode CancelListenRtkBaseStationRtcmDataNtfy(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机RTK信息通知
    virtual ErrorCode ListenDroneRtkInfoNtfy(uint32_t deviceId, ObjectId obejctId, std::shared_ptr<KeyListener<RtkReportInfo>> listener, int retryCount = 0) = 0;
    // 取消飞机RTK信息通知
    virtual ErrorCode CancelListenDroneRtkInfoNtfy(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机RTK GPGGA信息通知
    virtual ErrorCode ListenDroneRtkGpggaNtfy(uint32_t deviceId, ObjectId obejctId, std::shared_ptr<KeyListener<RtkGpggaInfo>> listener, int retryCount = 0) = 0;
    // 取消飞机RTK GPGGA信息通知    
    virtual ErrorCode CancelListenDroneRtkGpggaNtfy(uint32_t deviceId, ObjectId obejctId) = 0;

    // 飞机RTK原始信息通知
    virtual ErrorCode ListenDroneRtkRawInfoNtfy(uint32_t deviceId, ObjectId obejctId, std::shared_ptr<KeyListener<RtkRawInfo>> listener, int retryCount = 0) = 0; 
    // 取消飞机RTK原始信息通知
    virtual ErrorCode CancelListenDroneRtkRawInfoNtfy(uint32_t deviceId, ObjectId obejctId) = 0;
};

}

#endif

