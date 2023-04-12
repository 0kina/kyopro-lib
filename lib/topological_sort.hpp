/**
 * @file topological_sort.hpp
 * @brief トポロジカルソートに関するコード
 *
 * @example topological_sort_test.cpp
 */
#pragma once

#include <cassert>
#include <queue>
#include <vector>

/**
 * @brief トポロジカルソートのためのクラス
 *
 */
class TopologicalSort {
public:
  /**
   * @brief Topological Sortクラスのコンストラクタ
   *
   * @param graph 有向グラフ
   */
  TopologicalSort(const std::vector<std::vector<int>>& graph) :
    _n(graph.size()), _g(graph), _in_degree(graph.size()) {
    _sorted.reserve(_n);
    for (auto vs: graph) {
      for (int v: vs) {
        ++_in_degree[v];
      }
    }
    _solve();
  }

  /**
   * @brief トポロジカルソート可能性の判定
   *
   * @return トポロジカルソート可能かどうか
   */
  bool is_sortable() const {
    return _sorted.size() == _g.size();
  }

  /**
   * @brief トポロジカルソートした頂点列を返す
   *
   * @return ソート可能であればソートした頂点列を、そうでなければ空列を返す
   */
  std::vector<int> sorted() const {
    if (!is_sortable()) {
      return std::vector<int>();
    }
    return _sorted;
  }

private:
  int _n;
  std::vector<std::vector<int>> _g;
  std::vector<int> _in_degree;
  std::vector<int> _sorted;

  void _solve() {
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
  }
};