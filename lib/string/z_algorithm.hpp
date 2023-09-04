#pragma once
/**
 * @file z_algorithm.hpp
 * @brief Manacharアルゴリズムに関するコード。
 * @details
 * * 文字列SとS[i:]の最長共通接頭辞の長さをすべてのiに対して合計O(|S|)で求める。
 * * Library Checker
 *   * https://judge.yosupo.jp/submission/159294
 */

#include <string>
#include <sstream>
#include <vector>

// 参考：https://snuke.hatenablog.com/entry/2014/12/03/214243
/**
 * @brief 文字列SとS[i:]の最長共通接頭辞の長さをすべてのiに対して合計O(|S|)で求める。
 * @param S 対象の文字列。
 * @return 文字列SとS[i:]の最長共通接頭辞の長さを格納したvector。
 */
std::vector<int> z_algorithm(const std::string &S) {
  std::vector<int> ret(S.size());
  ret[0] = S.size();
  int i = 1, j = 0;
  while (i < S.size()) {
    while (i + j < S.size() && S[j] == S[i + j]) ++j;
    ret[i] = j;
    if (j == 0) {
      ++i;
      continue;
    }
    int k = 1;
    while (i + k < S.size() && k + ret[k] < j) {
      ret[i + k] = ret[k];
      ++k;
    }
    i += k;
    j -= k;
  }
  return ret;
}