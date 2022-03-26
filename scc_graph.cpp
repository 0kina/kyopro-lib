#pragma once

#include <algorithm>
#include <map>
#include <set>
#include <vector>

class SCC_Graph {
 public:
  explicit SCC_Graph(int n) : n(n), comp(n, -1), g(n), rev_g(n) {};

  void add_edge(int from, int to) {
    g[from].push_back(to);
    rev_g[to].push_back(from);
  };

  std::vector<int> scc() {
    std::vector<bool> visited(n, false);
    std::vector<int> order;

    for (int i = 0; i < n; ++i) {
      if (!visited[i]) dfs(i, visited, order);
    }

    std::reverse(std::begin(order), std::end(order));

    int comp_idx = 0;
    for (int i : order) {
      if (comp[i] == -1) {
        rdfs(i, comp_idx, comp, siz);
        ++comp_idx;
      }
    }

    return comp;
  }

  bool is_same(int u, int v) {
    return comp[u] == comp[v];
  }

  int size(int u) {
    return siz[comp[u]];
  }

  std::vector<std::vector<int>> rebuild() {
    int N = *std::max_element(std::begin(comp), std::end(comp)) + 1;
    std::vector<std::vector<int>> ret(N);
    std::set<std::pair<int, int>> connected;
    for (int i = 0; i < n; ++i) {
      for (int v : g[i]) {
        if (comp[i] != comp[v] && !connected.count(std::make_pair(i, v))) {
          connected.insert(std::make_pair(i, v));
          ret[comp[i]].push_back(comp[v]);
        }
      }
    }

    return ret;
  }

 private:
  int n;
  std::vector<int> comp;
  std::vector<std::vector<int>> g, rev_g;
  std::map<int, int> siz;

  void dfs(int u, std::vector<bool> &visited, std::vector<int> &order) {
    visited[u] = true;
    for (int v : g[u]) {
      if (!visited[v]) dfs(v, visited, order);
    }
    order.push_back(u);
  }

  void rdfs(int u, int comp_idx, std::vector<int> &comp, std::map<int, int> siz) {
    comp[u] = comp_idx;
    ++siz[comp_idx];
    for (int v : rev_g[u]) {
      if (comp[v] == -1) rdfs(v, comp_idx, comp, siz);
    }
  }
};