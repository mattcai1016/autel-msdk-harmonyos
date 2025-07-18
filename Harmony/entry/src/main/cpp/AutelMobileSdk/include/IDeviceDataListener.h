#ifndef IDEVICE_DATA_LISTENER_H
#define IDEVICE_DATA_LISTENER_H

#include <stdint.h>
#include <unordered_map>

#include "DeviceDataType.h"
#include "Common.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IGimbalDataListener
{
public:
    IGimbalDataListener() {};
    virtual ~IGimbalDataListener() {};

public:
    virtual void OnReport(DeviceId deviceId, GimbalData gimbalData) = 0;
};

class AUTELSDK_API IDroneDataListener
{
public:
    IDroneDataListener() {};
    virtual ~IDroneDataListener() {};

public:
    virtual void OnReport(const std::unordered_map<DeviceId, DroneStateData>& gimbalData) = 0;
};

class IFlightControlDataListener
{
public:
    IFlightControlDataListener() {};
    virtual ~IFlightControlDataListener() {};

public:
    virtual void OnReport(DeviceId deviceId, const FlightControlData& flightControlData) = 0;
};
} // namespace AutelMobileSdk

#endif
