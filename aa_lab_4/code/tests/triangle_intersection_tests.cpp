#include "triangle_intersection_tests.h"


class TestTriangleIntersection : public testing::TestWithParam<triangle_intersect_data_t> {};

TEST_P(TestTriangleIntersection, CmpExpected) {
    triangle_intersect_data_t tdata = GetParam();

    Triangle tr(tdata.tr);
    Ray ray(tdata.ray);
    double t = -10;
    bool interscet = tr.intersection(ray, t);

    EXPECT_EQ(interscet, tdata.isIntersect);
    if (interscet) {
        EXPECT_TRUE(t - tdata.t < EPS);
    }
}

INSTANTIATE_TEST_SUITE_P(
    TriangleIntersectTestSuite,
    TestTriangleIntersection,
    testing::Values(triangle_intersect_data[0], triangle_intersect_data[1], triangle_intersect_data[2],
                    triangle_intersect_data[3], triangle_intersect_data[4], triangle_intersect_data[5])
);
