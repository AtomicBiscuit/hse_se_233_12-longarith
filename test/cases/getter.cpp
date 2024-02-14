#include <gtest/gtest.h>
#include "bigfloat.h"

using namespace longarithmetic;

TEST(GettersCase, as_string_1) {
    EXPECT_EQ("132.45600000", BigFloat(132.456L).as_string());
}

TEST(GettersCase, as_string_2) {
    EXPECT_EQ("555855.", BigFloat(555855ull).as_string());
}

TEST(GettersCase, as_string_3) {
    EXPECT_EQ("0.", BigFloat(0ull).as_string());
}

TEST(GettersCase, as_string_4) {
    EXPECT_EQ(".00100000", BigFloat(0.001L).as_string());
}

TEST(GettersCase, as_string_5) {
    EXPECT_EQ("123456789.10000000", BigFloat(12345678910ull, 2).as_string());
}

TEST(GettersCase, as_string_6) {
    EXPECT_EQ("-.10000000", (-BigFloat(0.1L)).as_string());
}

TEST(GettersCase, as_array_1) {
    std::vector<digit_t> answer = {7, 89654123};
    EXPECT_EQ(answer, BigFloat(789654123ull).as_array());
}

TEST(GettersCase, as_array_2) {
    std::vector<digit_t> answer = {3, 14150000};
    EXPECT_EQ(answer, BigFloat(3.1415L).as_array());
}

TEST(GettersCase, as_integer_1) {
    EXPECT_EQ(-BigFloat(928ull), BigFloat(-928.99L).as_integer());
}

TEST(GettersCase, as_integer_2) {
    EXPECT_EQ(BigFloat(), BigFloat(0.5416L).as_integer());
}

TEST(GettersCase, precision_1) {
    EXPECT_EQ(0, BigFloat(0ull).precision());
}

TEST(GettersCase, precision_2) {
    EXPECT_EQ(8, BigFloat(0.001L).precision());
}

TEST(GettersCase, precision_3) {
    EXPECT_EQ(16, BigFloat(123, 9).precision());
}

TEST(GettersCase, sign_1) {
    EXPECT_EQ(BigFloat::Positive, BigFloat(42, 1).sign());
}

TEST(GettersCase, sign_2) {
    EXPECT_EQ(BigFloat::Negative, (-BigFloat(0.L)).sign());
}