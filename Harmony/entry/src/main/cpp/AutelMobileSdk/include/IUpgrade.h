#ifndef IUPGRADE_H
#define IUPGRADE_H

#include "ErrorCode.h"
#include "KeyListener.h"
#include "CompletionListener.h"
#include "UpgradeKeyDataType.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IUpgrade
{
public:
    // ======= 设置类接口 =======
    // 升级条件查询
    virtual ErrorCode CheckCanSystemUpgrade(uint32_t deviceId, const UpgradeQuery &param, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    // 进入升级状态
    virtual ErrorCode UpgradeEnter(uint32_t deviceId, const UpgradeEnterMsg &param, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    // 产品包传输进度
    virtual ErrorCode UpgradeTransferProgress(uint32_t deviceId, const UpgradeTransfer &param, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    // 产品包文件校验
    virtual ErrorCode UpgradeCheck(uint32_t deviceId, const UpgradeCheckMsg &param, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    // 开始升级
    virtual ErrorCode UpgradeExecute(uint32_t deviceId, const UpgradeExecuteReq &param, std::shared_ptr<CompletionListener<int>> listener, int retryCount = 0) = 0;
    // 执行组件恢复
    virtual ErrorCode ExecuteComponentRecorver(uint32_t deviceId, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    // 查询升级状态
    virtual ErrorCode QueryUpgradeState(uint32_t deviceId, std::shared_ptr<CompletionListener<UpgradeState>> listener, int retryCount = 0) = 0;
    // ======= 通知类接口 =======
    // 升级总进度通知
    virtual ErrorCode ListenUpgradeProgressNtfy(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<int>>& listener) = 0;
    virtual void CancelListenUpgradeProgressNtfy(uint32_t deviceId, ObjectId objectId) = 0;
    // 升级结果通知
    virtual ErrorCode ListenUpgradeResultNtfy(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<UpgradeResult>>& listener) = 0;
    virtual void CancelListenUpgradeResultNtfy(uint32_t deviceId, ObjectId objectId) = 0;
    // 组件一致性检查警告通知
    virtual ErrorCode ListenUpgradeComponentCheckNtfy(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<DroneVersionInfo>>& listener) = 0;
    virtual void CancelListenUpgradeComponentCheckNtfy(uint32_t deviceId, ObjectId objectId) = 0;
    // 升级前条件判断结果通知
    virtual ErrorCode ListenUpgradeQueryNtfy(uint32_t deviceId, ObjectId objectId, std::shared_ptr<KeyListener<int>>& listener) = 0;
    virtual void CancelListenUpgradeQueryNtfy(uint32_t deviceId, ObjectId objectId) = 0;
};

}

#endif // IUPGRADE_H

