#pragma once

#include <vector>

struct FlowEdge {
  int to;
  long long cap;
  int rev;

  FlowEdge(int to, long long cap, int rev) : to(to), cap(cap), rev(rev) {};

  void print_edge() {
    debug(to);
    debug(cap);
    debug(rev);
  };
};

class FlowGraph {
 public:
  FlowGraph(int n) : used(n, false), g(n) {};

  void print() {
    for (auto row : g) {
      for (auto e : row) e.print_edge();
      cerr << endl;
    }
  }

  void add_directed_edge(int from, int to, long long cap) {
    g[from].push_back(FlowEdge{to, cap, (int)g[to].size()});
    g[to].push_back(FlowEdge{from, 0, (int)g[from].size() - 1});
  }

  long long max_flow(int s, int t) {
    long long flow = 0LL;
    while (true) {
      long long f = flow_dfs(s, t, INF);
      cerr << "f: " << f << endl;
      if (f == 0LL) return flow;
      flow += f;
    }
  }

 private:
  std::vector<bool> used;
  std::vector<std::vector<FlowEdge>> g;

  const long long INF = 1000000000;

  long long flow_dfs(int s, int t, long long mincap) {
    if (s == t) return mincap;
    used[s] = true;
    for (auto &e : g[s]) {
      if (!used[e.to] && e.cap > 0) {
        long long d = flow_dfs(e.to, t, std::min(mincap, e.cap));
        if (d > 0) {
          e.cap -= d;
          g[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }
};