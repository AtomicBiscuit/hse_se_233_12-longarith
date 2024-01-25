#include <deque>
#include <vector>
#include <cstdint>
#include <stdexcept>

using namespace std;

using digit_t = unsigned char;


class BigInt {
private:
    vector<digit_t> digits;
    uint32_t _size;
    uint8_t _sign;
public:
    BigInt();

    BigInt(const vector<digit_t>&, const uint32_t, const uint8_t);

    BigInt(const BigInt&);

    const uint32_t size() const;

    const uint8_t sign() const;

    const vector<digit_t>& as_array() const;

    friend BigInt operator+(const BigInt&, const BigInt&);
};

BigInt::BigInt() :digits({ 0 }), _size(1), _sign(0) {}

BigInt::BigInt(const vector<digit_t>& dig, const uint32_t size, const uint8_t sign) :digits(dig), _size(size), _sign(sign) {}

BigInt::BigInt(const BigInt& obj) {
    this->digits = vector<digit_t>(obj.digits);
    this->_size = obj.size();
    this->_sign = obj.sign();
}

const uint32_t BigInt::size() const {
    return this->_size;
}

const uint8_t BigInt::sign() const {
    return this->_sign;
}

const vector<digit_t>& BigInt::as_array() const {
    return this->digits;
}