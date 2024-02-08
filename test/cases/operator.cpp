#include <gtest/gtest.h>
#include "bigfloat.h"

TEST(OperationsCase, addition_1) {
    EXPECT_EQ(100_bf, 53_bf + 43_bf + 3_bf + 1_bf);
}

TEST(OperationsCase, addition_2) {
    EXPECT_EQ(7.19_bf, 2.38_bf + 4.81_bf);
}

TEST(OperationsCase, addition_3) {
    EXPECT_EQ(0.0001_bf, 2.0001_bf + (-2_bf));
}

TEST(OperationsCase, addition_4) {
    EXPECT_EQ(-876543.21_bf, -BigFloat(888888888,3) + BigFloat(12345678, 3));
}