#include "reflect_refract_tests.h"

class TestReflect : public testing::TestWithParam<reflect_data_t> {};

TEST_P(TestReflect, Reflect) {
    reflect_data_t tdata = GetParam();

    Vector3 vout = tdata.vin.reflect(tdata.norm);
    EXPECT_TRUE(vout == tdata.vout);
}

INSTANTIATE_TEST_SUITE_P(
    ReflectTestSuite,
    TestReflect,
    testing::Values(reflect_data[0], reflect_data[1], reflect_data[2], 
                    reflect_data[3], reflect_data[4])
);



class TestRefract : public testing::TestWithParam<refract_data_t> {};

TEST_P(TestRefract, Refract) {
    refract_data_t tdata = GetParam();

    Vector3 vout = tdata.vin.refract(tdata.norm, tdata.refrIndFrom, tdata.refrIndTo);
    // std::cout << "Vout = " << vout << "\n";
    EXPECT_TRUE(vout == tdata.vout);
}

INSTANTIATE_TEST_SUITE_P(
    RefractTestSuite,
    TestRefract,
    testing::Values(refract_data[0], refract_data[1], refract_data[2])
);
