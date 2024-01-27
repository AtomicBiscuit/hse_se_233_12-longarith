#include "bigfloat.h"

BigFloat::BigFloat(): BigInt(), _pre(0){}

BigFloat::BigFloat(const long double val) {
    this->_sign = val < 0 ? BigFloat::Negative : BigFloat::Positive;
    std::string s_val = std::to_string(std::abs(val));
    this->_size = 0;
    this->_pre = 0;
    this->digits = std::vector<unsigned char>();
    bool dot = false, not_zero = false;
    for (auto c : s_val) {
        if (c == '.') {
            dot = true;
            continue;
        } else if (c != '0') {
            not_zero = true;
        }
        if (dot) {
            this->_pre++;
        }
        if (not_zero) {
            this->_size++;
            this->digits.push_back(c - '0');
        }
    }
    if (this->_size == 0) {
        this->_size = 1;
        this->digits.push_back(0);
    }
}

BigFloat::BigFloat(const unsigned long long val) {
    this->_sign = BigFloat::Positive;
    this->_pre = 0;
    std::string s_val = std::to_string(val);
    this->_size = s_val.size();
    this->digits = std::vector<unsigned char>(this->_size, 0);
    for (int32_t i = 0; i < s_val.size(); i++) {
        this->digits[i] = s_val[i] - '0';
    }
    if (this->_size == 0) {
        this->_size = 1;
        this->digits.push_back(0);
    }
}

BigFloat::BigFloat(const std::vector<unsigned char>& dig, const uint32_t size, const uint32_t pre, const uint8_t sign): \
BigInt(dig, size, sign), _pre(pre){}

BigFloat::BigFloat(const BigInt& obj): BigInt(obj), _pre(0){}

BigFloat::BigFloat(const BigFloat& obj)  : BigInt(obj) {
    this->_pre = obj._pre;
}

uint32_t BigFloat::precision() const {
    return this->_pre;
}

uint32_t BigFloat::size() const {
    return this->_size;
}

uint8_t BigFloat::sign() const {
    return this->_sign;
}

std::string BigFloat::as_string() const {
    std::string s1;
    std::string s = s1.append((this->_pre > this->_size ? this->_pre - this->_size : 0), '0') + this->BigInt::as_string();
    s.insert(s.end() - this->_pre, '.');
    return s;
}

const std::vector<unsigned char>& BigFloat::as_array() const {
    return this->digits;
}

BigInt BigFloat::as_integer() const {
    return {this->digits, this->_size, this->_sign};
}

void BigFloat::clear() {
    this->_size = 1;
    this->_pre = 0;
    this->_sign = BigInt::Positive;
    this->digits.clear();
    this->digits.push_back(0);
}

BigInt BigFloat::shift(int32_t count) const {
    return this->as_integer().shift(count);
}

BigFloat BigFloat::normalized(const BigFloat& other) const {
    return BigFloat(this->shift(static_cast<int32_t>(std::max(this->_pre, other._pre) - this->_pre)));
}

BigFloat operator+(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer();
    BigInt R = rh.normalized(lh).as_integer();
    BigFloat result(L + R);
    result._pre = std::max(lh._pre, rh._pre);
    return result;
}

BigFloat operator-(const BigFloat& lh) {
    BigFloat temp(lh);
    temp._sign = temp._sign == BigFloat::Positive ? BigFloat::Negative : BigFloat::Positive;
    return temp;
}

BigFloat operator-(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer();
    BigInt R = rh.normalized(lh).as_integer();
    BigFloat result(L - R);
    result._pre = std::max(lh._pre, rh._pre);
    return result;
}

BigFloat operator*(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer();
    BigInt R = rh.normalized(lh).as_integer();
    BigFloat result((L * R).shift(-1 * static_cast<int32_t>(std::min(lh._pre, rh._pre))));
    result._pre = std::max(lh._pre, rh._pre);
    return result;
}

BigFloat operator/(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).shift(static_cast<int32_t>(std::max(lh._pre, rh._pre)));
    BigInt R = rh.normalized(lh).as_integer();
    BigFloat res(L / R);
    res._pre = std::max(lh._pre, rh._pre);
    return res;
}

std::ostream& operator<<(std::ostream& _os, const BigFloat& obj) {
    return _os << obj.as_string();
}

BigFloat& BigFloat::operator=(const BigFloat& rh) {
    this->_sign = rh._sign;
    this->_size = rh._size;
    this->_pre = rh._pre;
    this->digits = rh.digits;
    return *this;
}

bool operator>(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer();
    BigInt R = rh.normalized(lh).as_integer();
    return L > R;
}

bool operator>=(const BigFloat& lh, const BigFloat& rh) {
    return lh > rh || lh == rh;
}

bool operator<(const BigFloat& lh, const BigFloat& rh) {
    return rh > lh;
}

bool operator<=(const BigFloat& lh, const BigFloat& rh) {
    return rh > lh || rh == lh;
}

bool operator==(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer();
    BigInt R = rh.normalized(lh).as_integer();
    return L == R;
}

BigFloat operator""_bf(long double data) {
    return BigFloat(data);
}

BigFloat operator""_bf(unsigned long long data) {
    return BigFloat(data);
}