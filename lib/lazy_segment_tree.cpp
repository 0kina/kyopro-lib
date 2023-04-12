#pragma once

#include <functional>
#include <vector>

template <typename T, typename U>
class LazySegmentTree {
 public:
  LazySegmentTree(int n, const T identity_elem_T, U identity_elem_U,
                  std::function<T(T, T)> fun_T, std::function<T(T, U)> fun_A, std::function<U(U, U)> fun_M)
  : identity_elem_T(identity_elem_T), identity_elem_U(identity_elem_U), fun_T(fun_T), fun_A(fun_A), fun_U(fun_U) {
    n_leaves = 1;
    while (n_leaves < n) n_leaves *= 2;
    val = std::vector<T>(2 * n_leaves - 1, identity_elem);
    lazy = std::vector<T>(2 * n_leaves - 1, identity_elem);
  }

  void update(int l, int r, T new_val) {
    update_main(l, r, new_val);
  }

  T query(int query_left, int query_right) {
    return query_main(query_left, query_right, 0, 0, n_leaves);
  }

  T operator[] (int pos) {
    return val[pos + n_leaves - 1];
  }

 private:
  int n_leaves;
  T identity_elem_T;
  U identity_elem_U;
  std::function<T(T, T)> fun_T;
  std::function<T(T, U)> fun_A;
  std::function<U(U, U)> fun_U;
  std::vector<T> val;
  std::vector<U> lazy;

  void eval(int node) {
    if (lazy[node] == identity_elem) return;
    if (node < n_leaves - 1) {
      lazy[2 * node + 1] = fun_U(lazy[2 * k + 1], lazy[node]);
      lazy[2 * node + 2] = fun_U(lazy[2 * k + 2], lazy[node]);
    }

    val[node] = fun_A(val[node], lazy[node]);
    lazy[node] = identity_elem_U;
  }

  void update_main(int update_left, int update_right, T new_val, int node, int seg_left, int seg_right) {
    eval(node);
    if (update_left >= seg_right || update_right <= seg_left) return;

    if (update_left <= seg_left && update_right >= seg_right){
      lazy[node] = fun_U(lazy[node], new_val);
      eval(node);
    } else {
      update(update_left, update_right, new_val, 2 * node + 1, seg_left, (seg_left + seg_right) / 2);
      update(update_left, update_right, new_val, 2 * node + 1, (seg_left + seg_right) / 2, seg_right);
      val[node] = fun_T(val[2 * node + 1], val[2 * node + 2]);
    }
  }

  T query_main(int query_left, int query_right, int node, int seg_left, int seg_right) {
    eval(node);
    if (query_left >= seg_right || query_right <= seg_left) return identity_elem;

    if (query_left <= seg_left && query_right >= seg_right) return val[node];
    else {
      T c1 = query_main(query_left, query_right, 2 * node + 1, seg_left, (seg_left + seg_right) / 2);
      T c2 = query_main(query_left, query_right, 2 * node + 2, (seg_left + seg_right) / 2, seg_right);
      return fun(c1, c2);
    }
  }
};