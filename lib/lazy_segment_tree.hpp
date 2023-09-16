#pragma once
/**
 * @file lazy_segment_tree.hpp
 * @brief 遅延セグメント木に関するコード。
 * @details
 * モノイドの演算に関する処理を以下の時間で行う。
 * * 区間計算クエリ：O(lg N)
 * * 区間更新クエリ：O(lg N)
 * * Validation
 *   * 区間加算、1点取得: https://onlinejudge.u-aizu.ac.jp/status/users/okina25/submissions/1/DSL_2_E/judge/8289629/C++17
 *   * 区間加算、区間min: https://onlinejudge.u-aizu.ac.jp/status/users/okina25/submissions/1/DSL_2_H/judge/8289658/C++17
 *   * 区間更新、区間min: https://onlinejudge.u-aizu.ac.jp/status/users/okina25/submissions/1/DSL_2_F/judge/8289721/C++17
 */

#include <cassert>
#include <functional>
#include <vector>

template <typename DataType, typename OperatorType>
class LazySegmentTree {
public:
  LazySegmentTree(int n,
                  const DataType identity_data,
                  const OperatorType identity_operator,
                  const std::function<DataType(DataType, DataType)> &fun_data,
                  const std::function<DataType(DataType, OperatorType)> &act,
                  const std::function<OperatorType(OperatorType, OperatorType)> &fun_operator
  ) : identity_data_(identity_data), identity_operator_(identity_operator),
      fun_data_(fun_data), fun_operator_(fun_operator), act_(act)
  {
    n_leaves_ = 1;
    while (n_leaves_ < n) n_leaves_ *= 2;
    data_ = std::vector<DataType>(2 * n_leaves_ - 1, identity_data_);
    lazy_ = std::vector<OperatorType>(2 * n_leaves_ - 1, identity_operator_);
  }

  /**
   * @brief 配列の初期値を設定する。`set()`を呼び終わった後に`built()`を呼ぶ。
   * @param pos 配列中の位置。
   * @param val 配列の値。
   */
  void set(int pos, DataType val) { data_[pos + n_leaves_ - 1] = val; }

  /**
   * @brief 配列の初期値が設定済みのセグメント木をO(N)で初期化する。
   */
  void build() {
    assert(!is_built_);
    for (int node = n_leaves_ - 2; node >= 0; --node) {
      data_[node] = fun_data_(data_[2 * node + 1], data_[2 * node + 2]);
    }
    is_built_ = true;
  }

  /**
   * @brief 半開区間[l, r)の区間更新をO(lg N)で行う。
   * @param l 区間の左端。
   * @param r 区間の右端。
   * @param new_val 作用素。
   */
  void update(int l, int r, OperatorType new_val) {
    assert(is_built_);
    update_inner_(l, r, new_val, 0, 0, n_leaves_);
  }

  /**
   * @brief 半開区間[l, r)の区間クエリにO(lg N)で応答する。
   * @param l 区間の左端。
   * @param r 区間の右端。
   * @param new_val 作用素。
   */
  DataType query(int query_left, int query_right) {
    assert(is_built_);
    return query_inner_(query_left, query_right, 0, 0, n_leaves_);
  }

private:
  bool is_built_ = false;
  int n_leaves_;
  DataType identity_data_;
  OperatorType identity_operator_;
  std::function<DataType(DataType, DataType)> fun_data_;
  std::function<OperatorType(OperatorType, OperatorType)> fun_operator_;
  std::function<DataType(DataType, OperatorType)> act_;
  std::vector<DataType> data_;
  std::vector<OperatorType> lazy_;

  void eval_(int node) {
    if (lazy_[node] == identity_operator_) return;
    if (node < n_leaves_ - 1) {
      lazy_[2 * node + 1] = fun_operator_(lazy_[2 * node + 1], lazy_[node]);
      lazy_[2 * node + 2] = fun_operator_(lazy_[2 * node + 2], lazy_[node]);
    }

    data_[node] = act_(data_[node], lazy_[node]);
    lazy_[node] = identity_operator_;
  }

  void update_inner_(
    int update_left, int update_right, DataType new_val, int node, int seg_left, int seg_right
  ) {
    eval_(node);
    // ノードの担当区間が更新区間に完全に収まる
    if (update_left <= seg_left && seg_right <= update_right){
      lazy_[node] = fun_operator_(lazy_[node], new_val);
      eval_(node);
    // ノードの担当区間が更新区間と重なる
    } else if (seg_left < update_right && update_left < seg_right) {
      update_inner_(
        update_left, update_right, new_val, 2 * node + 1, seg_left, (seg_left + seg_right) / 2
      );
      update_inner_(
        update_left, update_right, new_val, 2 * node + 2, (seg_left + seg_right) / 2, seg_right
      );
      data_[node] = fun_data_(data_[2 * node + 1], data_[2 * node + 2]);
    }
  }

  DataType query_inner_(int query_left, int query_right, int node, int seg_left, int seg_right) {
    eval_(node);
    // ノードの担当区間がクエリ区間に完全に収まる
    if (query_left <= seg_left && seg_right <= query_right) {
      return data_[node];
    }
    // ノードの担当区間がクエリ区間と重なる
    else if (seg_left < query_right && query_left < seg_right) {
      DataType c1 = query_inner_(
        query_left, query_right, 2 * node + 1, seg_left, (seg_left + seg_right) / 2
      );
      DataType c2 = query_inner_(
        query_left, query_right, 2 * node + 2, (seg_left + seg_right) / 2, seg_right
      );
      return fun_data_(c1, c2);
    }
    return identity_data_;
  }
};