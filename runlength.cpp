#pragma once

#include <string>
#include <vector>

std::vector<std::pair<char, int>> runlength(std::string s) {
  std::vector<std::pair<char, int>> ret;
  char c = s[0];
  int cnt = 1;

  for (int i = 1; i < s.size(); ++i) {
    if (s[i] == c) ++cnt;
    else {
      ret.emplace_back(c, cnt);
      c = s[i];
      cnt = 1;
    }
  }

  ret.emplace_back(c, cnt);

  return ret;
}