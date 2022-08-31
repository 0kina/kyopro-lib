#ifndef OKINA_KRUSKAL
#define OKINA_KRUSKAL

#include <functional>
#include <utility>
#include <queue>
#include <tuple>

#include "union_find.hpp"

template<typename CostType>
class Kruskal {
 using Edge = std::tuple<int, int, CostType>;
 public:
  Kruskal(int n) : _n(n), _pq([](Edge a, Edge b) { return std::get<2>(a) > std::get<2>(b); }), _uf(n) {};

  void add_edge(const int u, const int v, const CostType c) {
    _pq.emplace(u, v, c);
  }

  void solve() {
    while (!_pq.empty()) {
      auto [u, v, c] = _pq.top();
      _pq.pop();
      if (!_uf.is_same(u, v)) {
        _uf.unite(u, v);
        _msf.emplace_back(u, v, c);
      }

      if (_msf.size() == _n - 1) break;
    }
    _is_solved = true;
  }

  bool is_mst() const {
    assert(_is_solved);
    return _msf.size() == _n - 1;
  }

  CostType get_cost_sum() const {
    assert(_is_solved);
    CostType ret = 0;
    for (auto [u, v, c] : _msf) {
      ret += c;
    }
    return ret;
  }

  std::vector<Edge> get_msf() const {
    assert(_is_solved);
    return _msf;
  };

 private:
  int _n;
  bool _is_solved = false;
  std::priority_queue<Edge, std::vector<Edge>, std::function<bool(Edge, Edge)>> _pq;
  UnionFind _uf;
  std::vector<Edge> _msf;
};

#endif