#include <gtest/gtest.h>
#include "bigfloat.h"

using namespace longarithmetic;

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
    EXPECT_EQ(-876543.21_bf, -BigFloat(888888888, 3) + BigFloat(12345678, 3));
}

TEST(OperationsCase, subtraction_1) {
    EXPECT_EQ(0_bf, 56_bf - 42_bf - 4_bf - 10_bf);
}

TEST(OperationsCase, subtraction_2) {
    EXPECT_EQ(179998.2225_bf, 200000_bf - 20001.7775_bf);
}

TEST(OperationsCase, subtraction_3) {
    EXPECT_EQ(-4.0001_bf, -2.0001_bf - 2_bf);
}

TEST(OperationsCase, subtraction_4) {
    EXPECT_EQ(-876543.21_bf, -BigFloat(888888888, 3) + BigFloat(12345678, 3));
}

TEST(OperationsCase, multiplying_1) {
    EXPECT_EQ(0.0_bf, 78246.5555_bf * 0_bf);
}

TEST(OperationsCase, multiplying_2) {
    EXPECT_EQ(-1000.1_bf, 1000.1_bf * -1_bf);
}

TEST(OperationsCase, multiplying_3) {
    std::vector<digit_t> digits = {31004, 36987822, 45630669, 41035555};
    EXPECT_EQ(BigFloat(digits, digits.size(), 2, BigFloat::Positive), BigFloat(8527419631495ull, 9).power(3) * 5_bf);
}

TEST(OperationsCase, division_1) {
    EXPECT_EQ(0.0_bf, 1.2_bf / 0_bf);
}

TEST(OperationsCase, division_2) {
    EXPECT_EQ(2.12_bf, -2.12_bf / -1.0_bf);
}

TEST(OperationsCase, division_3) {
    EXPECT_EQ(BigFloat(66666666667ull, 8), 2000.0_bf / 3_bf);
}