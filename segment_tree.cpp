#pragma once

#include <functional>
#include <vector>

template <typename DataType>
class SegmentTree {
 public:
  SegmentTree<DataType>(int n, const DataType identity_elem,
                        std::function<DataType(DataType, DataType)> fun)
    : identity_elem(identity_elem), fun(fun) {
    n_leaves = 1;
    while (n_leaves < n) n_leaves *= 2;

    val = std::vector<DataType>(n_leaves * 2 - 1, identity_elem);
  }

  void update(int pos, DataType new_val) {
    pos += n_leaves - 1;
    val[pos] = new_val;
    while (pos > 0) {
      pos = (pos - 1) / 2;
      val[pos] = fun(val[2 * pos + 1], val[2 * pos + 2]);
    }
  }

  DataType query(int query_left, int query_right) {
    return query_main(query_left, query_right, 0, 0, n_leaves);
  }

  DataType operator[](int idx) {
    return val[idx + n_leaves - 1];
  }

 private:
  int n_leaves;
  DataType identity_elem;
  std::function<DataType(DataType, DataType)> fun;
  std::vector<DataType> val;

  DataType query_main(int query_left, int query_right, int node, int seg_left, int seg_right) {
    if (query_left >= seg_right || query_right <= seg_left) return identity_elem;

    if (query_left <= seg_left && query_right >= seg_right) return val[node];
    else {
      DataType c1 = query_main(query_left, query_right, node * 2 + 1, seg_left, (seg_left + seg_right) / 2);
      DataType c2 = query_main(query_left, query_right, node * 2 + 2, (seg_left + seg_right) / 2, seg_right);
      return fun(c1, c2);
    }
  }

};