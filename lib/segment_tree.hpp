#pragma once
/**
 * @file segment_tree.hpp
 * @brief セグメント木に関するコード。
 * @details
 * モノイドの演算に関する処理を以下の時間で行う。
 * * 区間計算クエリ：O(lg N)
 * * 1点更新クエリ：O(lg N)
 * @example segment_tree_example.cpp
 */

#include <functional>
#include <vector>

template <typename DataType>
class SegmentTree {
public:
  SegmentTree<DataType>(
    int n,
    const DataType identity_elem,
    const std::function<DataType(DataType, DataType)> fun
  ) : _identity_elem(identity_elem), _fun(fun) {
    _n_leaves = 1;
    while (_n_leaves < n) _n_leaves *= 2;

    _val = std::vector<DataType>(_n_leaves * 2 - 1, identity_elem);
  }

  /**
   * @brief 1点更新をO(lg n)で行う。
   *
   * @param pos 更新箇所。
   * @param new_val 更新値。
   */
  void update(int pos, DataType new_val) {
    pos += _n_leaves - 1;
    _val[pos] = new_val;
    while (pos > 0) {
      pos = (pos - 1) / 2;
      _val[pos] = _fun(_val[2 * pos + 1], _val[2 * pos + 2]);
    }
  }

  /**
   * @brief 半開区間の区間クエリをO(lg n)で行う。
   *
   * @param query_left クエリの左端。計算時に含まれる。
   * @param query_right クエリの右端。計算時に含まれない。
   * @return 区間クエリの結果。
   */
  DataType query(int query_left, int query_right) {
    return _query_inner(query_left, query_right, 0, 0, _n_leaves);
  }

  /**
   * @brief 現在の値をO(1)で取得する。
   */
  DataType operator[](int idx) const {
    return _val[idx + _n_leaves - 1];
  }

private:
  int _n_leaves;
  DataType _identity_elem;
  std::function<DataType(DataType, DataType)> _fun;
  std::vector<DataType> _val;

  DataType _query_inner(int query_left, int query_right, int node, int seg_left, int seg_right) {
    // クエリがノードの担当範囲外
    if (seg_right <= query_left || query_right <= seg_left) return _identity_elem;

    // ノードの担当範囲がクエリに完全に収まる
    if (query_left <= seg_left && seg_right <= query_right) return _val[node];
    // ノードの担当範囲がクエリと部分的に重なる
    else {
      DataType c1 = _query_inner(
        query_left, query_right,
        node * 2 + 1, seg_left, (seg_left + seg_right) / 2
      );
      DataType c2 = _query_inner(
        query_left, query_right,
        node * 2 + 2, (seg_left + seg_right) / 2, seg_right
      );
      return _fun(c1, c2);
    }
  }

}; // class SegmentTree

/**
 * @brief 半群をセグメント木に載せるためのクラス。
 */
template <typename DataType>
class SemigroupSegmentTree {
public:
  /**
   * @brief SemigroupSegmentTreeクラスのコンストラクタ。
   * @param identity_elem 配列の値および演算結果として有効でない値。
   */
  SemigroupSegmentTree<DataType>(
    int n,
    const DataType identity_elem,
    const std::function<DataType(DataType, DataType)> fun
  ) : _identity_elem(identity_elem), _fun(fun) {
    _n_leaves = 1;
    while (_n_leaves < n) _n_leaves *= 2;

    _val = std::vector<DataType>(_n_leaves * 2 - 1, identity_elem);
  }

  /**
   * @brief 1点更新をO(lg n)で行う。
   *
   * @param pos 更新箇所。
   * @param new_val 更新値。
   */
  void update(int pos, DataType new_val) {
    pos += _n_leaves - 1;
    _val[pos] = new_val;
    while (pos > 0) {
      pos = (pos - 1) / 2;
      _val[pos] = _fun(_val[2 * pos + 1], _val[2 * pos + 2]);
    }
  }

  /**
   * @brief 半開区間の区間クエリをO(lg n)で行う。
   *
   * @param query_left クエリの左端。計算時に含まれる。
   * @param query_right クエリの右端。計算時に含まれない。
   * @return 区間クエリの結果。
   */
  DataType query(int query_left, int query_right) {
    return _query_inner(query_left, query_right, 0, 0, _n_leaves);
  }

  /**
   * @brief 現在の値をO(1)で取得する。
   */
  DataType operator[](int idx) const {
    return _val[idx + _n_leaves - 1];
  }

private:
  int _n_leaves;
  DataType _identity_elem;
  std::function<DataType(DataType, DataType)> _fun;
  std::vector<DataType> _val;

  DataType _query_inner(int query_left, int query_right, int node, int seg_left, int seg_right) {
    // クエリがノードの担当範囲外
    if (seg_right <= query_left || query_right <= seg_left) return _identity_elem;

    // ノードの担当範囲がクエリに完全に収まる
    if (query_left <= seg_left && seg_right <= query_right) return _val[node];
    // ノードの担当範囲がクエリと部分的に重なる
    else {
      DataType c1 = _query_inner(
        query_left, query_right,
        node * 2 + 1, seg_left, (seg_left + seg_right) / 2
      );
      DataType c2 = _query_inner(
        query_left, query_right,
        node * 2 + 2, (seg_left + seg_right) / 2, seg_right
      );
      if (c1 == _identity_elem) return c2;
      if (c2 == _identity_elem) return c1;
      return _fun(c1, c2);
    }
  }

}; // class SemigroupSegmentTree