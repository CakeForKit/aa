#include "camera_tests.h"

class TestCamera : public testing::TestWithParam<camera_test_data_t> {};

TEST_P(TestCamera, StandartBasis) {
    camera_test_data_t tdata = GetParam();

    Camera cam;
    cam.setFocalLength(tdata.focalLength, false);
    cam.setViewportHeight(tdata.viewportHeight, false);
    cam.setCameraPos(tdata.cameraPos, false);
    cam.setCountPixelsViewport(tdata.countPixelsWidth, tdata.countPixelsHeight);

    std::vector<ij_coord_t> dataRes = tdata.res;
    for (ij_coord_t elem : dataRes) {
        Ray ray = cam.createRay(elem.i, elem.j);
        Vector3 excpectDir = elem.expectCoord - tdata.cameraPos;
        excpectDir.normalize();
        EXPECT_TRUE(excpectDir == ray.getDirection());
    }
}



INSTANTIATE_TEST_SUITE_P(
    CameraTestSuite,
    TestCamera,
    testing::Values(camera_test_data[0])
);
