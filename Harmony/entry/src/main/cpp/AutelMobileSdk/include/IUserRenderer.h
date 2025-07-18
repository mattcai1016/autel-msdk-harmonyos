#ifndef IUSER_RENDERER_H
#define IUSER_RENDERER_H

//#include <QImage>
#include <stdio.h>

#include "Common.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IUserRenderer
{
public:
    enum Format{
        Format_RGBA8888 = 17, // == QImage::Format_RGBA8888
        Format_Grayscale8 = 24 // == QImage::Format_Grayscale8
    };
public:
    //virtual void UpdateImage(QImage image) = 0;
    virtual void UpdateImage(const void* data, int width, int height, int format) = 0;
};
}

#endif
