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

#include <list>
#include <memory>
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
  std::vector<std::vector<std::pair<int, T>>> get_flow() const {
    std::vector<std::vector<int, T>> flow(n_);
    for (int i = 0; i < n_; ++i) {
      flow[i].reserve(residual_g_[i].size() / 2);
      for (Edge edge : residual_g_[i]) {
        if (edge.id_in_all_edge % 2 == 1) {
          flow[edge.to].emplace_back(edge.from, edge.cap);
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

template <typename T>
class PushRelabel {
public:
  PushRelabel(
    const std::vector<std::vector<std::pair<int, T>>> &g,
    const int source, const int target
  ) : n_(g.size()), source_(source), target_(target), max_active_v_distance_(0),
      distance_label_(n_, 0), distance_to_active_v_(2 * n_),
      admissible_edge_ids_(n_), excess_amount_(n_, 0), max_flow_value_(0), flow_(n_)
  {
    residual_g_.reserve(g.size());
    int edge_id = 0;
    for (int i = 0; i < g.size(); ++i) {
      for (int j = 0; j < g[i].size(); ++j) {
        auto [to, cap] = g[i][j];
        // Edge: from, to, cap, id_in_all_edge, id_in_adj
        Edge e = {i, to, cap, edge_id, int(residual_g_[i].size())};
        Edge rev_e = {to, i, 0, edge_id + 1, int(residual_g_[to].size())};
        residual_g_[i].push_back(std::make_shared<Edge>(e));
        residual_g_[to].push_back(std::make_shared<Edge>(rev_e));
        edges_.push_back(residual_g_[i].back());
        edges_.push_back(residual_g_[to].back());
        edge_id += 2;
      }
    }
    solve_();
    for (int i = 0; i < n_; ++i) {
      cerr << "Excess at " << i << " is " << excess_amount_[i] << endl;
      if (i == source_ || i == target_) continue;
      assert(excess_amount_[i] == 0);
    }
    cerr << "edges: " << endl;
    for (auto e : edges_) {
      cerr << (e->id_in_all_edge % 2 == 0 ? "O" : "X") << " ";
      cerr << "(" << e->from << ", " << e->to << "," << e->cap << ")" << endl;
    }
    for (int i = 0; i < n_; ++i) {
      cerr << "i: " << i << ", residual_g_[i].size(): " << residual_g_[i].size() << endl;
      flow_[i].reserve(residual_g_[i].size() / 2);
      for (const std::shared_ptr<Edge> &edge : residual_g_[i]) {
        if (edge->id_in_all_edge % 2 == 1) {
          flow_[edge->to].emplace_back(edge->from, edge->cap);
        }
      }
    }
    for (const std::shared_ptr<Edge> &e : residual_g_[source_]) {
      if (e->id_in_all_edge % 2 == 0) max_flow_value_ += edges_[get_rev_edge_id_(e->id_in_all_edge)]->cap;
      else max_flow_value_ -= edges_[e->id_in_all_edge]->cap;
    }
  }

  T get_max_flow_value() const { return max_flow_value_; }

  std::vector<std::vector<std::pair<int, T>>> get_flow() const { return flow_; }

private:
  struct Edge {
    int from, to;
    T cap;
    int id_in_all_edge, id_in_adj;
  };

  int get_rev_edge_id_(int edge_id) const {
    if (edge_id % 2 == 0) return edge_id + 1;
    else return edge_id - 1;
  }

  void augment_flow_(int edge_id, T amount) {
    cerr << "augment amount: " << amount << endl;
    assert(amount > 0);
    assert(amount <= edges_[edge_id]->cap);
    cerr << "add flow with edge (" << edges_[edge_id]->from << ", " << edges_[edge_id]->to << ")";
    cerr << "by " << amount << endl;
    edges_[edge_id]->cap -= amount;
    edges_[get_rev_edge_id_(edge_id)]->cap += amount;
    excess_amount_[edges_[edge_id]->from] -= amount;
    if (edges_[edge_id]->from != source_) assert(excess_amount_[edges_[edge_id]->from] >= 0);
    excess_amount_[edges_[edge_id]->to] += amount;
    assert(edges_[edge_id]->cap >= 0);
    assert(edges_[get_rev_edge_id_(edge_id)]->cap >= 0);
  }

  void push_(int edge_id) {
    cerr << "push" << endl;
    std::shared_ptr<Edge> e = edges_[edge_id];
    cerr << "push edge (" << e->from << ", " << e->to << ")" << endl;
    cerr << "dist: " << "{" << distance_label_[e->from] << ", " << distance_label_[e->to] << "}";
    assert(distance_label_[e->from] == distance_label_[e->to] + 1);
    T augment_amount = std::min(excess_amount_[e->from], e->cap);
    cerr << "augment amount: " << augment_amount << endl;
    augment_flow_(edge_id, augment_amount);
    if (e->cap == 0) admissible_edge_ids_[e->from].pop_back();
    // 使用可能辺の逆辺は使用不可能なので，連結リストへの次のような追加は不要
    // if (rev_e->cap > 0) admissible_edge_ids_[rev_e->from].push_back();
    if (excess_amount_[e->from] == 0) {
      distance_to_active_v_[max_active_v_distance_].pop_back();
    }
    if (excess_amount_[e->to] == augment_amount && e->to != target_) {
      cerr << "excess of to: " << excess_amount_[e->to] << endl;
      distance_to_active_v_[distance_label_[e->to]].push_back(e->to);
    }
  }

  void relabel_(int v) {
    cerr << "relabel" << endl;
    // 距離ラベルとして有り得る上限値より大きければよい．
    // distance_label_の有効な値は2n_-1のため2n_を設定．
    distance_to_active_v_[max_active_v_distance_].pop_back();
    distance_label_[v] = 2 * n_;
    for (const std::shared_ptr<Edge> &e : residual_g_[v]) {
      if (e->cap == 0) continue;
      cerr << "dist of " << e->to << " is " << distance_label_[e->to] << endl;
      distance_label_[v] = min(distance_label_[v], distance_label_[e->to] + 1);
    }
    cerr << "new dist of " << v << " is: " << distance_label_[v] << endl;
    for (const shared_ptr<Edge> &e : residual_g_[v]) {
      // 使用可能辺の追加
      if (e->cap > 0 && distance_label_[v] == distance_label_[e->to] + 1) {
        admissible_edge_ids_[v].push_back(e->id_in_all_edge);
        cerr << "new admissible edge is: (" << e->from << ", " << e->to << ")" << endl;
      }
      const std::shared_ptr<Edge> &rev_e = edges_[get_rev_edge_id_(e->id_in_all_edge)];
      if (rev_e->cap > 0 && distance_label_[rev_e->from] == distance_label_[rev_e->to] + 1) {
        admissible_edge_ids_[rev_e->from].push_back(rev_e->id_in_all_edge);
        cerr << "new admissible edge is: (" << rev_e->from << ", " << rev_e->to << ")" << endl;
      }
      // 使用可能辺の削除
      // relabelを呼ぶ時点で v == w + 1 となる 使用可能辺は存在しない
      //   relabel を呼ぶための条件より．
      // relabelを呼ぶ時点で v + 1 == w となる w s.t. (w, v) \in E が存在する？
      // w から出る使用可能辺が増えるのは relabel(w) が呼ばれたときのみ
      // この relabel(w) のあと， w は v より大きな活性点となるので， (w, v) が使用可能辺であれば，
      // push(w, v) が必ず relabel(v) より前に行われる．
      // この push で (w, v) が消えれば問題なし．
      // (w, v) が残っているとき， w は非活性点であり， (w, v) が w の最後の使用可能辺である．
      //   v の活性化より前に w が次に活性化したとして， (w, v) の後に使用可能辺を追加した状態で非活性化することはない．
      //   これは使用可能辺が残っている頂点については push が行われるため．
      //   したがって， v が活性化した段階で (w, v) が使用可能であれば，必ず w の最後の使用可能辺である．
      if (admissible_edge_ids_[rev_e->from].size() > 0) {
        cerr << "rev_e: (" << rev_e->from << ", " << rev_e->to << ")\n";
        for (int a : admissible_edge_ids_[rev_e->from]) {
          auto foo_e = edges_[a];
          cerr << "admissible edge: (" << foo_e->from << ", " << foo_e->to << ")\n";
        }
      }
      if (
        admissible_edge_ids_[rev_e->from].size() > 0
        && admissible_edge_ids_[rev_e->from].back() == rev_e->id_in_all_edge
      ) admissible_edge_ids_[rev_e->from].pop_back();
    }

    distance_to_active_v_[distance_label_[v]].push_back(v);
    max_active_v_distance_ = std::max(max_active_v_distance_, distance_label_[v]);
  }

  void solve_() {
    for (const std::shared_ptr<Edge> &e : residual_g_[source_]) {
      if (e->cap == 0) continue;
      if (e->to != target_) distance_to_active_v_[0].push_back(e->to);
      augment_flow_(e->id_in_all_edge, e->cap);
    }
    distance_label_[source_] = n_;
    cerr << "edges: " << endl;
    for (auto e : edges_) {
      cerr << "(" << e->from << ", " << e->to << "," << e->cap << ")" << endl;
    }
    if (distance_to_active_v_[0].empty()) return;
    while (max_active_v_distance_ >= 0) {
      delete_non_admissible_edges_();
      cerr << "max: " << max_active_v_distance_ << endl;
      cerr << "head: " << distance_to_active_v_[max_active_v_distance_].back() << endl;
      int active_v = distance_to_active_v_[max_active_v_distance_].back();
      if (admissible_edge_ids_[active_v].empty()) relabel_(active_v);
      else {
        push_(admissible_edge_ids_[active_v].back());
      }
      // admissible_edges_check_();
      while (
        max_active_v_distance_ >= 0
        && distance_to_active_v_[max_active_v_distance_].empty()
      ) --max_active_v_distance_;
    }
    return;
  }

  void delete_non_admissible_edges_() {
    int active_v = distance_to_active_v_[max_active_v_distance_].back();
    while (!admissible_edge_ids_[active_v].empty()) {
      const shared_ptr<Edge> &e = edges_[admissible_edge_ids_[active_v].back()];
      if (distance_label_[e->from] == distance_label_[e->to] + 1) break;
      admissible_edge_ids_[active_v].pop_back();
    }
  }

  void admissible_edges_check_() const {
    cerr << "----------\n";
    for (int i = 0; i < n_; ++i) {
      cerr << "Edges of " << i << endl;
      cerr << "Edge num: " << admissible_edge_ids_[i].size() << endl;
      for (auto iter = begin(admissible_edge_ids_[i]); iter != end(admissible_edge_ids_[i]); ++iter) {
        int e_id = *iter;
        const std::shared_ptr<Edge> &e = edges_[e_id];
        cerr << "edge: (" << e->from << ", " << e->to << ")";
        cerr << "dist: (" << distance_label_[e->from] << ", " << distance_label_[e->to] << ")\n";
        assert(distance_label_[e->from] == distance_label_[e->to] + 1);
      }
    }
    cerr << "----------\n";
  }

  std::vector<std::vector<std::shared_ptr<Edge>>> residual_g_;
  std::vector<std::shared_ptr<Edge>> edges_;
  const int n_, source_, target_;
  int max_active_v_distance_;
  // 各頂点の距離ラベル
  std::vector<int> distance_label_;

  // 距離ラベルの値毎の，活性点のリスト
  std::vector<std::list<int>> distance_to_active_v_;

  // 頂点毎の，出ていく使用可能辺のリスト
  std::vector<std::list<int>> admissible_edge_ids_;

  // 頂点毎の，流入量 - 流出量
  std::vector<T> excess_amount_;

  T max_flow_value_;
  std::vector<std::vector<std::pair<int, T>>> flow_;
}; // class PushRelabel
