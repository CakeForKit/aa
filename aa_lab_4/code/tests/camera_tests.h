#pragma once

#include <gtest/gtest.h>
#include <initializer_list>
#include <vector>

#include "Camera.h"

struct ij_coord_t {
    int i; int j;
    Point3 expectCoord;
};

struct camera_test_data_t {
    float focalLength;
    float viewportHeight;
    size_t countPixelsWidth;
    size_t countPixelsHeight;
    Vector3 cameraPos;
    std::vector<ij_coord_t> res;
};

const camera_test_data_t camera_test_data[] = {
    {
        10, 100, 6, 4, Vector3(0, 0, 10), 
        {
            {0, 0, Point3(-75 + 12.5, 50 - 12.5, 0)},
            {5, 0, Point3(-75 + 12.5 + 25 * 5, 50 - 12.5, 0)},
            {0, 3, Point3(-75 + 12.5, 50 - 12.5 - 25 * 3, 0)},
            {5, 3, Point3(-75 + 12.5 + 25 * 5, 50 - 12.5 - 25 * 3, 0)},
            // {3, 1, Point3(-75 + 12.5+ 25 * 3, 50 - 12.5 - 25 * 1, 0)},
        }
    }
};