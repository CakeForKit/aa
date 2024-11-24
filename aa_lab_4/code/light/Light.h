#pragma once

#include "Vector3.h"
#include "Color.h"

enum class typeLight
{
    AMBIENT,
    POINT
};

class Light
{
public:
    Light(Intensity &&intensColor);
    virtual ~Light() = 0;

    virtual const Intensity getIntensity() const noexcept;
    virtual bool getPos(Point3 &p) const noexcept = 0;
    typeLight getType() const noexcept { return type; }

protected:
    typeLight type;
    Intensity intensColor;
};

class AmbientLight : public Light
{
public:
    AmbientLight();

    virtual bool getPos(Point3 &p) const noexcept;
};


/// @brief Точечный источник света
class PointLight : public Light
{
protected:
    Point3 pos;

public:
    PointLight();
    // PointLight(Point3 &&_pos, Color &&_color, double _intensity);

    virtual bool getPos(Point3 &p) const noexcept;
};

