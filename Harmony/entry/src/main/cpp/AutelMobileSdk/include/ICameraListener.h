#ifndef ICAMERA_LISTENER_H
#define ICAMERA_LISTENER_H

#include <cstdint>
#include "Common.h"

namespace AutelMobileSdk
{
class AUTELSDK_API ICameraListener
{
public:
    ICameraListener();
    virtual ~ICameraListener();

public:
    virtual void OnCameraChanged(uint32_t deviceId, int cameraId, bool connected);

protected:
};
} // namespace AutelMobileSdk

#endif
