#pragma once

#include <numeric>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : par(n), siz(n, 1) {
      std::iota(par.begin(), par.end(), 0);
    }

  int root(int x) {
    if (par[x] == x) {
      return x;
    }
    return par[x] = root(par[x]);
  }

  int is_same(int x, int y) {
    return root(x) == root(y);
  }

  bool unite(int x, int y) {
    x = root(x);
    y = root(y);

    if (x == y) return false;

    if (siz[x] < siz[y]) std::swap(x, y);

    par[y] = x;
    siz[x] += siz[y];
    return true;
  }

  int size(int x) {
    return siz[root(x)];
  }

 private:
  std::vector<int> par, siz;
};