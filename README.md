# kyopro-lib <!-- omit in toc -->
- [シグネチャ](#シグネチャ)
- [バリデーション](#バリデーション)
  - [old](#old)

## シグネチャ
* dijkstra:
  * `Dijkstra<CostType>(int n, const vector<vector<pair<int, CostType>>> &G, int src)`
    * `n`: グラフの頂点数．
    * `CostType`: 辺の重みの型．`int`または`long long`．
    * `G`: グラフの隣接行列．
    * `src`: 始点．

  * `CostType distance_to(int t)`
    * 頂点`t`までの距離を返す．

  * `pair<bool, vector<int>> path_to(int t)`
    * （頂点`t`までのパスが存在するかどうか，存在する場合はパスを表す頂点列）のペアを返す．
    * パスが存在しない場合，第2要素は空のベクトル．

* kruskal:
  * `Kruskal<CostType>(int n)`
    * `CostType`: 辺の重みの型．`int`または`long long`．
    * `n`: `グラフの頂点数．

  * `void add_edge(const int u, const int v, const CostType`
    * 2頂点`u`, `v`間を結ぶコスト`c`の無向辺を追加．
  
  * `void solve()`
    * 現段階での最小全域森を求める．
  
  * `bool is_mst()`
    * `solve()`の実行後に呼ぶことで，計算した全域森が全域木であるかどうかを返す．
  
  * `CostType get_cost_sum()`
    * `solve()`の実行後に呼ぶことで，計算した全域森の合計コストを返す．

  * `vector<tuple<int, int, CostType> get_msf`
    * `solve()`の実行後に呼ぶことで，計算した全域森を返す．
    * 全域森は，各辺を表す`tuple`<頂点, 頂点, コスト>の`vector`で表される．

* union_find:
  * `UnionFind(int n)`
    * `n`: 集合の要素数．
    * `int root(int x)`
      * 要素`x`に対する代表元を返す．
    
    * `bool is_same(int x, int y)`
      * `x`, `y`が同じグループに属している場合は`true`を返す．
      * そうでない場合は`false`を返す．
    
    * `bool unite(int x, int y)`
      * `x`, `y`が同じグループに属している場合は`false`を返し，何もしない．
      * そうでない場合は`x`の属するグループと`y`の属するグループを合併し，`true`を返す．

## バリデーション
* dijkstra: https://judge.yosupo.jp/submission/100397
* kruskal: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6934332#1
* union_find: https://judge.yosupo.jp/submission/102091

### old
* fenwick_tree: 
  * add, sum: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6381675#1 
  * lower_bound: https://atcoder.jp/contests/arc033/submissions/29947667
* indexed_segment_tree: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6318014#1
* modint: https://atcoder.jp/contests/abc055/submissions/29173328
* runlength: https://atcoder.jp/contests/abc019/submissions/30513094
* scc_graph: https://onlinejudge.u-aizu.ac.jp/status/users/okina25/submissions/1/GRL_3_C/judge/6435203/C++17
* segment_tree: https://judge.yosupo.jp/submission/78395
* topological_sort: https://judge.u-aizu.ac.jp/onlinejudge/submission.jsp# 