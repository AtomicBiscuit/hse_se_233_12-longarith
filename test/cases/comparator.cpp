#include <gtest/gtest.h>
#include "bigfloat.h"

TEST(ComparasionCase, greater_1) {
    EXPECT_GT(1_bf, -1_bf);
}

TEST(ComparasionCase, greater_2) {
    EXPECT_GT(BigFloat(772233, 45), BigFloat(772232, 45));
}

TEST(ComparasionCase, less_1) {
    EXPECT_LT(-5_bf, 0_bf);
}

TEST(ComparasionCase, less_2) {
    EXPECT_LT(BigFloat(2, 1), BigFloat(20, 2).power(0));
}

TEST(ComparasionCase, less_3) {
    EXPECT_LT(BigFloat(20, 2).power(2), BigFloat(20, 2));
}

TEST(ComparasionCase, equal_1) {
    EXPECT_EQ((16_bf).root(4), 2_bf);
}

TEST(ComparasionCase, equal_2) {
    EXPECT_EQ(0_bf, (10_bf).power(1000) - (10000_bf).power(250));
}

TEST(ComparasionCase, not_equal_1) {
    EXPECT_NE(2_bf, 2_bf + BigFloat(1, 1000));
}
