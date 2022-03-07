#pragma once

#include <functional>
#include <queue>
#include <vector>

#include "graph.cpp"
#include "union_find.cpp"

template<typename T>
class Kruskal {
 public:
  Kruskal(const Graph<T> &g) : g(g) { solve(); };

  bool is_mst() {
    return mst.size() == g.size() - 1;
  }

  T get_cost_sum() {
    T ret = 0;
    for (Edge<T> e : mst) ret += e.cost;
    return ret;
  }

  std::vector<Edge<T>> get_mst() { return mst; };

 private:
  Graph<T> g;
  std::vector<Edge<T>> mst;

  void solve() {
    std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::function<bool(Edge<T>, Edge<T>)>>
      pq([](Edge<T> a, Edge<T> b) {
        return a.cost > b.cost;
      });
    
    for (int i = 0; i < static_cast<int>(g.size()); ++i) {
      for (Edge<T> e : g[i]) {
        if (e.from < e.to) pq.push(e);
      }
    }
  
    UnionFind uf(g.size());
    while (!pq.empty()) {
      Edge<T> e = pq.top();
      pq.pop();
      if (!uf.is_same(e.from, e.to)) {
        uf.unite(e.from, e.to);
        mst.emplace_back(e);
      }

      if (mst.size() == g.size() - 1) break;
    }
  }
};