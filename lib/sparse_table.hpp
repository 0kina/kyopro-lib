/**
 * @file sparse_table.hpp
 * @brief Sparse Tableに関するコード。
 * @details 不変な数列の区間に対するクエリに答えられる。ただし、演算は結合則と冪等則を満たす必要がある。
 * @example sparse_table_test.cpp
 */
#ifndef OKINA_SPARSE_TABLE
#define OKINA_SPARSE_TABLE

#include <functional>
#include <vector>

/**
 * @brief Sparse Tableに関するクラス。
 * @tparam T 配列に格納されている値の型。
 */
template <typename T>
class SparseTable {
public:
  /**
   * @brief Sparse Tableクラスのコンストラクタ。配列のサイズをnとしてO(n log n)。
   * @param arr 数列への参照。
   * @param func 結合則と冪等則を満たす演算への参照。
   */
  SparseTable(const std::vector<T> &arr, const std::function<bool(T, T)> &func)
    : _func(func)
  {
    int n = arr.size();
    _log_table.resize(n + 1);
    _log_table[0] = 0;
    _log_table[1] = 0;
    for (int i = 2; i < n + 1; ++i) {
      _log_table[i] = _log_table[i >> 1] + 1;
    }

    _table.resize(n);
    for (int i = 0; i < n; ++i) {
      _table[i].resize(_log_table[n] + 1);
    }

    for (int i = 0; i < n; ++i) {
      _table[i][0] = arr[i];
    }
    for (int k = 1; (1 << k) <= n; ++k) {
      for (int i = 0; i + (1 << k) <= n; ++i) {
        T first = _table[i][k - 1];
        T second = _table[i + (1 << (k - 1))][k - 1];

        if (func(first, second)) {
          _table[i][k] = first;
        } else {
          _table[i][k] = second;
        }
      }
    }
  };

  /**
   * @brief 区間クエリ。O(1)。
   * @param l 左端。
   * @param r 右端。
   * @return 区間[l, r]に対するクエリの結果。
   */
  T query(int l, int r) const {
    int d = r - l + 1;
    int k = _log_table[d];

    if (_func(_table[l][k], _table[r - (1 << k) + 1][k])) {
      return _table[l][k];
    } else {
      return _table[r - (1 << k) + 1][k];
    }
  }

private:
  std::function<bool(T, T)> _func;
  std::vector<int> _log_table;
  std::vector<std::vector<int>> _table;
};

#endif // OKINA_SPARSE_TABLE