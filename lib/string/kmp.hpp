#pragma once
/**
 * @file kmp.hpp
 * @brief KMPアルゴリズムに関するコード。
 * @details
 * * 文字列SとパターンPに対し、Pの出現位置をO(|P| + |S|)で列挙する。
 * * AOJ
 *   * https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=8242587#1
 */

#include <string>
#include <sstream>
#include <vector>

#include <bits/stdc++.h>
using namespace std;

// 参考：アルゴリズムイントロダクション第3版
namespace kmp_inner
{
  std::vector<int> compute_prefix_function_(const std::string &P) {
    const int m = P.size();
    std::vector<int> pi(m);
    pi[0] = -1;
    int k = -1;
    for (int q = 1; q < m; ++q) {
      while (k >= 0 && P[k + 1] != P[q]) {
        k = pi[k];
      }
      if (P[k + 1] == P[q]) ++k;
      pi[q] = k;
    }
    return pi;
  }
} // namespace kmp_inner

std::vector<int> kmp(const std::string &S, const std::string &P) {
  const int n = S.size();
  const int m = P.size();
  auto pi = kmp_inner::compute_prefix_function_(P);
  int q = -1;
  std::vector<int> ret;
  for (int i = 0; i < n; ++i) {
    while (q >= 0 && P[q + 1] != S[i]) q = pi[q];
    if (P[q + 1] == S[i]) ++q;
    if (q == m - 1) {
      ret.push_back(i - m + 1);
      q = pi[q];
    }
  }
  return ret;
}