#pragma once
/**
 * @file rerooting.hpp
 * @brief 全方位木DPに関するコード．
 * @details
 * * 抽象化の参考：[抽象化全方位木DPのライブラリとドキュメント](https://trap.jp/post/1702/)
 * * Validation
 *   * [AOJ GRL_5_A](https://onlinejudge.u-aizu.ac.jp/status/users/okina25/submissions/1/GRL_5_A/judge/8375136/C++17)
 *   * [典型90 004](https://atcoder.jp/contests/typical90/submissions/46430551)
 */

#include <functional>
#include <vector>

/**
 * @brief 全方位木DPのためのクラス．
 * @tparam Dp 有向辺に対応する各部分木が表す情報の型．
 * @tparam Monoid 部分木と有向辺の情報から`put_edge()`によって計算される情報の型．子ノードのマージに使用される．
 * @tparam Edge 辺が持つ情報．
 * @tparam Vertex 頂点が持つ情報．
 */
template <typename Dp, typename Monoid, typename Edge=int, typename Vertex=int>
class Rerooting {
public:
  /**
   * @brief Rerootingクラスのコンストラクタ。
   * @param graph グラフ．各要素は(辺の終点，辺番号)を保持．
   * @param identity_elem Monoidの単位元．
   * @param merge Monoidの演算．
   * @param put_edge 部分木と有向辺の情報からマージに必要な情報を計算する関数．
   * @param put_vertex マージした情報からDPに格納する情報を計算する関数．
   * @param edges 各辺に格納された情報．
   * @param vertices 各頂点に格納された情報．
   */
  Rerooting(
    const std::vector<std::vector<std::pair<int, int>>> &graph,
    const Monoid identity_elem,
    const std::function<Monoid(Monoid, Monoid)> &merge,
    const std::function<Monoid(Dp, Edge)> &put_edge,
    const std::function<Dp(Monoid, Vertex)> &put_vertex,
    const std::vector<Edge> &edges=std::vector<Edge>(),
    const std::vector<Vertex> &vertices=std::vector<Vertex>()
  ) : graph_(graph), identity_elem_(identity_elem), merge_(merge),
      put_edge_(put_edge), put_vertex_(put_vertex), edges_(edges), vertices_(vertices),
      dp_(graph.size()), ans_(graph.size())
  {
    for (int i = 0; i < graph.size(); ++i) {
      dp_[i].resize(graph[i].size(), identity_elem);
    }
    solve_();
  }

  std::vector<int> get_ans() const { return ans_; }

private:
  void solve_() {
    dfs0_(0, -1);
    dfs1_(0, -1, identity_elem_);
  }

  /**
   * @brief 木DPを行うDFS
   * @param v 部分木の根
   * @param parent `v`の親
   * @return 部分木に対応するデータ
   */
  Dp dfs0_(int v, int parent) {
    Monoid merged_children = identity_elem_;
    for (int i = 0; i < graph_[v].size(); ++i) {
      auto [u, e_id] = graph_[v][i];
      if (u == parent) continue;
      if (dp_[v][i] == identity_elem_) {
        dp_[v][i] = dfs0_(u, v);
      }
      merged_children = merge_(merged_children, put_edge_(dp_[v][i], edges_[e_id]));
    }
    return put_vertex_(merged_children, vertices_[v]);
  }

  void dfs1_(int v, int parent, Dp parent_dp) {
    const int degree = graph_[v].size();
    for (int i = 0; i < degree; ++i) {
      if (graph_[v][i].first == parent) dp_[v][i] = parent_dp;
    }
    // [0, i)の累積
    std::vector<Monoid> acc_children(degree + 1, identity_elem_);
    // [i, degree - 1]の累積
    std::vector<Monoid> racc_children(degree + 1, identity_elem_);
    for (int i = 0; i < degree; ++i) {
      auto [u, e_id] = graph_[v][i];
      acc_children[i + 1] = merge_(acc_children[i], put_edge_(dp_[v][i], edges_[e_id]));
    }
    for (int i = 0; i < degree; ++i) {
      auto [u, e_id] = graph_[v][degree - i - 1];
      racc_children[degree - i - 1] = merge_(
        racc_children[degree - i],
        put_edge_(dp_[v][degree - i - 1], edges_[e_id])
      );
    }
    ans_[v] = put_vertex_(acc_children[degree], vertices_[v]);
    for (int i = 0; i < degree; ++i) {
      auto [u, e_id] = graph_[v][i];
      if (u == parent) continue;
      dfs1_(u, v, put_vertex_(merge_(acc_children[i], racc_children[i + 1]), v));
    }
  }

private:
  const std::vector<std::vector<std::pair<int, int>>> &graph_;
  const Monoid identity_elem_;
  const std::function<Monoid(Monoid, Monoid)> &merge_;
  const std::function<Monoid(Dp, Edge)> &put_edge_;
  const std::function<Dp(Monoid, Vertex)> &put_vertex_;
  const std::vector<Edge> &edges_;
  const std::vector<Vertex> &vertices_;
  // 頂点iから出るj本目の辺が指す部分木のデータ
  std::vector<std::vector<Dp>> dp_;
  std::vector<Dp> ans_;
}; // class Rerooting
