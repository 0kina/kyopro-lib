#pragma once

#include <vector>

std::vector<bool> sieve_of_eratosthenes(int n) {
  std::vector<bool> res(n + 1, true);
  res[0] = false;
  res[1] = false;
  for (int i = 2; i < n; ++i) {
    if (!res[i]) continue;

    for (int j = 2 * i; j <= n; j += i) {
      res[j] = false;
    }
  }

  return res;
}

std::vector<int> enum_prime_nums(int n) {
  std::vector<bool> is_prime(n + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;

  std::vector<int> res;
  for (int i = 2; i < n; ++i) {
    if (!is_prime[i]) continue;

    res.push_back(i);

    for (int j = 2 * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }

  return res;
}