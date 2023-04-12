#include <iostream>

#include "prime_number.hpp"

using namespace std;

/*
* Output
* Is Prime: 0 0 1 1 0 1 0 1 0 0 0
* Prime Numbers: 2 3 5 7
*/

int main() {
  int n = 10;

  vector<bool> is_prime = make_is_prime(n);
  vector<int> prime_nums = enum_prime_nums(n);

  cout << "Is Prime: ";
  for (int i = 0; i <= n; ++i) {
    cout << is_prime[i] << (i < n ? " " : "\n");
  }
  cout << "Prime Numbers: ";
  int m = prime_nums.size();
  for (int i = 0; i < m; ++i) {
    cout << prime_nums[i] << (i < m - 1 ? " " : "\n");
  }
}