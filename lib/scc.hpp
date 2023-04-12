/**
 * @file scc.hpp
 * @brief 強連結成分分解に関するコード
 * @example scc_test.cpp
 */
#pragma once

#include <algorithm>
#include <cassert>
#include <map>
#include <set>
#include <vector>

/**
 * @brief 強連結成分分解を行うためのクラス
 *
 */
class SCC {
public:
  /**
   * @brief SCCクラスのコンストラクタ
   *
   * @param graph 有向グラフ
   */
  explicit SCC(const std::vector<std::vector<int>> &graph)
    : _n(graph.size()), _comp(graph.size(), -1), _g(graph)
  {
    _rev_g.resize(graph.size());
    for (int from = 0; from < _n; ++from) {
      for (int to : graph[from]) {
        _rev_g[to].push_back(from);
      }
    }
    _solve();
  };

  /**
   * @brief 各頂点の強連結成分番号をvectorで返す
   *
   * @return 各頂点の強連結成分番号を保持
   */
  std::vector<int> comp() const {
    return _comp;
  }

  /**
   * @brief 2頂点が同じ強連結成分に属するかどうかを返す
   *
   * @param u 1つ目の頂点
   * @param v 2つ目の頂点
   * @return 2頂点が同じ強連結成分に属するかどうか
   */
  bool is_same(const int u, const int v) const {
    return _comp[u] == _comp[v];
  }

  /**
   * @brief 頂点が属する強連結成分のサイズを返す
   * 
   * @param u 頂点
   * @return uが属する強連結成分のサイズ
   */
  int comp_size(const int u) const {
    return _siz.at(_comp[u]);
  }

  /**
   * @brief 強連結成分の配列をトポロジカル順に返す
   *
   * @return 各vectorが強連結成分となっている2次元vector
   */
  std::vector<std::vector<int>> scc() const {
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

  void _solve() {
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
  }

};