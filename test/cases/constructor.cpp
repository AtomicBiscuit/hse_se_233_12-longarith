#include <gtest/gtest.h>
#include "bigfloat.h"


TEST(ConstructorCase, empty_1) {
    EXPECT_EQ("0.", BigFloat().as_string());
}

TEST(ConstructorCase, item_1) {
    std::vector<digit_t> d = {1, 23, 45};
    auto sign = BigFloat::Negative;
    uint32_t precision = 1;
    uint32_t size = 3;
    EXPECT_EQ("-100000023.00000045", BigFloat(d, size, precision, sign).as_string());
}

TEST(ConstructorCase, item_2) {
    std::vector<digit_t> d = {0, 0, 929};
    auto sign = BigFloat::Negative;
    uint32_t precision = 4;
    uint32_t size = 3;
    EXPECT_EQ("-.00000000000000000000000000000929", BigFloat(d, size, precision, sign).as_string());
}

TEST(ConstructorCase, copy_1) {
    BigFloat a = 5555522_bf;
    EXPECT_EQ("5555522.", BigFloat(a).as_string());
}

TEST(ConstructorCase, copy_2) {
    BigFloat a = -.0000042_bf;
    EXPECT_EQ("-.00000420", BigFloat(a).as_string());
}

TEST(ConstructorCase, long_double_1) {
    EXPECT_EQ("2.71828182", BigFloat(2.7182818284L).as_string());
}

TEST(ConstructorCase, long_double_2) {
    EXPECT_EQ("-23.14069263", BigFloat(-23.1406926328L).as_string());
}

TEST(ConstructorCase, unsigned_long_long_1) {
    EXPECT_EQ("880055535.", BigFloat(880055535ull).as_string());
}

TEST(ConstructorCase, unsigned_long_long_2) {
    EXPECT_EQ("1.", BigFloat(1ull).as_string());
}

TEST(ConstructorCase, number_precision_1) {
    EXPECT_EQ("2.7182818284000000", BigFloat(27182818284, 10).as_string());
}

TEST(ConstructorCase, number_precision_2) {
    EXPECT_EQ("23.1406926328000000", BigFloat(231406926328, 10).as_string());
}