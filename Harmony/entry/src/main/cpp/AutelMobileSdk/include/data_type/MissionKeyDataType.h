#ifndef MISSION_KEY_DATA_TYPE_H
#define MISSION_KEY_DATA_TYPE_H

#include <string>
#include "Common.h"

namespace AutelMobileSdk
{
struct AUTELSDK_API MissionSwarmInfo
{
    int missionId;
    int startTime;

    std::string ToString() const;
};
} // namespace AutelMobileSdk

#endif
