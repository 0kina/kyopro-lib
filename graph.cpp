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
bool operator<(const Edge<CostType> &a, const Edge<CostType> &b) {
  bool res = false;
  if (a.from < b.from) res = true;
  else if (a.from == b.from) {
    if (a.to < b.to) res = true;
    else if (a.to == b.to && a.cost < b.cost) res = true;
  }

  return res;
}

template <typename CostType = int>
bool operator==(const Edge<CostType> &a, const Edge<CostType> &b) {
  return !(a < b) && !(b < a);
}

template <typename CostType = int>
bool operator!=(const Edge<CostType> &a, const Edge<CostType> &b) {
  return !(a == b);
}

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

  const std::vector<Edge<CostType>> &operator[](const int &k) const {
    return g[k];
  }

  std::size_t size() const {
    return g.size();
  }

 private:
  int siz;
};