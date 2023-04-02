#ifndef OKINA_SCC
#define OKINA_SCC

#include <algorithm>
#include <cassert>
#include <map>
#include <set>
#include <vector>

class SCC {
public:
  explicit SCC(const int n) : _n(n), _comp(n, -1), _g(n), _rev_g(n) {};

  void add_edge(const int from, const int to) {
    _g[from].push_back(to);
    _rev_g[to].push_back(from);
  };

  void solve() {
    std::vector<bool> is_visited(_n, false);
    std::vector<int> order;

    for (int i = 0; i < _n; ++i) {
      if (!is_visited[i]) _dfs(i, is_visited, order);
    }

    std::reverse(std::begin(order), std::end(order));

    int comp_idx = 0;
    for (int i : order) {
      if (_comp[i] == -1) {
        _rdfs(i, comp_idx, _comp, _siz);
        ++comp_idx;
      }
    }

    _n_comp = comp_idx;
    _is_solved = true;
  }

  std::vector<int> comp() const {
    return _comp;
  }

  bool is_same(const int u, const int v) const {
    assert(_is_solved);
    return _comp[u] == _comp[v];
  }

  int comp_size(const int u) const {
    assert(_is_solved);
    return _siz.at(_comp[u]);
  }

  std::vector<std::vector<int>> scc() const {
    assert(_is_solved);
    std::vector<std::vector<int>> ret(_n_comp);
    for (int i = 0; i < _n_comp; ++i) {
      ret[i].reserve(_siz.at(i));
    }
    for (int i = 0; i < _n; ++i) {
      ret[_comp[i]].push_back(i);
    }

    return ret;
  }

private:
  int _n, _n_comp;
  std::vector<int> _comp;
  std::vector<std::vector<int>> _g, _rev_g;
  std::map<int, int> _siz;

  bool _is_solved = false;

  void _dfs(int u, std::vector<bool> &visited, std::vector<int> &order) {
    visited[u] = true;
    for (int v : _g[u]) {
      if (!visited[v]) _dfs(v, visited, order);
    }
    order.push_back(u);
  }

  void _rdfs(int u, int comp_idx, std::vector<int> &comp, std::map<int, int> &siz) {
    comp[u] = comp_idx;
    ++siz[comp_idx];
    for (int v : _rev_g[u]) {
      if (comp[v] == -1) _rdfs(v, comp_idx, comp, siz);
    }
  }
};

#endif