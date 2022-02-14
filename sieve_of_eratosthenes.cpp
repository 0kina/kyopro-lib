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