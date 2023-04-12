/**
 * @file prime_number.hpp
 * @brief 素数に関するコード
 * @example prime_number_test.cpp
 */
#pragma once

#include <vector>

/**
 * @brief エラトステネスの篩で素数判定表を構築する。O(n log log n)
 *
 * @param n この値以下の判定表を構築する
 * @return 0以上n以下の整数の素数判定表
 */
std::vector<bool> make_is_prime(int n) {
  std::vector<bool> is_prime(n + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;
  for (int i = 2; i < n; ++i) {
    if (!is_prime[i]) continue;

    for (int j = 2 * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }

  return is_prime;
}

/**
 * @brief エラトステネスの篩で素数を列挙する。O(n log log n)
 *
 * @param n この値以下の素数を列挙する
 * @return 0以上n以下の素数で構築された配列
 */
std::vector<int> enum_prime_nums(int n) {
  std::vector<bool> is_prime(n + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;

  std::vector<int> prime_nums;
  for (int i = 2; i < n; ++i) {
    if (!is_prime[i]) continue;

    prime_nums.push_back(i);

    for (int j = 2 * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }

  return prime_nums;
}