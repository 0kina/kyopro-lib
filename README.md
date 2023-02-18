# kyopro-lib <!-- omit in toc -->
- [シグネチャ](#シグネチャ)
- [バリデーション](#バリデーション)
  - [old](#old)

## シグネチャ
* dijkstra:
  * `Dijkstra<CostType>(const int n, int src)`
    * `n`: グラフの頂点数．
    * `CostType`: 辺の重みの型．`int`または`long long`．
    * `src`: 始点．
  
  * `void add_edge(const int u, const int v, const CostType c)`
    * 2頂点`u`, `v`間を結ぶコスト`c`の有向辺を追加．
  
  * `void solve()`
    * 最短経路を計算する．
  
  * `bool is_reachable(int t)`
    * 頂点`t`に到達可能かどうかを返す．

  * `CostType distance_to(int t)`
    * `is_reachable(t)`が`true`であるときに頂点`t`までの距離を返す．

  * `pair<bool, vector<int>> path_to(int t)`
    * `is_reachable(t)`が`true`であるときに，頂点`t`までのパスを表す頂点列を`vector`で返す．

* kruskal:
  * `Kruskal<CostType>(int n)`
    * `CostType`: 辺の重みの型．`int`または`long long`．
    * `n`: `グラフの頂点数．

  * `void add_edge(const int u, const int v, const CostType c)`
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

* runlength:
  * `vector<pair<T, int>> runlength(ForwardIterator first, ForwardIterator last)`
    * `ForwardIterator`は`T`を要素にもつコンテナのフォワードイテレータである必要がある．
    * `first`から`last`をランレングス符号化し，（値，連続数）の`pair`で構成される`vector`を返す．

* scc:
  * `SCC(int n)`
    * `n`: `グラフの頂点数．

  * `void add_edge(const int from, const int to)`
    * 2頂点`from`, `to`間を結ぶ有向辺を追加．
  
  * `void solve()`
    * 強連結成分を計算．
  
  * `vector<int> comp()`
    * 各頂点の強連結成分番号を表すサイズ`n`の`vector`を返す．
  
  * `bool is_same(const int u, const int v)`
    * 2頂点`u`, `v`が同じ強連結成分に属するかどうかを返す．
  
  * `int comp_size(const int u)`
    * 頂点`u`が属する強連結成分のサイズを返す．
  
  * `vector<vector<int>> scc()`
    * 第`i`成分が強連結成分番号`i`である頂点集合となるような2次元`vector`を返す．

* topological_sort:
  * `TopologicalSort(int n)`
  * `TopologicalSort(const vector<vector<int>>& graph, const vector<int>& in_degree)`
  * `TopologicalSort(const vector<vector<int>>& graph)`
    * `n`: グラフの頂点数。
    * `graph`: 有向グラフの隣接リスト。
    * `in_degree`: 各頂点の入次数。

  * `void add_edge(int from, int to)`
    * 有向辺の追加。

  * `void solve()`
    * トポロジカルソートの計算。

  * `vector<int> sorted()`
    * ソートした頂点列を返す。

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
* dijkstra: https://judge.yosupo.jp/submission/102399
* kruskal: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6934332#1
* modint: https://atcoder.jp/contests/abc055/submissions/29173328
* runlength: https://atcoder.jp/contests/abc019/submissions/34605758
* scc: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6937226#1
* union_find: https://judge.yosupo.jp/submission/102091

### old
* fenwick_tree: 
  * add, sum: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6381675#1 
  * lower_bound: https://atcoder.jp/contests/arc033/submissions/29947667
* indexed_segment_tree: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6318014#1
* segment_tree: https://judge.yosupo.jp/submission/78395
* topological_sort: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6940546#1