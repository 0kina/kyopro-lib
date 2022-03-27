#pragma once

#include <queue>
#include <vector>

std::vector<int> topological_sort(std::vector<std::vector<int>> g) {
  int n = g.size();
  std::vector<int> in_degree(n, 0);

  for (int i = 0; i < n; ++i) {
    for (int v : g[i]) {
      ++in_degree[v];
    }
  }

  std::queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (in_degree[i] == 0) q.push(i);
  }

  std::vector<int> ret;

  while (!q.empty()) {
    int f = q.front();
    q.pop();

    ret.push_back(f);
    for (int v : g[f]) {
      if (--in_degree[v] == 0) q.push(v);
    }
  }

  return ret;
}