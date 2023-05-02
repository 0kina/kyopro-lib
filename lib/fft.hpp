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
 * @example fft_example.cpp
 */

#ifndef OKINA_FFT
#define OKINA_FFT

#include <cassert>
#include <complex>
#include <cmath>
#include <vector>

class FFT {
  using func = std::vector<std::complex<double>>;
public:
  /**
   * @brief 関数のDFTを求める。
   *
   * @param base_func 関数。
   * @param is_invert IDFTを求める場合はtrue。
   * @return base_funcのDFT。
   */
  static func dft(const func &base_func, bool is_invert) {
    int sz = base_func.size();
    if (sz == 1) return base_func;
    func f0(sz / 2), f1(sz / 2);
    for (int i = 0; i < sz / 2; ++i) {
      f0[i] = base_func[i * 2];
      f1[i] = base_func[i * 2 + 1];
    }
    func ft_f0 = dft(f0, is_invert); // f0のDFT
    func ft_f1 = dft(f1, is_invert); // f1のDFT
    std::complex<double> zeta = std::polar(1.0, 2 * std::acos(-1) / sz * (is_invert ? -1 : 1));
    std::complex<double> pow_zeta = 1.0;

    func ft_f(sz); // fのDFT
    for (int i = 0; i < sz; ++i) {
      ft_f[i] = ft_f0[i % (sz / 2)] + pow_zeta * ft_f1[i % (sz / 2)];
      pow_zeta *= zeta;
    }
    return ft_f;
  }

  /**
   * @brief 2つの多項式を畳み込む
   * @param f 1つ目の多項式。
   * @param g 2つ目の多項式。
   * @return std::vector<double> 畳み込み結果の多項式。
   */
  template <typename T>
  static std::vector<double> multiply(const std::vector<T> &f, const std::vector<T> &g) {
    assert(f.size() == g.size());
    int sz = 1;
    while (sz < f.size() + g.size()) sz *= 2;
    func complex_f(sz, 0.0), complex_g(sz, 0.0);
    for (int i = 0; i < f.size(); ++i) {
      complex_f[i] = f[i];
      complex_g[i] = g[i];
    }

    func ft_f = dft(complex_f, false);
    func ft_g = dft(complex_g, false);

    func ft_fg = ft_f;
    for (int i = 0; i < sz; ++i) {
      ft_fg[i] *= ft_g[i];
    }

    func fg = dft(ft_fg, true);

    std::vector<double> res(sz);
    for (int i = 0; i < sz; ++i) {
      res[i] = fg[i].real() / sz;
    }

    return res;
  }
}; // class FFT

#endif // OKINA_FFT