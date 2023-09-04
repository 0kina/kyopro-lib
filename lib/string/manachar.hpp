#pragma once
/**
 * @file manachar.hpp
 * @brief Manacharアルゴリズムに関するコード。
 * @details
 * * 文字列のi文字目を中心とした回文の最大半径(i文字目を含む)を合計O(N)で求める。
 * * 同じ時間でi文字目とi+1文字目の間を中心とする回文の最大半径を求めることもできる。
 * * Library Checker
 *   * https://judge.yosupo.jp/submission/159284
 */

#include <string>
#include <sstream>
#include <vector>

namespace manachar_inner {
  // 参考：https://snuke.hatenablog.com/entry/2014/12/02/235837
  std::vector<int> manachar_(const std::string &s) {
    std::vector<int> ret(s.size());
    int i = 0, j = 0;
    while (i < s.size()) {
      while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) ++j;
      ret[i] = j;
      int k = 1;
      while (i - k >= 0 && k + ret[i - k] < j) {
        ret[i + k] = ret[i - k];
        ++k;
      }
      i += k; j -= k;
    }
    return ret;
  }
} // namespace manachar_inner

/**
 * @brief 文字列のi文字目を中心とした回文の最大半径(i文字目を含む)を合計O(N)で求める。
 * @param s 対象の文字列。
 * @param odd 回文の中心が、`true`のときi文字目となり、`false`のときi文字目とi+1文字目の間となる。
 * @return 回文の最大半径を格納したvector。長さは、`odd`が`true`のとき`s.size()`となり、`false`のとき`s.size() - 1`となる。
 */
std::vector<int> manachar(
  const std::string &s,
  const bool odd=true
) {
  if (odd) return manachar_inner::manachar_(s);
  std::ostringstream dummy_oss;
  for (int i = 0; i < s.size(); ++i) {
    dummy_oss << s[i];
    if (i < s.size() - 1) dummy_oss << '$';
  }
  std::vector<int> dummy_result = manachar_inner::manachar_(dummy_oss.str());
  std::vector<int> ret;
  for (int i = 1; i < dummy_result.size(); i += 2) {
    ret.push_back(dummy_result[i] / 2);
  }
  return ret;
}