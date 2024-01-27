#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

class BigInt {
protected:
    std::vector<unsigned char> digits;
    uint32_t _size;
    uint8_t _sign;
    friend BigInt add(const BigInt&, const BigInt&);
public:
    BigInt();

    BigInt(const std::vector<unsigned char>&, uint32_t, uint8_t);

    BigInt(const BigInt&);

    static const uint32_t MAX_SIZE = 50000;

    enum eSign { Positive, Negative };

    virtual const uint32_t size() const;

    virtual const uint8_t sign() const;

    virtual const std::vector<unsigned char> & as_array() const;

    virtual std::string as_string() const;

    virtual BigInt shift(int32_t) const;

    virtual void clear();

    friend BigInt operator+(const BigInt&, const BigInt&);

    friend BigInt operator-(const BigInt&);

    friend BigInt operator-(const BigInt&, const BigInt&);

    friend BigInt operator*(const BigInt&, const BigInt&);

    friend BigInt operator*(const BigInt&, const uint8_t&);

    friend BigInt operator/(const BigInt&, const BigInt&);

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    BigInt& operator=(const BigInt&);

    friend bool operator>(const BigInt&, const BigInt&);

    friend bool operator==(const BigInt& lh, const BigInt& rh);

    friend bool greater_with_absolute(const BigInt&, const BigInt&);
};