#include <gtest/gtest.h>
#include "bigfloat.h"


TEST(MethodTestCase, shift_1) {
    EXPECT_EQ(85274100000000_bf, BigFloat(852741ull).shift(1));
}

TEST(MethodTestCase, shift_2) {
    EXPECT_EQ(BigFloat(12340000.0L), BigFloat(0.1234L).shift(1));
}

TEST(MethodTestCase, shift_3) {
    std::vector<digit_t> digits(101, 0);
    digits[0] = 12000000;
    EXPECT_EQ(BigFloat(digits, digits.size(), 1, BigFloat::Positive), BigFloat(.12L).shift(100));
}

TEST(MethodTestCase, shift_4) {
    EXPECT_EQ(12345678_bf, BigFloat(1234567887654321ull).shift(-1));
}

TEST(MethodTestCase, shift_5) {
    EXPECT_EQ(BigFloat(1234077753, 8), BigFloat(12340777532741234ull, 7).shift(-1));
}

TEST(MethodTestCase, abs_1) {
    EXPECT_EQ(12345678_bf, BigFloat(12345678_bf).abs());
}

TEST(MethodTestCase, normalize_1) {
    BigFloat obj1 = 123.055_bf;
    BigFloat obj2 = 41_bf;
    EXPECT_EQ(12305500000_bf, obj1.normalized(obj2));
    EXPECT_EQ(4100000000_bf, obj2.normalized(obj1));
}

TEST(MethodTestCase, normalize_2) {
    BigFloat obj1(15935748ull, 5);
    BigFloat obj2 = obj1 * BigFloat(1, 16);
    EXPECT_EQ(BigFloat(15935748000ull).shift(1), obj1.normalized(obj2));
    EXPECT_EQ(159_bf, obj2.normalized(obj1));
}

TEST(MethodTestCase, round_1) {
    EXPECT_EQ(BigFloat(123456788ull, 8), BigFloat(1234567879ull, 9).round(1));
}

TEST(MethodTestCase, round_2) {
    EXPECT_EQ(12_bf, BigFloat(12345ull, 3).round(0));
}

TEST(MethodTestCase, power_1) {
    std::vector<digit_t> digits = {138, 78627758, 57268447, 83245312};
    EXPECT_EQ(BigFloat(digits, digits.size(), 0, BigFloat::Positive), BigFloat(238ull).power(11));
}

TEST(MethodTestCase, power_2) {
    // Pre-calculated with sympy
    std::vector<digit_t> digits = {3383, 85167790, 63221676, 1086076, 36591853, 66979020, 3024851, 156741, 1941936,
                                   72805369, 62324367, 42209099, 27846392, 10493892, 80651689, 86396884, 62076568,
                                   50817282, 1034685, 75683945, 3563373, 33654082, 21936732, 31526453, 79037571,
                                   14970344, 71066386, 20143553, 32155316, 86940020, 97700854, 33688611, 16036608,
                                   20471900, 62641667};
    EXPECT_EQ(BigFloat(digits, digits.size(), 1, BigFloat::Positive), (73877484_bf + 0.184917_bf).power(34));
}

TEST(MethodTestCase, power_3) {
    EXPECT_EQ(33_bf, (33_bf).power(1));
}

TEST(MethodTestCase, power_4) {
    EXPECT_EQ(1_bf, (45_bf).power(0));
}

TEST(MethodTestCase, root_1) {
    std::vector<digit_t> digits = {54578826, 69492661, 45185029, 68890000};
    EXPECT_EQ((73877484_bf + 0.184917_bf + BigFloat(0, 16)),
              BigFloat(digits, digits.size(), 2, BigFloat::Positive).root(2));
}

TEST(MethodTestCase, root_2) {
    EXPECT_EQ(16_bf, (2_bf).power(100).root(25));
}

TEST(MethodTestCase, root_3) {
    EXPECT_EQ(2_bf, (2_bf).power(100).root(100));
}

TEST(MethodTestCase, root_4) {
    EXPECT_EQ(0_bf, (-44_bf).root(100));
}

TEST(MethodTestCase, root_5) {
    EXPECT_EQ(1_bf, (48_bf).root(0));
}

TEST(MethodTestCase, root_6) {
    EXPECT_EQ(42_bf, (42_bf).root(1));
}

TEST(MethodTestCase, invert_1) {
    EXPECT_EQ(1_bf, (2_bf).invert());
}

TEST(MethodTestCase, invert_2) {
    EXPECT_EQ(0.5_bf, (2.0_bf).invert());
}

TEST(MethodTestCase, invert_3) {
    EXPECT_EQ(0.01717842_bf, (3.8756_bf).power(3).invert());
}