#pragma once

#include <algorithm>
#include <queue>
#include <limits>

#include "graph.cpp"

template <typename DistType = int, typename CostType = int>
class Dijkstra {
 public:
  int s;
  const CostType INF = std::numeric_limits<DistType>::max();

  Dijkstra(const Graph<CostType> &G, int s) :
    s(s),
    G(G),
    dist(G.size(), INF),
    prev(G.size(), -1) {
      dist[s] = 0;
      solve();
  };

  DistType distance_to(int t) const {
    if (dist[t] == INF) return -1;
    else return dist[t];
  }

  std::pair<bool, std::vector<Edge<CostType>>> path_to(int t) const {
    std::pair<bool, std::vector<Edge<CostType>>> res{false, std::vector<Edge<CostType>>()};

    if (dist[t] == INF) return res;

    res.first = true;

    int pos = t;
    while (pos != s) {
      res.second.emplace_back(prev[pos], pos, dist[pos] - dist[prev[pos]]);
      pos = prev[pos];
    }

    std::reverse(std::begin(res.second), std::end(res.second));

    return res;
  }

 private:
  const Graph<CostType> &G;
  std::vector<DistType> dist;
  std::vector<int> prev;

  void solve() {
    using PQItem = std::pair<int, DistType>;

    auto comp = [](PQItem a, PQItem b) {
      return a.second > b.second;
    };

    std::priority_queue<PQItem, std::vector<PQItem>, decltype(comp)> pq{comp};
    pq.push({s, 0});

    while (!pq.empty()) {
      PQItem tp = pq.top();
      pq.pop();
      if (dist[tp.first] < tp.second) continue;

      for (Edge<CostType> v : G[tp.first]) {
        if (dist[v.to] > dist[v.from] + v.cost) {
          dist[v.to] = dist[v.from] + v.cost;
          prev[v.to] = v.from;
          pq.push({v.to, dist[v.to]});
        }
      }
    }
  }

};