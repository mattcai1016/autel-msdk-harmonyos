#ifndef IDRONE_LISTENER_H
#define IDRONE_LISTENER_H

#include <stdint.h>
#include <unordered_map>
#include <set>
#include <memory>
#include "BaseType.h"
#include "DeviceDataType.h"
#include "NetworkingDataType.h"
#include "IKeyListener.h"

namespace AutelMobileSdk
{
struct SDKErrorUtil
{
};

class AUTELSDK_API IDroneListener
{
public:
    IDroneListener();
    virtual ~IDroneListener();

public:
    virtual void OnDroneChanged(DeviceId deviceId, bool connected, bool hasNetworkedDrone);
    virtual void OnCaremaAbilityChanged(bool localFetched, bool remoteFetched, DeviceId deviceId);
    virtual void OnMainServiceChanged(bool valid, uint32_t deviceId);
    virtual void OnSDKError(const SDKErrorInfo& errorInfo);

protected:
};

class INetworkedDeviceListChangedListener
{
public:
    virtual void OnNetworkedDeviceListChanged(const std::unordered_map<DeviceId, DeviceInfoBean>& droneList,
        const std::unordered_map<DeviceId, DeviceInfoBean>& rcList) = 0;
};



class IDeviceListChangedListener
{
public:
    virtual void OnDeviceListChanged(DeviceChangeType changeType) = 0;
};

class INetworkedDeviceListener
{
public:
    virtual ~INetworkedDeviceListener(){}
    // 受控状态发生改变
    virtual void OnDeviceControlModeChanged(JoystickControlMode mode) = 0;

    // 单控下进行设备切换
    virtual void SingleControlDroneDeviceChanged(uint32_t deviceId) = 0;

    // watch设备发现变化（1.启动时，2.watch设备列表发生变化时）
    virtual void OnWatchedDroneChanged(const std::set<uint32_t>& drones) = 0;
};

class INetworkedDeviceChangedListener
{
public:
    virtual ~INetworkedDeviceChangedListener() {}

public:
    // 在线飞机列表更新
    virtual void OnDroneDeviceChanged(const std::unordered_map<DeviceId, DeviceInfoBean>& newDroneList) = 0;

    // 在线遥控器列表更新
    virtual void OnRemoteDeviceChanged(const std::unordered_map<DeviceId, DeviceInfoBean>& newRcList) = 0;

    // 设备列表单控，多控状态更新
    virtual void OnControlModeChanged(JoystickControlMode mode) = 0;

    virtual void SingleControlDroneChanged(const DeviceInfoBean devInfo) = 0;

    // 1. 首次获取到watch列表
    // 2. 主遥控删除watch飞机
    // 3. 设备发现watch飞机变化时
    virtual void OnWatchedDroneChanged(const std::unordered_map<DeviceId, DeviceInfoBean>& droneList) = 0;
};
} // namespace AutelMobileSdk

#endif
