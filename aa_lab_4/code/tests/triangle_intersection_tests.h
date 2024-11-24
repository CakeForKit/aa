#pragma once

#include <gtest/gtest.h>
#include "Triangle.h"

struct triangle_intersect_data_t {
    Triangle tr;
    Ray ray;
    bool isIntersect;
    double t;
};

const triangle_intersect_data_t triangle_intersect_data[] {
    {
        // Треугольник - в плоскости XOY. Луч || OZ. Пересекает внутри
        Triangle(Point3(1, 3, 0), Point3(3, 1, 0), Point3(-1, -1, 0)),
        Ray(Point3(0, 0, 10), Vector3(0, 0, -10)),
        true,
        10.0
    },
    {
        // Треугольник - в плоскости XOY. Луч || OZ. Пересекает в вершине треугольника
        Triangle(Point3(1, 3, 0), Point3(3, 1, 0), Point3(-1, -1, 0)),
        Ray(Point3(-1, -1, 10), Vector3(0, 0, -10)),
        true,
        10.0
    },
    {
        // Треугольник - в плоскости XOY. Луч || OZ. Пересекает грань треульника
        Triangle(Point3(1, 3, 0), Point3(3, 1, 0), Point3(-1, -1, 0)),
        Ray(Point3(0, 1, 10), Vector3(0, 0, -10)),
        true,
        10.0
    },
    {
        // Треугольник - в плоскости XOY. Луч || XOY. Не пересекает. 
        Triangle(Point3(1, 3, 0), Point3(3, 1, 0), Point3(-1, -1, 0)),
        Ray(Point3(0, 0, 10), Vector3(0, 1, 0)),
        false,
        0.0
    },
    {
        // Треугольник - в плоскости XOY. Луч || OZ. Не пересекает
        Triangle(Point3(1, 3, 0), Point3(3, 1, 0), Point3(-1, -1, 0)),
        Ray(Point3(3, 3, 10), Vector3(0, 0, -10)),
        false,
        0.0
    },
    {
        // Треугольник - в плоскости XOY. Луч под углом к плоскости. Пересекает внутри в (1, 1, 0)
        Triangle(Point3(1, 3, 0), Point3(3, 1, 0), Point3(-1, -1, 0)),
        Ray(Point3(0, 0, 4), Vector3(1, 1, -4)),
        true,
        4.242640
    },
};