#pragma once

#include <gtest/gtest.h>
#include "Vector3.h"

struct reflect_data_t {
    Vector3 vin;
    Vector3 norm;
    Vector3 vout;
};

const reflect_data_t reflect_data[] {
    {   // угол = 45 град, scalProduct(L, n) < 0
        Vector3(10, 0, 0),
        Vector3(-1, 1, 0),
        Vector3(0, 1, 0),
    },
    {   // угол = 0 град, scalProduct(L, n) < 0
        Vector3(0, -1, 0),
        Vector3(0, 1, 0),
        Vector3(0, 1, 0),
    },
    {   // угол = 90 град
        Vector3(11, 0, 0),
        Vector3(0, 13, 0),
        Vector3(1, 0, 0),
    },
    {   // угол = 45 град, scalProduct(L, n) > 0
        Vector3(10, 0, 0),
        -Vector3(-1, 1, 0),
        Vector3(0, 1, 0),
    },
    {   // угол = 0 град, scalProduct(L, n) > 0
        Vector3(0, -1, 0),
        -Vector3(0, 1, 0),
        Vector3(0, 1, 0),
    }
};

struct refract_data_t {
    Vector3 vin;
    Vector3 norm;
    Vector3 vout;
    double refrIndFrom;
    double refrIndTo;
};

const refract_data_t refract_data[] {
    {   // угол in == 30, угол out == 60, scalProduct(L, n) < 0
        Vector3(10, 10 * sqrt(3), 0),
        Vector3(0, 1, 0),
        Vector3(10, 10 / sqrt(3), 0).normalized(),
        sqrt(3),
        1
    },
    {   // угол in == 30, угол out == 60, scalProduct(L, n) > 0
        Vector3(10, 10 * sqrt(3), 0),
        -Vector3(0, 1, 0),
        Vector3(10, 10 / sqrt(3), 0).normalized(),
        sqrt(3),
        1
    },
    {   // угол in == 30, угол out == 90, scalProduct(L, n) < 0
        Vector3(10, 10 * sqrt(3), 0),
        Vector3(0, 1, 0),
        Vector3(0, 0, 0),
        1,
        0.5
    }
};

