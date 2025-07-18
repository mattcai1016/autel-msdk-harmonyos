#ifndef AI_TRACK_KEY_DATA_TYPE_H
#define AI_TRACK_KEY_DATA_TYPE_H

#include <string>

namespace AutelMobileSdk
{


//选择跟踪目标
struct TrackTargetRectangle
{
    float startX; //ROI起始x坐标
    float startY; //ROI起始y坐标
    float width; //ROI框width
    float height; //ROI框height

    std::string ToString() const;
};

} // namespace AutelMobileSdk

#endif
