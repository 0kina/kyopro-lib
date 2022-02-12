#pragma once

#include <functional>
#include <vector>

template <typename DataType>
class SegmentTree {
  using NodeType = std::pair<DataType, int>;

 public:
  SegmentTree<DataType>(int n, const DataType identity_elem,
                        std::function<DataType(DataType, DataType)> val_fun)
    : identity_elem(identity_elem) {
    n_leaves = 1;
    while (n_leaves < n) n_leaves *= 2;

    val = std::vector<NodeType>(n_leaves * 2 - 1, {identity_elem, -1});
    for (int i = 0; i < n; ++i) {
      val[n_leaves - 1 + i].second = i;
    }

    fun = [=](NodeType a, NodeType b) {
      if (a.first == b.first) {
        if (a.second != -1) return a;
        else return b;
      } else {
        DataType tmp = val_fun(a.first, b.first);
        if (tmp == a.first) return a;
        else return b;
      }
    };
  }

  void update(int pos, DataType new_val) {
    pos += n_leaves - 1;
    val[pos].first = new_val;
    while (pos > 0) {
      pos = (pos - 1) / 2;
      val[pos] = fun(val[2 * pos + 1], val[2 * pos + 2]);
    }
  }

  NodeType query(int query_left, int query_right) {
    return query_main(query_left, query_right, 0, 0, n_leaves);
  }

 private:
  int n_leaves;
  DataType identity_elem;
  std::function<NodeType(NodeType, NodeType)> fun;
  std::vector<NodeType> val;

  NodeType query_main(int query_left, int query_right, int node, int seg_left, int seg_right) {
    if (query_left >= seg_right || query_right <= seg_left) return std::make_pair(identity_elem, -1);

    if (query_left <= seg_left && query_right >= seg_right) return val[node];
    else {
      NodeType c1 = query_main(query_left, query_right, node * 2 + 1, seg_left, (seg_left + seg_right) / 2);
      NodeType c2 = query_main(query_left, query_right, node * 2 + 2, (seg_left + seg_right) / 2, seg_right);
      return fun(c1, c2);
    }
  }
};