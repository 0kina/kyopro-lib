#include <iostream>
#include <sstream>

#include "fft.hpp"

using namespace std;

/*
* Output
* Original: 4X^3 + 3X^2 + 2X^1 + 1X^0
* Restored: 4X^3 + 3X^2 + 2X^1 + 1X^0
* F: 3X^3 + 7X^2 + 8X^1 + 1X^0
* G: 1X^2 + 3X^1 + 2X^0
* Correct FG   : 3X^5 + 16X^4 + 35X^3 + 39X^2 + 19X^1 + 2X^0
* Calculated FG: 3X^5 + 16X^4 + 35X^3 + 39X^2 + 19X^1 + 2X^0
*/

template <typename T>
std::string func_to_string(vector<T> f, int n) {
  ostringstream ost;
  for (int i = n - 1; i >= 0; --i) {
    ost << f[i] << "X^" << i;
    if (i > 0) ost << " + ";
  }
  return ost.str();
}

int main() {

  // func simple_F = {1, 2, 3, 4};
  // func FT_simple_F = FFT::dft(simple_F, false);
  // func restored_simple_F = FFT::dft(FT_simple_F, true);
  // for (auto &c : restored_simple_F) {
  //   c /= restored_simple_F.size();
  // }
  // cout << "Original: " << func_to_string(simple_F, simple_F.size()) << endl;
  // cout << "Restored: " << func_to_string(restored_simple_F, restored_simple_F.size()) << endl;

  vector<int> F = {1, 8, 7, 3};
  vector<int> G = {2, 3, 1, 0};
  vector<int> FG = {2, 19, 39, 35, 16, 3};

  vector<long long> calculated_FG = FFT::multiply(F, G);

  cout << "F: " << func_to_string(F, 4) << endl;
  cout << "G: " << func_to_string(G, 3) << endl;
  cout << "Correct FG   : " << func_to_string(FG, 6) << endl;
  cout << "Calculated FG: " << func_to_string(calculated_FG, 6) << endl;
}