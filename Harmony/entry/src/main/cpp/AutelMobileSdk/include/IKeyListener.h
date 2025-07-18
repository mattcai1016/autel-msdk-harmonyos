#ifndef IKEY_LISTENER_H
#define IKEY_LISTENER_H

#include <any>
#include <string>
#include "Common.h"

namespace AutelMobileSdk
{

class AUTELSDK_API IKeyListener
{
public:
    IKeyListener();
    IKeyListener(const std::string& keyName);
    virtual ~IKeyListener();

public:
    void SetKeyName(const std::string& keyName);
    virtual void OnValueChanged(const std::any& oldValue, const std::any& newValue);
    virtual void OnChannelTopicMessageReceive(const std::any& channelTopicMsg);
    virtual std::string ValueToString(const std::any& value) const;

protected:
    std::string m_keyName;
};

} // namespace AutelMobileSdk

#endif
