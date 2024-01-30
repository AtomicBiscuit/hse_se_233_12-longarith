#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <compare>

class BigFloat {
private:
    static const int32_t float_conversion_digits = 15;
    std::vector<unsigned char> digits;
    uint32_t _size;
    uint32_t _pre;
    int8_t _sign;

    static BigFloat _pure_add(const BigFloat &, const BigFloat &, const uint32_t &);

    static BigFloat _pure_mul(const BigFloat &, const BigFloat &);

    static BigFloat _pure_mul_dig(const BigFloat &, const uint8_t &);

public:
    enum eSign {
        Positive = 1, Negative = -1
    };

    BigFloat();

    explicit BigFloat(long double);

    explicit BigFloat(unsigned long long);

    BigFloat(const std::vector<unsigned char> &, uint32_t, uint32_t, int8_t);

    BigFloat(const BigFloat &);

    uint32_t precision() const;

    uint32_t size() const;

    int8_t sign() const;

    std::string as_string() const;

    const std::vector<unsigned char> &as_array() const;

    BigFloat as_integer() const;

    BigFloat shift(int32_t) const;

    BigFloat normalized(const BigFloat &) const;

    BigFloat abs() const;

    BigFloat round(const uint32_t &) const;

    BigFloat power(const uint32_t &) const;

    BigFloat root(const uint32_t &) const;

    void clear();

    friend BigFloat operator+(const BigFloat &, const BigFloat &);

    friend BigFloat operator-(const BigFloat &);

    friend BigFloat operator-(const BigFloat &, const BigFloat &);

    friend BigFloat operator*(const BigFloat &, const BigFloat &);

    static BigFloat div(const BigFloat &, const BigFloat &);

    friend BigFloat operator/(const BigFloat &, const BigFloat &);

    friend std::ostream &operator<<(std::ostream &, const BigFloat &);

    BigFloat &operator=(const BigFloat &);

    std::strong_ordering operator<=>(const BigFloat &rh) const;

    bool operator==(const BigFloat &rh) const;
};

BigFloat operator ""_bf(long double);

BigFloat operator ""_bf(unsigned long long);

BigFloat power(const BigFloat &, const uint32_t &);

BigFloat root(const BigFloat &, const uint32_t &);