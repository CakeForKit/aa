#include "Light.h"

Light::Light(Intensity &&intensColor)
: intensColor(intensColor) {}

Light::~Light() = default;

const Intensity Light::getIntensity() const noexcept {
    return intensColor;
}


AmbientLight::AmbientLight()
: Light(Intensity(0.1, 0.1, 0.1)) {
    type = typeLight::AMBIENT;
}

bool AmbientLight::getPos(Point3 &p) const noexcept {
    (void) p;
    return false;
}


PointLight::PointLight()
: Light(Intensity(1, 1, 1)), pos(Point3(100, 0, 100)) {
    type = typeLight::POINT;
}


bool PointLight::getPos(Point3 &p) const noexcept {
    p = pos;
    return true;
}

