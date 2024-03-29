#pragma once
/**
 * @file modint.hpp
 * @brief 素数を法とするmodに関するコード。
 * @details mod Pでの演算をサポート。
 */

#include <ostream>
#include <vector>

template <long long mod>
class ModInt {
public:
  ModInt() {
    this->x = 0;
  }

  ModInt(long long x) {
    this->x = x % mod;
    if (this->x < 0) this->x += mod;
  }

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
    // (x *= right.inv()) %= mod;
    // return *this;
    long long a = right.get_x(), b = mod, u = 1, v = 0;
    while (b) {
      long long t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }

    x = x * u % mod;
    if (x < 0) x += mod;
    return *this;
  }

  ModInt<mod> pow(const long long &exp) const {
    if (!x || exp == 0) return ModInt<mod>(1);

    ModInt<mod> m = pow(exp / 2);
    m *= m;
    if (exp & 1) m *= x;
    return m;
  }

  ModInt<mod> inv() const {
    return pow(mod - 2);
  }

  long long get_x() const {
    return x;
  }

private:
  long long x;
};

template<long long mod>
bool operator==(ModInt<mod> left, ModInt<mod> right) {
  return left.get_x() == right.get_x();
}

template<long long mod>
bool operator!=(ModInt<mod> left, ModInt<mod> right) {
  return !(left == right);
}

template<long long mod>
ModInt<mod> operator+(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res += right;
}

template<long long mod>
ModInt<mod> operator-(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res -= right;
}

template<long long mod>
ModInt<mod> operator*(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res *= right;
}

template<long long mod>
ModInt<mod> operator/(ModInt<mod> left, ModInt<mod> right) {
  ModInt<mod> res = left;
  return res /= right;
}


template <long long mod>
ModInt<mod> choose(long long n, long long k) {
  if (n < k || k < 0) return 0;
  ModInt<mod> ret(1);
  for (long long i = 0; i < k; ++i) {
    ret *= ModInt<mod>(n - i);
    ret *= ModInt<mod>(k - i).inv();
  }

  return ret;
}

/**
 * @brief 閾値以下の自然数に対し、階乗を計算。
 * @param n 階乗を求める整数の最大値。
 * @return n以下の階乗を保持する配列。
 */
template <long long mod>
std::vector<ModInt<mod>> calc_fact(int n) {
  std::vector<ModInt<mod>> fact;
  fact.push_back(1);
  fact.push_back(1);
  for (int i = 2; i <= n; ++i) fact.push_back(fact[i - 1] * ModInt<mod>(i));
  return fact;
}

/**
 * @brief 閾値以下の自然数に対し、階乗の逆数を計算。
 * @param n 階乗を求める整数の最大値。
 * @return n以下の階乗の逆数を保持する配列。
 */
template <long long mod>
void calc_inv_fact(const std::vector<ModInt<mod>> &fact, std::vector<ModInt<mod>> &inv_fact) {
  for (int i = 0; i < (int)fact.size(); ++i) inv_fact.push_back(ModInt<mod>(1) / fact[i]);
  return;
}

/**
 * @brief n choose kを計算。
 * @param n 元の総数。
 * @param k 選択する元の個数。
 * @param fact_n nの階乗。
 * @param inv_fact_k kの階乗の逆数。
 * @param inv_fact_n_minus_k (n - k)の階乗の逆数。
 * @return n choose k。
 */
template <long long mod>
ModInt<mod> choose(long long n, long long k, ModInt<mod> fact_n, ModInt<mod> inv_fact_k, ModInt<mod> inv_fact_n_minus_k) {
  if (n < k || k < 0) return 0;

  return fact_n * inv_fact_k * inv_fact_n_minus_k;
}

template <long long mod>
std::ostream &operator<<(std::ostream &ost, const ModInt<mod> &m) {
  ost << m.get_x();
  return ost;
};