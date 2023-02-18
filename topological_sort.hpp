#ifndef OKINA_TOPOLOGICAL_SORT
#define OKINA_TOPOLOGICAL_SORT

#include <cassert>
#include <queue>
#include <vector>

class TopologicalSort {
public:
  TopologicalSort(int n) : _n(n), _g(n), _in_degree(n) {
    _sorted.reserve(n);
  }

  TopologicalSort(const std::vector<std::vector<int>>& graph, const std::vector<int>& in_degree) :
    _n(graph.size()), _g(graph), _in_degree(in_degree) {
    _sorted.reserve(_n);
  }

  TopologicalSort(const std::vector<std::vector<int>>& graph) :
    _n(graph.size()), _g(graph), _in_degree(graph.size()) {
    _sorted.reserve(_n);
    for (auto vs: graph) {
      for (int v: vs) {
        ++_in_degree[v];
      }
    }
  }

  void add_edge(int from, int to) {
    _g[from].push_back(to);
    ++_in_degree[to];
  }

  void solve() {
    std::queue<int> q;
    for (int i = 0; i < _n; ++i) {
      if (_in_degree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
      int f = q.front();
      q.pop();

      _sorted.push_back(f);
      for (int to : _g[f]) {
        if (--_in_degree[to] == 0) q.push(to);
      }
    }

    _is_solved = true;
  }

  std::vector<int> sorted() const {
    assert(_is_solved);
    return _sorted;
  }

private:
  int _n;
  std::vector<std::vector<int>> _g;
  std::vector<int> _in_degree;
  bool _is_solved = false;
  std::vector<int> _sorted;
};

#endif