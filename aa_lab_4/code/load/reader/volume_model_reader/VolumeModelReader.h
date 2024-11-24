#pragma once

#include "Reader.h"
#include "Vector3.h"
#include <vector>

class VolumeModelReader : public Reader
{
public:
    virtual ~VolumeModelReader() = 0;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() = 0;

    virtual void readData() = 0;
    // virtual std::vector<psPoint3> getVertices() = 0;
    virtual std::vector<std::vector<psPoint3>> getFaces() = 0;
    virtual Point3 getCenter() = 0;
};
