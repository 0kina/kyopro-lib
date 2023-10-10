#pragma once

#include <algorithm>
#include <queue>
#include <limits>
#include <vector>

template <typename CostType>
class Dijkstra {
  using State = std::pair<CostType, int>;
public:
  Dijkstra(const std::vector<std::vector<pair<int, CostType>>> &g, int src)
    : _src(src), _g(g), _dist(g.size(), _INF), _prev(g.size(), -1)
  {
    _dist[src] = 0;
    _pq.emplace(0, src);
    _solve();
  }

  Dijkstra(const std::vector<std::vector<int>> &g, int src)
    : _src(src), _g(g.size()), _dist(g.size(), _INF), _prev(g.size(), -1)
  {
    for (int i = 0; i < g.size(); ++i) {
      for (int j : g[i]) {
        _g[i].push_back(std::make_pair(j, 1));
      }
    }
    _dist[src] = 0;
    _pq.emplace(0, src);
    _solve();
  }

  bool is_reachable(int t) const {
    return _dist[t] != _INF;
  }

  CostType distance_to(int t) const {
    return _dist[t];
  }

  std::vector<int> path_to(int t) const {
    if (!is_reachable(t)) return std::vector<int>();
    std::vector<int> res;

    res.push_back(t);
    int pos = t;
    while (pos != _src) {
      res.push_back(_prev[pos]);
      pos = _prev[pos];
    }

    std::reverse(std::begin(res), std::end(res));

    return res;
  }

  int prev(int v) const { return _prev[v]; }

private:
  const CostType _INF = std::numeric_limits<CostType>::max();
  int _src;
  std::vector<std::vector<std::pair<int, CostType>>> _g;
  std::vector<CostType> _dist;
  std::vector<int> _prev;
  std::priority_queue<State, std::vector<State>, std::greater<State>> _pq;

  void _solve() {
    while (!_pq.empty()) {
      auto [du, u] = _pq.top();

      _pq.pop();
      if (_dist[u] != du) continue;

      for (auto [v, c] : _g[u]) {
        CostType new_dv = du + c;
        if (_dist[v] > new_dv) {
          _dist[v] = new_dv;
          _prev[v] = u;
          _pq.emplace(new_dv, v);
        }
      }
    }
  }
};