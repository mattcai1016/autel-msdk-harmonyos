#ifndef IDEVICE_MNG_H
#define IDEVICE_MNG_H

#include <list>
#include <memory>
#include "ErrorCode.h"
#include "IDeviceListener.h"
#include "ICameraListener.h"
#include "IKeyManager.h"
#include "NetworkingDataType.h"
#include "CompletionListener.h"
#include "KeyListener.h"

namespace AutelMobileSdk
{
// DeviceManager的以下接口待实现：
// addDroneDevicesListener
// removeDroneDevicesListener

class AUTELSDK_API IDeviceMng
{
public:
    IDeviceMng() {};
    virtual ~IDeviceMng() {};

public:
    // 组网相关接口
    //开始组网(CreateDeviceNetworkReq.isContinue = 0初次创建非续时 1非初次创建需续时)
    virtual ErrorCode StartNetworkingMatching(const CreateDeviceNetworkReq& netMashReq, bool startMatch, std::shared_ptr<CompletionListener<CreateDeviceNetworkResp>> listener, int retryCount = 0) = 0;
    //删除组网设备
    virtual ErrorCode DelNetworkedDevice(DeviceId deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    //设置中继节点
    virtual ErrorCode SetCenterNode(DeviceId deviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    //加入组网(从遥控器加入)
    virtual ErrorCode JoinNetworking(const JoinDeviceNetworkReq& request, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    //完成组网
    virtual ErrorCode CompleteNetworkingMatching(std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    //解散组网(主遥控器当前创建的组网进行解散)
    virtual ErrorCode DismissNetworkingMatching(int64_t groupId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    //退出组网(从遥控器退出当前组网)
    virtual ErrorCode QuitNetworkingMatching(int64_t groupId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    //设置组网名称
    virtual ErrorCode SetTeamName(const std::string& name, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    //设置组网设备名称
    virtual ErrorCode SetMemberDeviceName(DeviceId deviceId, const std::string& name, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;

    virtual ErrorCode GetNetworkingInviteCode(std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode SelectMultiControlDevices(const std::vector<DeviceId>& selectDeviceList, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;     // 多设备摇杆控制
    
    /**
     * @brief 多控模式切换图传
     * @param selectDeviceList 选择的设备列表
     * @param listener 回调监听器
     * @return 1:成功  2:失败  0:未知
     * @note 弃用接口
     */
    virtual ErrorCode SelectVideoSourceDevices(const std::vector<DeviceId>& selectDeviceList, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;      // 多控模式切换图传
    
    /**
     * @brief 多控模式切换图传
     * @param selectedDeviceInfo 选择的设备信息
     * @param listener 回调监听器
     * @return 1:成功  2:失败  0:未知
     */
    virtual ErrorCode SelectVideoSourceDevices(const SelectedDeviceInfo& selectedDeviceInfo, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;      // 多控模式切换图传
    
    virtual ErrorCode SwtichVideoSourceDevice(DeviceId selectDeviceId, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;                           // 单选模式下，切换飞机图传
    virtual ErrorCode SwitchDeviceControlMode(const SwitchDroneDeviceBean& devices, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;         // 统一切换飞机控制
    virtual ErrorCode GetDeviceControlMode(std::shared_ptr<CompletionListener<JoystickControlMode>> listener, int retryCount = 0) = 0;    // 组网配对状态监听
    virtual ErrorCode SetNetworkingStreamControl(const std::vector<CameraStreamInfo>& streamList, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    virtual ErrorCode DismissTeam() = 0;

    // 多设备操作接口
    virtual ErrorCode GetValue(const std::vector<DeviceId>& deviceList, std::shared_ptr<IAutelKey>& key, std::shared_ptr<IMultiDevCompletionListener>& listener, int retryCount = 0) = 0;
    virtual ErrorCode SetValue(const std::vector<DeviceId>& deviceList, std::shared_ptr<IAutelKey>& key, const std::any& param, std::shared_ptr<IMultiDevCompletionListener>& listener, int retryCount = 0) = 0;
    virtual ErrorCode PerformAction(const std::vector<DeviceId>& deviceList, std::shared_ptr<IAutelKey>& key, const std::any& param, std::shared_ptr<IMultiDevCompletionListener>& listener, int retryCount = 0) = 0;

    // 设备信息获取
    //获取设备信息列表
    virtual std::unordered_map<DeviceId, DeviceInfoBean> GetDevicesInfo() = 0;
    virtual std::set<DeviceId> GetDroneList(DroneType type) = 0;
    virtual std::set<DeviceId> GetRCList() = 0;
    virtual std::set<DeviceId> GetMultiControlDroneList() = 0;
    virtual DeviceId GetSingleControlDroneId() const = 0;
    virtual DeviceId GetLocalRCId() = 0;
    virtual DeviceId GetMainRCId() = 0;
    virtual DeviceId GetCenterDroneId() = 0;
    virtual std::string GetLocalRCName() = 0;
    virtual std::string GetMainRCName() = 0;
    virtual JoystickControlMode GetJoystickControlMode() = 0;
    virtual std::set<DeviceId> GetConnectedDrones() = 0;
    virtual std::shared_ptr<IKeyManager> GetKeyManager(DeviceId deviceId) = 0;
    virtual bool IsMainRC() = 0;
    virtual bool IsLocalRCNetworked() = 0;
    virtual bool IsDroneConnected(DeviceId deviceId) = 0;
    virtual bool HasDroneConnected() = 0;
    virtual bool GetDroneState(DeviceId, DroneStateData & droneState) = 0;

    // 无人机状态变化监听
    virtual ErrorCode AddDroneListener(ObjectId objectId, std::shared_ptr<IDroneListener>& listener) = 0;
    virtual void RemoveDroneListener(ObjectId objectId) = 0;

    // 相机变化监听
    virtual ErrorCode AddCameraListener(ObjectId objectId, std::shared_ptr<ICameraListener>& listener) = 0;
    virtual void RemoveCameraListener(ObjectId objectId) = 0;

    // 设备列表变化监听
    virtual ErrorCode AddDeviceListChangedListener(ObjectId objectId, std::shared_ptr<IDeviceListChangedListener>& listener) = 0;
    virtual void RemoveDeviceListChangedListener(ObjectId objectId) = 0;

    // 组网设备变化监听
    virtual ErrorCode AddNetworkedDeviceListener(ObjectId objectId, std::shared_ptr<INetworkedDeviceListener> listener) = 0;
    virtual void RemoveNetworkedDeviceListener(ObjectId objectId) = 0;

    // 组网设备变化监听
    virtual ErrorCode AddNetworkedDeviceChangedListener(ObjectId objectId, std::shared_ptr<INetworkedDeviceChangedListener> listener) = 0;
    virtual void RemoveNetworkedDeviceChangedListener(ObjectId objectId) = 0;

    // 组网设备列表变化监听
    virtual ErrorCode AddNetworkedDeviceListChangedListener(ObjectId objectId, std::shared_ptr<INetworkedDeviceListChangedListener>& listener) = 0;
    virtual void RemoveNetworkedDeviceListChangedListener(ObjectId objectId) = 0;

    // 组网配对状态监听
    virtual ErrorCode AddNetworkingMatchingListener(ObjectId objectId, std::shared_ptr<KeyListener<DeviceNetworkBeanStatus>> listener) = 0;
    virtual void RemoveNetworkingMatchingListener(ObjectId objectId) = 0;

    // 中心结点变化监听
    virtual ErrorCode AddCenterNodeChangeListener(ObjectId objectId, std::shared_ptr<KeyListener<DeviceNetworkCenterNodeStatus>> listener) = 0;
    virtual void RemoveCenterNodeChangeListener(ObjectId objectId) = 0;

    // 上报组网设备列表监听
    virtual ErrorCode AddNetworkedDeviceReportListener(ObjectId objectId, std::shared_ptr<KeyListener<DeviceNetworkingBean>> listener) = 0;
    virtual void RemoveNetworkedDeviceReportListener(ObjectId objectId) = 0;

    // 设备是否在网消息通知监听
    virtual ErrorCode AddDeviceNetworkingStateListener(ObjectId objectId, std::shared_ptr<KeyListener<bool>> listener) = 0;
    virtual void RemoveDeviceNetworkingStateListener(ObjectId objectId) = 0;

    // 设备多、单控制上报监听
    virtual ErrorCode AddDeviceControlModeChangeListener(ObjectId objectId, std::shared_ptr<KeyListener<ControlDronesBean>> listener) = 0;
    virtual void RemoveDeviceControlModeChangeListener(ObjectId objectId) = 0;

    // 重连设备发现
    virtual void ReconnectDeviceListReport() = 0;

    // 设置Watched飞机
    virtual bool SetWatchedDrone(uint32_t deviceId) = 0;
};
}  // namespace AutelMobileSdk

#endif
