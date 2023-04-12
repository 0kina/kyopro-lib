#include <iostream>
#include <iomanip>

#include "sparse_table.hpp"

using namespace std;

/*
* Output
* Length  1:  1,  8,  7,  3,  2,  6,  4,  9,  0,  5
* Length  2:  1,  7,  3,  2,  2,  4,  4,  0,  0
* Length  3:  1,  3,  2,  2,  2,  4,  0,  0
* Length  4:  1,  2,  2,  2,  2,  0,  0
* Length  5:  1,  2,  2,  2,  0,  0
* Length  6:  1,  2,  2,  0,  0
* Length  7:  1,  2,  0,  0
* Length  8:  1,  0,  0
* Length  9:  0,  0
* Length 10:  0
*/

int main() {
  vector<int> A = {1, 8, 7, 3, 2, 6, 4, 9, 0, 5};

  function<bool(int, int)> func = [](int a, int b) {
    return a < b;
  };

  SparseTable<int> st(A, func);

  int n = A.size();

  for (int len = 1; len <= n; ++len) {
    cout << "Length " << setw(2) << len << ": ";
    for (int i = 0; i + len - 1 < n; ++i) {
      cout << setw(2) << st.query(i, i + len - 1);
      if (i < n - len) cout << ", ";
      else cout << endl;
    }
  }
}