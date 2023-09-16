#pragma once
/**
 * @file weighted_union_find.hpp
 * @brief 重み付きUnionFindに関するコード
 * @details
 * 可換群であれば重みとして扱える．
 * * Validation
 *   * https://atcoder.jp/contests/abc320/submissions/45655566
 */

#include <functional>
#include <numeric>
#include <vector>

template <typename T>
class WeightedUnionFind {
public:
  WeightedUnionFind(
    int n, T identity_elem,
    const std::function<T(T, T)> &op,
    const std::function<T(T, T)> &inv_op
  ) : par_(n), siz_(n, 1), diff_weight_(n, identity_elem),
      identity_elem_(identity_elem), op_(op), inv_op_(inv_op) {
    std::iota(par_.begin(), par_.end(), 0);
  }

  int root(int x) {
    if (par_[x] == x) {
      return x;
    }
    int r = root(par_[x]);
    diff_weight_[x] = op_(diff_weight_[x], diff_weight_[par_[x]]);
    return par_[x] = r;
  }

  bool is_same(int x, int y) {
    return root(x) == root(y);
  }

  T weight(int x) {
    root(x);
    return diff_weight_[x];
  }

  /**
   * @brief `weight(y)` - `weight(x)`を返す．
   */
  T diff(int x, int y) {
    return inv_op_(weight(y), weight(x));
  }

  /**
   * @brief weight(y) - weight(x) = wとなるようにxとyをマージする．
   * @return すでにx, yが同じグループに属する場合は`false`, そうでなければ`true`.
   */
  bool unite(int x, int y, T w) {
    w = op_(w, weight(x)); w = inv_op_(w, weight(y));
    x = root(x), y = root(y);
    if (x == y) return false;
    if (siz_[x] < siz_[y]) {
      std::swap(x, y);
      w = inv_op_(identity_elem_, w);
    }
    par_[y] = x;
    siz_[x] += siz_[y];
    diff_weight_[y] = w;
    return true;
  }

  int size(int x) {
    return siz_[root(x)];
  }

private:
  std::vector<int> par_, siz_;
  std::vector<T> diff_weight_;
  T identity_elem_;
  std::function<T(T, T)> op_, inv_op_;
}; // class WeightedUnionFind
