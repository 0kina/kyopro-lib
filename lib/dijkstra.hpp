#ifndef OKINA_DIJKSTRA
#define OKINA_DIJKSTRA

#include <algorithm>
#include <queue>
#include <limits>
#include <vector>

template <typename CostType>
class Dijkstra {
  using State = std::pair<CostType, int>;
 public:
  Dijkstra(const int n, const int src): _src(src), _g(n), _dist(n, _INF), _prev(n, -1) {
    _dist[src] = 0;

    _pq.emplace(0, src);
  }

  void add_edge(const int u, const int v, const CostType c) {
    _g[u].emplace_back(v, c);
  }

  void solve() {
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
    _is_solved = true;
  }

  bool is_reachable(int t) const {
    assert(_is_solved);
    return _dist[t] != _INF;
  }

  CostType distance_to(int t) const {
    assert(is_reachable(t));
    return _dist[t];
  }

  std::vector<int> path_to(int t) const {
    assert(is_reachable(t));
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

 private:
  const CostType _INF = std::numeric_limits<CostType>::max();
  int _src;
  std::vector<std::vector<std::pair<int, CostType>>> _g;
  std::vector<CostType> _dist;
  std::vector<int> _prev;
  std::priority_queue<State, std::vector<State>, std::greater<State>> _pq;
  bool _is_solved = false;
};

#endif