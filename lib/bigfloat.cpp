#include "bigint.hpp"

using namespace std;

class BigFloat : BigInt {
protected:
    uint32_t _pre;
public:
    BigFloat();
    BigFloat(const vector<digit_t>&, const uint32_t, const  uint32_t, const uint8_t);
    BigFloat(const BigInt&);
    BigFloat(const BigFloat&);

    const uint32_t precision() const;

    string as_string() const;

    BigFloat inversed() const;

    void clear();

    friend BigFloat operator+(const BigFloat&, const BigFloat&);

    friend BigFloat operator-(const BigFloat&, const BigFloat&);

    friend BigFloat operator*(const BigFloat&, const BigFloat&);

    friend BigFloat operator/(const BigFloat&, const BigFloat&);

    friend ostream& operator<<(ostream&, const BigFloat&);

    BigFloat& operator=(const BigFloat&);

    friend bool operator>(const BigFloat&, const BigFloat&);

    friend bool operator==(const BigFloat& lh, const BigFloat& rh);
};

BigFloat::BigFloat() : BigInt(), _pre(0) {}

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

string BigFloat::as_string() const {
    string s1 = "";
    string s = s1.append((this->_pre > this->_size ? this->_pre - this->_size : 0), '0') + this->BigInt::as_string();

    s.insert(s.end() - this->_pre, '.');
    return s;
}

void BigFloat::clear() {
    this->BigInt::clear();
    this->_pre = 0;
}

BigFloat operator+(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = BigFloat(lh).shift(max(lh._pre, rh._pre) - lh._pre);
    BigInt R = BigFloat(rh).shift(max(lh._pre, rh._pre) - rh._pre);
    BigFloat result(L + R);
    result._pre = max(lh._pre, rh._pre);
    return result;
}

BigFloat operator-(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = BigFloat(lh).shift(max(lh._pre, rh._pre) - lh._pre);
    BigInt R = BigFloat(rh).shift(max(lh._pre, rh._pre) - rh._pre);
    BigFloat result(L - R);
    result._pre = max(lh._pre, rh._pre);
    return result;
}

BigFloat operator*(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = BigFloat(lh).shift(max(lh._pre, rh._pre) - lh._pre);
    BigInt R = BigFloat(rh).shift(max(lh._pre, rh._pre) - rh._pre);
    BigFloat result(L * R);
    result._pre = lh._pre + rh._pre;
    return result;
}

BigFloat BigFloat::inversed() const {
    BigInt one(vector<digit_t>(1, 1), 1, BigInt::Positive);
    one.shift(this->_pre * 2);
    BigInt denominator = BigFloat(*this).shift(0);
    BigFloat temp(one / denominator);
    temp._pre = this->_pre;
    return temp;
}

BigFloat operator/(const BigFloat& lh, const BigFloat& rh) {
    BigFloat R = rh.inversed();
    return lh * R;
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
    BigInt L = BigFloat(lh).shift(max(lh._pre, rh._pre));
    BigInt R = BigFloat(rh).shift(max(lh._pre, rh._pre));
    return L > R;
}

bool operator==(const BigFloat& lh, const BigFloat& rh) {
    BigInt L = BigFloat(lh).shift(max(lh._pre, rh._pre));
    BigInt R = BigFloat(rh).shift(max(lh._pre, rh._pre));
    return L == R;
}
