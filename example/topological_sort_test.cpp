#include <iostream>

#include "topological_sort.hpp"

using namespace std;

/*
* Graph
* (0) --> (1)             (8) --> (9)
*  |       |               ^
*  v       v               |
* (3) --> (2) --> (6) --> (5)
*                  ^       ^
*                  |       |
*                 (4) <-- (7)
*
* Output
* 0 7 1 3 4 2 6 5 8 9 
*/

int main() {
  int n = 10;
  vector<vector<int>> graph(n);
  graph[0].push_back(1);
  graph[0].push_back(3);
  graph[1].push_back(2);
  graph[2].push_back(6);
  graph[3].push_back(2);
  graph[4].push_back(6);
  graph[5].push_back(8);
  graph[6].push_back(5);
  graph[7].push_back(4);
  graph[7].push_back(5);
  graph[8].push_back(9);

  TopologicalSort tpl(graph);

  vector<int> sorted = tpl.sorted();
  for (auto iter = begin(sorted); iter != end(sorted); ++iter) {
    cout << *iter << " ";
  }
  cout << endl;
}