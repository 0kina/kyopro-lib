#ifndef OKINA_RUNLENGTH
#define OKINA_RUNLENGTH

#include <string>
#include <typeinfo>
#include <vector>

template <typename T, class ForwardIterator>
std::vector<std::pair<T, int>> runlength(ForwardIterator first, ForwardIterator last) {
  assert(typeid(T) == typeid(*first));
  std::vector<std::pair<T, int>> ret;
  T val = *first;
  int cnt = 1;

  auto iter = first;
  ++iter;
  for (; iter != last; ++iter) {
    if (*iter == val) ++cnt;
    else {
      ret.emplace_back(val, cnt);
      val = *iter;
      cnt = 1;
    }
  }
  ret.emplace_back(val, cnt);

  return ret;
}

#endif