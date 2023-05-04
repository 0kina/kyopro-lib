#pragma once
/**
 * @file fft.hpp
 * @brief FFTに関するコード。
 * @details
 * ## 離散フーリエ変換(DFT)について
 * * DFT： @f$ \hat{f}(t) = \sum_{i = 0}^{n - 1} f(\zeta_n^i) t^i @f$
 * * ただし、@f$ \zeta_n @f$ は1のn乗根
 * * DFTの性質として、次の等式が成り立つ。@f$ \hat{f}(\zeta_n^{-k}) = nc_k @f$
 * * 上の性質を用いて、離散フーリエ逆変換(IDFT)が次のように計算できる
 *  * @f$ f(t) = \frac{1}{n} \sum_{i = 0}^{n - 1} \hat{f}(\zeta_n^{-i}) t^i @f$
 *
 * ## 多項式の積について
 * @f{eqnarray*}{ \widehat{g * h}(t) &=& \sum_{i = 0}^{n - 1} (g * h)(\zeta_n^i) \\
 *                               &=& \sum_{i = 0}^{n - 1} g(\zeta_n^i) h(\zeta_n^i) @f}
 * * DFTの係数は「関数をある点で評価した値」であり、「関数の積をある点で評価した値」と
 *   「2つの関数を同じ点で評価した値の積」は等しいので式変形が可能
 *
 * ## Verification
 * https://atcoder.jp/contests/atc001/submissions/41168208
 * https://atcoder.jp/contests/practice2/submissions/41168314
 * @example fft_example.cpp
 */

// #ifndef OKINA_FFT
// #define OKINA_FFT

#include <cassert>
#include <cmath>
#include <vector>

#include "../lib/modint.hpp"

class FFT {
  static constexpr long long MOD = 998244353;
  static constexpr int DIVIDE_LIMIT = 23;
  static constexpr int PRIMITIVE_ROOT = 3;
  using mint = ModInt<MOD>;

public:
  /**
   * @brief 多項式関数のDFTをNTTを用いて求める。
   *
   * @param f 多項式関数。
   * @param depth lg(fの項数)。
   * @param root MOD 998244353での2冪乗根。
   * @return fのDFT。
   */
  static std::vector<mint> ntt(const std::vector<mint> &f,
                               int depth,
                               const std::vector<mint> &root) {
    assert((int)std::pow(2, depth) == f.size());
    int sz = f.size();
    if (sz == 1) return f;
    std::vector<mint> f0(sz / 2, 0), f1(sz / 2, 0);
    for (int i = 0; i < sz / 2; ++i) {
      f0[i] = f[i * 2];
      f1[i] = f[i * 2 + 1];
    }
    std::vector<mint> ft_f0 = ntt(f0, depth - 1, root); // f0のDFT
    std::vector<mint> ft_f1 = ntt(f1, depth - 1, root); // f1のDFT
    mint zeta = root[depth];
    mint pow_zeta = 1.0;

    std::vector<mint> ft_f(sz, 0); // fのDFT
    for (int i = 0; i < sz; ++i) {
      ft_f[i] = ft_f0[i % (sz / 2)] + pow_zeta * ft_f1[i % (sz / 2)];
      pow_zeta *= zeta;
    }
    return ft_f;
  }

  /**
   * @brief 2つの多項式を畳み込む。2つの多項式の次数が等しい2冪の数であることが必要。
   * @param f 1つ目の多項式。
   * @param g 2つ目の多項式。
   * @return std::vector<double> 畳み込み結果の多項式。
   */
  template <typename T>
  static std::vector<long long> multiply(const std::vector<T> &f, const std::vector<T> &g) {
    assert(f.size() == g.size());
    int sz = 1;
    int log_sz = 0;
    while (sz < f.size() + g.size()) {
      sz *= 2;
      ++log_sz;
    }
    std::vector<mint> mint_f(sz, 0), mint_g(sz, 0);
    for (int i = 0; i < f.size(); ++i) {
      mint_f[i] = f[i];
      mint_g[i] = g[i];
    }

    std::vector<mint> root(DIVIDE_LIMIT + 1, 0);
    std::vector<mint> inv_root(DIVIDE_LIMIT + 1, 0);

    root[DIVIDE_LIMIT] = mint(PRIMITIVE_ROOT).pow((mint(MOD - 1) / mint(2).pow(DIVIDE_LIMIT)).get_x());
    inv_root[DIVIDE_LIMIT] = root[DIVIDE_LIMIT].inv();
    for (int i = DIVIDE_LIMIT - 1; i >= 0; --i) {
      root[i] = root[i + 1] * root[i + 1];
      inv_root[i] = inv_root[i + 1] * inv_root[i + 1];
    }

    std::vector<mint> ft_f = ntt(mint_f, log_sz, root);
    std::vector<mint> ft_g = ntt(mint_g, log_sz, root);

    std::vector<mint> ft_fg = ft_f;
    for (int i = 0; i < sz; ++i) {
      ft_fg[i] *= ft_g[i];
    }

    std::vector<mint> fg = ntt(ft_fg, log_sz, inv_root);

    std::vector<long long> res(sz);
    for (int i = 0; i < sz; ++i) {
      res[i] = (fg[i] / mint(sz)).get_x();
    }

    return res;
  }
}; // class FFT

// #endif // OKINA_FFT