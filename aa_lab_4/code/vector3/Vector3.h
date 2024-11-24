#pragma once
#include <iostream>
#include <cmath>
#include <memory>
#include "BaseException.h"
#include "config.h"



class Vector3
{
protected:
    double coord[3];

public:
    Vector3() noexcept;
    Vector3(double _x, double _y, double _z, double _w = 1) noexcept;
    Vector3(Vector3 &&v) noexcept;
    Vector3(const Vector3 &v);

    double x() const noexcept;
    double y() const noexcept;
    double z() const noexcept;
    void setX(double x) noexcept;
    void setY(double y) noexcept;
    void setZ(double z) noexcept;
    double operator[](size_t ind) const;
    double &operator[](size_t ind);

    Vector3& operator=(const Vector3 &v) noexcept;
    Vector3& operator=(Vector3 &&v) noexcept;

    bool operator==(const Vector3 &v) const noexcept;
    bool operator!=(const Vector3 &v) const noexcept;

    double scalarProduct(const Vector3 &v) const noexcept;
    Vector3 vectorProduct(const Vector3 &v) const noexcept;

    Vector3 reflect(Vector3 &norm) const;   // отражение
    Vector3 refract(Vector3 &norm, double refrIndFrom, double refrIndexTo) const;   // преломление
    
    double length() const noexcept;
    void normalize();
    Vector3 normalized()  const;

    bool isNormalized() const noexcept;
    bool isNull() const noexcept;
    bool isBelongsToLine(const Vector3 &p1, const Vector3 &p2) const noexcept;

    Vector3 operator-() const noexcept;

    Vector3 operator+(double num) const noexcept;
    Vector3 operator-(double num) const noexcept;
    Vector3 operator*(double num) const noexcept;
    Vector3 operator/(double num) const;

    Vector3 operator+(const Vector3 &v) const noexcept;
    Vector3 operator+(const Vector3 &&v) const noexcept;
    Vector3& operator+=(const Vector3 &v) noexcept;
    Vector3& operator+=(const Vector3 &&v) noexcept;

    Vector3 operator-(const Vector3 &v) const noexcept;
    Vector3 operator-(const Vector3 &&v) const noexcept;

    Vector3 operator*(const Vector3 &v) const noexcept;
    Vector3 operator*(const Vector3 &&v) const noexcept;

};

std::ostream& operator<<(std::ostream &os, const Vector3 &v);

Vector3 operator+(const double num, const Vector3& vec) noexcept;
Vector3 operator-(const double num, const Vector3& vec) noexcept;
Vector3 operator*(const double num, const Vector3& vec) noexcept;
Vector3 operator/(const double num, const Vector3& vec);

using Point3 = Vector3;
using psPoint3 = std::shared_ptr<Point3>;

using Intensity = Vector3;
