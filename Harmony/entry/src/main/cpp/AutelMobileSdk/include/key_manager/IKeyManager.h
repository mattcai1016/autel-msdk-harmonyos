#ifndef IKEY_MANAGER_H
#define IKEY_MANAGER_H

#include <memory>
#include <vector>
#include "IAutelKey.h"
#include "IKeyListener.h"
#include "ICompletionListener.h"

namespace AutelMobileSdk
{
class IKeyManager
{
public:
    IKeyManager() {}
    virtual ~IKeyManager() {}

public:
    virtual void GetValue(std::shared_ptr<IAutelKey>& key, std::shared_ptr<ICompletionListener> listener, int retryCount = 0) = 0;
    virtual void GetValueList(std::vector<std::shared_ptr<IAutelKey>>& keyList, std::shared_ptr<ICompletionListener> listener, int retryCount = 0) = 0;
    virtual void SetValue(std::shared_ptr<IAutelKey>& key, const std::any& param, std::shared_ptr<ICompletionListener> listener, int retryCount = 0) = 0;
    virtual void SetValueList(std::vector<std::shared_ptr<IAutelKey>>& keyList, const std::vector<std::any>& paramList, std::shared_ptr<ICompletionListener> listener, int retryCount = 0) = 0;
    virtual void PerformAction(std::shared_ptr<IAutelKey>& key, const std::any& param, std::shared_ptr<ICompletionListener> listener, int retryCount = 0) = 0;
    virtual void PerformAction2(std::shared_ptr<IAutelKey>& key, const std::any& param, std::shared_ptr<ICompletionListener> listener, int retryCount = 0) = 0;
    virtual void SetFrequencyReport(std::shared_ptr<IAutelKey>& key, const std::any& param) = 0;
    virtual void AddListener(ObjectId objectId, std::shared_ptr<IAutelKey>& key, std::shared_ptr<IKeyListener>& listener) = 0;
    virtual void RemoveListener(ObjectId objectId, std::shared_ptr<IAutelKey>& key) = 0;
    virtual void RemoveAllListener() = 0;
    virtual void ResetAllKeyStates() = 0;

protected:
};
} // namespace AutelMobileSdk
#endif