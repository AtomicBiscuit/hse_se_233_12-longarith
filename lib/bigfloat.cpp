#include "bigint.hpp"

using namespace std;

class BigFloat : BigInt {
protected:
    uint32_t _pre;
public:
    BigFloat();

    BigFloat(const long double);

    BigFloat(const unsigned long long);

    BigFloat(const vector<digit_t>&, const uint32_t, const  uint32_t, const uint8_t);

    BigFloat(const BigInt&);

    BigFloat(const BigFloat&);

    const uint32_t precision() const;

    const uint32_t size() const;

    const uint8_t sign() const;

    string as_string() const;

    BigInt as_integer() const;

    BigFloat shift(const int32_t) const;

    BigFloat normalized(const BigFloat&) const;

    void clear();

    friend BigFloat operator+(const BigFloat&, const BigFloat&);

    friend BigFloat operator-(const BigFloat&);

    friend BigFloat operator-(const BigFloat&, const BigFloat&);

    friend BigFloat operator*(const BigFloat&, const BigFloat&);

    friend BigFloat operator/(const BigFloat&, const BigFloat&);

    friend ostream& operator<<(ostream&, const BigFloat&);

    BigFloat& operator=(const BigFloat&);

    friend bool operator>(const BigFloat&, const BigFloat&);

    friend bool operator>=(const BigFloat&, const BigFloat&);

    friend bool operator<(const BigFloat&, const BigFloat&);

    friend bool operator<=(const BigFloat&, const BigFloat&);

    friend bool operator==(const BigFloat& lh, const BigFloat& rh);
};

BigFloat operator ""_bf(long double);

BigFloat::BigFloat() : BigInt(), _pre(0) {}

BigFloat::BigFloat(const long double val) {
    this->_sign = val < 0 ? BigFloat::Negative : BigFloat::Positive;
    string s_val = to_string(abs(val));
    this->_size = 0;
    this->_pre = 0;
    this->digits = vector<digit_t>();
    bool dot = false;
    bool not_zero = false;
    for (auto c : s_val) {
        if (c == '.') {
            dot = true;
            continue;
        } else if (c != '0') {
            not_zero = true;
        }
        if (dot) {
            ++this->_pre;
        }
        if (not_zero) {
            ++this->_size;
            this->digits.push_back(c - '0');
        }
    }
    if (this->_size == 0) {
        this->clear();
    }
}

BigFloat::BigFloat(const unsigned long long val) {
    this->_sign = BigFloat::Positive;
    this->_pre = 0;
    string s_val = to_string(val);
    this->_size = s_val.size();
    this->digits = vector<digit_t>(this->_size, 0);
    for (int32_t i = 0; i < s_val.size(); i++) {
        this->digits[i] = s_val[i] - '0';
    }
    if (this->_size == 0) {
        this->clear();
    }
}

BigFloat::BigFloat(const vector<digit_t>& dig, const uint32_t size, const uint32_t pre, const uint8_t sign) :BigInt(dig, size, sign), _pre(pre) {}

BigFloat::BigFloat(const BigInt& obj) {
    this->digits = obj.as_array();
    this->_size = obj.size();
    this->_pre = 0;
    this->_sign = obj.sign();
}

BigFloat::BigFloat(const BigFloat& obj) {
    this->digits = obj.digits;
    this->_size = obj._size;
    this->_pre = obj._pre;
    this->_sign = obj._sign;
}

const uint32_t BigFloat::precision() const {
    return this->_pre;
}

const uint32_t BigFloat::size() const {
    return this->_size;
}

const uint8_t BigFloat::sign() const {
    return this->_sign;
}

string BigFloat::as_string() const {
    string s1 = "";
    string s = s1.append((this->_pre > this->_size ? this->_pre - this->_size : 0), '0') + this->BigInt::as_string();

    s.insert(s.end() - this->_pre, '.');
    return s;
}

BigInt BigFloat::as_integer() const {
    return BigInt(this->digits, this->_size, this->_sign);
}

void BigFloat::clear() {
    this->BigInt::clear();
    this->_pre = 0;
}

BigFloat BigFloat::shift(const int32_t count) const {
    BigFloat temp(this->as_integer().shift(count));
    temp._pre = this->_pre;
    return temp;
}

BigFloat BigFloat::normalized(const BigFloat& other) const {
    BigInt temp = this->as_integer().shift(max(this->_pre, other._pre) - this->_pre);
    BigFloat result(temp);
    result._pre = max(this->_pre, other._pre) - this->_pre;
    return result;
}

BigFloat operator+(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer();
    BigInt R = rh.normalized(lh).as_integer();
    BigFloat result(L + R);
    result._pre = max(lh._pre, rh._pre);
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
    result._pre = max(lh._pre, rh._pre);
    return result;
}

BigFloat operator*(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer();
    BigInt R = rh.normalized(lh).as_integer();
    BigFloat result(L * R);
    result._pre = max(lh._pre, rh._pre);
    result = result.shift(-min(lh._pre, rh._pre));
    return result;
}

BigFloat operator/(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = lh.normalized(rh).as_integer().shift(max(lh._pre, rh._pre));
    BigInt R = rh.normalized(lh).as_integer();
    BigFloat res(L / R);
    res._pre = max(lh._pre, rh._pre);
    return res;
}

ostream& operator<<(ostream& _os, const BigFloat& obj) {
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
    BigInt L = lh.normalized(rh);
    BigInt R = rh.normalized(lh);
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
    BigInt L = lh.normalized(rh);
    BigInt R = rh.normalized(lh);
    return L == R;
}

BigFloat operator""_bf(long double data) {
    return BigFloat(data);
}

BigFloat operator""_bf(unsigned long long data) {
    return BigFloat(data);
}
