#pragma once

#include <vector>

template <typename CostType = int>
struct Edge {
 public:
  int from, to, id;
  CostType cost;

  Edge(int from, int to, CostType cost = 1, int id = -1) : from(from), to(to), cost(cost), id(id) {}
};

template <typename CostType = int>
struct Graph {
 public:
  std::vector<std::vector<Edge<CostType>>> g;
  
  explicit Graph(int n) :g(n), siz(0) {}

  void add_edge(int from, int to, CostType cost = 1) {
    g[from].emplace_back(from, to, cost, siz);
    g[to].emplace_back(to, from, cost, siz++);
  }

  void add_directed_edge(int from, int to, CostType cost = 1) {
    g[from].emplace_back(from, to, cost, siz++);
  }

  std::vector<Edge<CostType>> &operator[](int const &k) {
    return g[k];
  }

  std::size_t size() {
    return g.size();
  }

 private:
  int siz;
};