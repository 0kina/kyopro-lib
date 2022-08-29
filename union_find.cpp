#ifndef OKINA_DIJKSTRA
#define OKINA_DIJKSTRA

#include <numeric>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : _par(n), _siz(n, 1) {
      std::iota(_par.begin(), _par.end(), 0);
    }

  int root(int x) {
    if (_par[x] == x) {
      return x;
    }
    return _par[x] = root(_par[x]);
  }

  bool is_same(int x, int y) {
    return root(x) == root(y);
  }

  bool unite(int x, int y) {
    x = root(x);
    y = root(y);

    if (x == y) return false;

    if (_siz[x] < _siz[y]) std::swap(x, y);

    _par[y] = x;
    _siz[x] += _siz[y];
    return true;
  }

  int size(int x) {
    return _siz[root(x)];
  }

 private:
  std::vector<int> _par, _siz;
};

#endif