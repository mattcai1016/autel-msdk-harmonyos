#ifndef ILET_H
#define ILET_H

#include <memory>
#include "ErrorCode.h"
#include "CompletionListener.h"

namespace AutelMobileSdk
{

// LTE模块
class AUTELSDK_API ILte
{
public:
    // ============== 参数查询、设置、操作接口 ==========
    // Lte开关
    virtual ErrorCode SetLteEnable(uint32_t devcieId, int32_t s32Enable, std::shared_ptr<CompletionListenerWithoutData> listener, int retryCount = 0) = 0;
    virtual ErrorCode GetLteEnable(uint32_t deviceId, std::shared_ptr<CompletionListener<int32_t>> listener, int retryCount = 0) = 0;
    // ============== 事件通知接口 ==========
};


} // namespace AutelMobileSdk

#endif // ILET_H
