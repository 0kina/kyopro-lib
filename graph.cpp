#pragma once

#include <vector>

template <typename CostType = int>
struct Edge {
 public:
  int from, to, id;
  CostType cost;

  Edge(int from, int to, CostType cost = 1, int id = -1) : from(from), to(to), id(id), cost(cost) {}
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
  
  explicit Graph(int n) :g(n), edge_num(0) {}

  void add_edge(int from, int to, CostType cost = 1) {
    g[from].emplace_back(from, to, cost, edge_num);
    g[to].emplace_back(to, from, cost, edge_num++);
  }

  void add_directed_edge(int from, int to, CostType cost = 1) {
    g[from].emplace_back(from, to, cost, edge_num++);
  }

  const std::vector<Edge<CostType>> &operator[](const int &k) const {
    return g[k];
  }

  std::size_t size() const {
    return g.size();
  }

  std::string to_string() const {
    std::string ret;
    for (std::size_t i = 0; i < size(); ++i) {
      ret += std::to_string(i) + ": ";
      for (std::size_t j = 0; j < g[i].size(); ++j) {
      ret += std::to_string(g[i][j].to);
        if (j < g[i].size() - 1) ret += ", ";
      }
    }

    return ret;
  }

 private:
  int edge_num;
};