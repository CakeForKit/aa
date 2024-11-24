#pragma once

#include <memory>
#include "Vector3.h"
#include "Exceptions.h"
#include "Ray.h"

class Triangle
{
protected:
    /* не повторяются, не вырождаются в линию или точку */
    psPoint3 points[3];    
    // Vector3 normal; // внутренняя нормаль

public:
    Triangle(Point3 &&p1, Point3 &&p2, Point3 &&p3);
    Triangle(psPoint3 &p1, psPoint3 &p2, psPoint3 &p3);
    Triangle(Triangle &&tr) noexcept;
    explicit Triangle(const Triangle &tr);

    psPoint3 operator[](size_t ind) const;
    // Point3 &operator[](size_t ind);

    Triangle& operator=(const Triangle &tr) noexcept;
    Triangle& operator=(Triangle &&tr) noexcept;

    // сравнивает не указатели на точки а сами сочки, их координаты
    bool operator==(const Triangle &tr) const noexcept;
    bool operator!=(const Triangle &tr) const noexcept;

    /// @brief Определяет пересечение луча и данного треугольника, используя барицентрические координаты
    /// @param [in] ray - луч
    /// @param [out] t - параметр луча t из R(t) = orig + t * dir
    /// @return Есть пересечение или нет, если пересечения нет то t - не изменяется
    bool intersection(const Ray &ray, double &t) const noexcept;

    // Считает внутреннуюю нормаль к треугольнику 
    // (определяет что нормаль внутренняя за счет луча, он должен входить в плоскость)
    Vector3 getNormal(const Ray &ray) const noexcept;

    void print_debug_info();

};

std::ostream& operator<<(std::ostream &os, const Triangle &tr);

using psTriangle = std::shared_ptr<Triangle>;