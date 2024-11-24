#pragma once

#include "Vector3.h"
#include "Color.h"
#include <assert.h>

class Drawer
{   
public:
    virtual ~Drawer() = default;

    virtual int getImgWidth() = 0;
    virtual int getImgHeight() = 0;

    virtual void setPixelColor(int x, int y, const Color &color) = 0;
    virtual void setPixelColor(int x, int y, const Color &&color) = 0;
    virtual void setScene() = 0;
};