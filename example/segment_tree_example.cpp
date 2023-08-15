#include <iostream>
#include <sstream>

#include "segment_tree.hpp"

using namespace std;

/*
* Output
* [1, 5, 3, 4]での区間[l, r)の加算クエリ
* sum(0, 3) = 0
* [1, 8, 3, 4]への変更
* 区間[0, 3)の加算クエリ
* sum(0, 3) = 8
*/

int main() {
  vector<int> v{1, 5, 3, 4};

  SegmentTree<int> segt(4, 0, [](int a, int b) { return a + b; });

  cout << "[1, 5, 3, 4]での区間[l, r)の加算クエリ" << endl;
  cout << "sum(0, 3) = " << to_string(segt.query(0, 3)) << endl;
  cout << "[1, 8, 3, 4]への変更" << endl;
  segt.update(1, 8);
  cout << "区間[0, 3)の加算クエリ" << endl;
  cout << "sum(0, 3) = " << to_string(segt.query(0, 3)) << endl;
}