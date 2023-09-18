#pragma once
/**
 * @file max_flow.cpp
 * @brief 最大フローに関するコード
 * @details
 * * FordFulkerson
 *   * 容量の最大値をUとしてO(MU)
 * * Validation
 *   * FordFulkerson: https://onlinejudge.u-aizu.ac.jp/status/users/okina25/submissions/1/GRL_6_A/judge/8293689/C++17
 */

#include <stack>
#include <vector>

template <typename T>
class FordFulkerson {
public:
  /**
   * @brief FordFulkersonクラスのコンストラクタ．同時にUを容量の最大値としてO(MU)で最大フローを求める．
   */
  FordFulkerson(
    const std::vector<std::vector<std::pair<int, T>>> &g,
    const int source, const int target
  ) : n_(g.size()), source_(source), target_(target), inf_(0) {
    residual_g_.reserve(g.size());
    int edge_id = 0;
    for (int i = 0; i < g.size(); ++i) {
      for (int j = 0; j < g[i].size(); ++j) {
        auto [to, cap] = g[i][j];
        inf_ = max(inf_, cap);
        // Edge: from, to, cap, id_in_all_edge, id_in_adj
        Edge e = {i, to, cap, edge_id, int(residual_g_[i].size())};
        Edge rev_e = {to, i, 0, edge_id + 1, int(residual_g_[to].size())};
        residual_g_[i].push_back(e);
        residual_g_[to].push_back(rev_e);
        edges_.push_back(std::move(e));
        edges_.push_back(std::move(rev_e));
        edge_id += 2;
      }
    }
    inf_ += 10;
    solve_();
  }

  T get_max_flow_value() const { return max_flow_value_; }

  /**
   * @brief O(M)でフローを求める．
   */
  std::vector<std::vector<int, T>> get_flow() const {
    std::vector<std::vector<int, T>> flow(n_);
    for (int i = 0; i < n_; ++i) {
      assert(residual_g_[i].size() % 2 == 0);
      flow[i].reserve(residual_g_[i].size() / 2);
      for (Edge edge : residual_g_[i]) {
        if (edge.id_in_all_edge % 2 == 1) {
          flow[i].emplace_back(edge.from, edge.cap);
        }
      }
    }
    return flow;
  }

private:
  struct Edge {
    int from, to;
    T cap;
    int id_in_all_edge, id_in_adj;
  };

  bool find_augment_path_(
    std::vector<int> &path, std::vector<Edge> &path_edges, std::vector<bool> &seen
  ) const {
    const std::vector<Edge> &adj = residual_g_[path.back()];
    for (Edge edge : adj) {
      if (seen[edge.to] || edge.cap == 0) continue;
      seen[edge.to] = true;
      path.push_back(edge.to);
      path_edges.push_back(edge);
      if (edge.to == target_) {
        return true;
      } else {
        if (find_augment_path_(path, path_edges, seen)) return true;
        else path.pop_back(), path_edges.pop_back();
      }
    }
    return false;
  }

  void solve_() {
    T max_flow_value = 0;
    while (true) {
      std::vector<int> path = {source_};
      std::vector<Edge> path_edges;
      std::vector<bool> seen(n_, false);
      seen[source_] = true;
      if (find_augment_path_(path, path_edges, seen)) {
        T augment_amount = inf_;
        for (Edge e : path_edges) augment_amount = min(augment_amount, e.cap);
        max_flow_value += augment_amount;
        for (auto [from, to, cap, id_in_all_edge, id_in_adj] : path_edges) {
          if (id_in_all_edge % 2 == 0) {
            residual_g_[from][id_in_adj].cap -= augment_amount;
            residual_g_[to][edges_[id_in_all_edge + 1].id_in_adj].cap += augment_amount;
          } else {
            residual_g_[from][id_in_adj].cap -= augment_amount;
            residual_g_[to][edges_[id_in_all_edge - 1].id_in_adj].cap += augment_amount;
          }
        }
      } else break;
    }
    max_flow_value_ = max_flow_value;
  }

  std::vector<std::vector<Edge>> residual_g_;
  std::vector<Edge> edges_;
  const int n_, source_, target_;
  T inf_, max_flow_value_;
}; // class FordFulkerson