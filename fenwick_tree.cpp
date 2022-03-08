#pragma once

#include <vector>

#include <iostream>

template<typename T = int>
class FenwickTree {
 public:
  FenwickTree(int n) : n(n), val(n, 0) {}

  void add(int pos, T x) {
    for (int i = pos; i < n; i|= i + 1) {
      val[i] += x;
    }
  }

  T sum(int pos) {
    if (pos < 0) return 0;
    else {
      T ret = 0;
      for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) ret += val[i];
      return ret;
    }
  }

  std::pair<int, T> lower_bound(T x) {
    int pos_ret = -1;
    T sum_ret = 0;
    int len_max = 1;
    while (len_max < n) len_max <<= 1;
    for (int len = len_max; len > 0; len >>= 1) {
      if (pos_ret + len < n && val[pos_ret + len] < x) {
        x -= val[pos_ret + len];
        sum_ret += val[pos_ret + len];
        pos_ret += len;
      }
    }

    return {pos_ret + 1, sum_ret};
  }

 private:
  int n;
  std::vector<T> val;
};