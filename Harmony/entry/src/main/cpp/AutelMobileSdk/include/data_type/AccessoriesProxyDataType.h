#ifndef ACCESSORIES_PROXY_DATA_TYPE_H
#define ACCESSORIES_PROXY_DATA_TYPE_H

#include <string>
#include <vector>

namespace AutelMobileSdk
{
enum class ThrowingGearActionType
{
    UNKNOWN = -1,
    NO_THROW = 0,
    ACTION_THROW,
};

struct JettisionGearControl
{
    int moduleId = 0;
    std::vector<ThrowingGearActionType> actions;

    std::string ToString() const;
};

struct JettisionGearStatus
{
    int moduleId = 0;
    std::vector<bool> validFlags;
    std::vector<bool> throwFlags;

    std::string ToString() const;
};
} // namespace AutelMobileSdk

#endif
