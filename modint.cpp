#include <ostream>

template <long long mod>
class ModInt {
 public:
  ModInt<mod>(long long x) : x(static_cast<long long>(x)) {}

  ModInt<mod> & operator+=(const ModInt<mod> &right) {
    if ((x += right.x) >= mod) x -= mod;
    return *this;
  }

  ModInt<mod> & operator-=(const ModInt<mod> &right) {
    if ((x -= right.x) < 0) x += mod;
    return *this;
  }

  ModInt<mod> & operator*=(const ModInt<mod> &right) {
    (x *= right.x) %= mod;
    return *this;
  }

  ModInt<mod> & operator/=(const ModInt<mod> &right) {
    (x *= right.inv()) %= mod;
    return *this;
  }

  ModInt<mod> & inv() const {
    return pow(*this, mod - 2);
  }

  long long get_x() const {
    return x;
  }

 private:
  long long x;
};

template<long long mod>
ModInt<mod> & operator+(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res += right;
}

template<long long mod>
ModInt<mod> & operator-(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res -= right;
}

template<long long mod>
ModInt<mod> & operator*(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res *= right;
}

template<long long mod>
ModInt<mod> & operator/(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res /= right;
}

template <long long mod>
ModInt<mod> pow(const ModInt<mod> &base, const long long &exp) {
  if (!base.x) return ModInt<mod>(1);

  ModInt<mod> m = pow(base, exp / 2);
  m *= m;
  if (exp & 1) m *= base;
  return m;
}

template <long long mod>
std::ostream &operator<<(std::ostream &ost, const ModInt<mod> &m) {
  ost << m.get_x();
  return ost;
};