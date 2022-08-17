#ifndef OKINA_DIJKSTRA
#define OKINA_DIJKSTRA

#include <algorithm>
#include <queue>
#include <limits>
#include <vector>

#include <iostream>

template <typename CostType>
class Dijkstra {
 public:
  Dijkstra(int n, const std::vector<std::vector<std::pair<int, CostType>>> &G, int src) : _src(src) {
    _dist.assign(n, INF);
    _dist[src] = 0;
    _prev.assign(n, -1);

    using State = std::pair<CostType, int>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.emplace(0, src);
    while (pq.size()) {
      auto [du, u] = pq.top();

      pq.pop();
      if (_dist[u] != du) continue;

      for (auto [v, c] : G[u]) {
        CostType new_dv = du + c;
        if (_dist[v] > new_dv) {
          _dist[v] = new_dv;
          _prev[v] = u;
          pq.emplace(new_dv, v);
        }
      }
    }
  };

  CostType distance_to(int t) const {
    if (_dist[t] == INF) return -1;
    else return _dist[t];
  }

  std::pair<bool, std::vector<int>> path_to(int t) const {
    std::pair<bool, std::vector<int>> res{false, std::vector<int>()};

    if (_dist[t] == INF) return res;

    res.first = true;

    res.second.push_back(t);
    int pos = t;
    while (pos != _src) {
      res.second.push_back(_prev[pos]);
      pos = _prev[pos];
    }

    std::reverse(std::begin(res.second), std::end(res.second));

    return res;
  }

 private:
  const CostType INF = std::numeric_limits<CostType>::max();
  int _src;
  std::vector<CostType> _dist;
  std::vector<int> _prev;
};

#endif