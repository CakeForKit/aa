#pragma once

#include "Vector3.h"

class Ray
{
protected:
    Point3 orig;
    Vector3 dir;

public:
    Ray(const Point3 &origin, const Vector3 &direction) noexcept;
    Ray(const Point3 &&origin, const Vector3 &&direction) noexcept;
    Ray(const Ray &ray) noexcept;
    Ray(Ray &&ray) noexcept;

    Point3 getOrigin() const noexcept;
    Vector3 getDirection() const noexcept;
    Point3 operator()(double t) const noexcept;

    Ray& operator=(const Ray &r) noexcept;
    Ray& operator=(Ray &&r) noexcept;
};

std::ostream& operator<<(std::ostream &os, const Ray &ray);

