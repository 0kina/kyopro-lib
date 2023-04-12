#include <iostream>

#include "scc.hpp"

using namespace std;

/*
* Graph
* (0) --> (1)             (8) --> (9)
*  ^       |               ^
*  |       v               |
* (3) <-- (2) --> (6) --> (5)
*                  ^       |
*                  |       v
*                 (4) <-- (7)
*
* Output
* 0th vertex: 0th component, whose size is 4
* 1th vertex: 0th component, whose size is 4
* 2th vertex: 0th component, whose size is 4
* 3th vertex: 0th component, whose size is 4
* 4th vertex: 1th component, whose size is 4
* 5th vertex: 1th component, whose size is 4
* 6th vertex: 1th component, whose size is 4
* 7th vertex: 1th component, whose size is 4
* 8th vertex: 2th component, whose size is 1
* 9th vertex: 3th component, whose size is 1
* 0th component:
* 0 1 2 3 
* 1th component:
* 4 5 6 7 
* 2th component:
* 8 
* 3th component:
* 9 
*/

int main() {
  int n = 10;
  vector<vector<int>> graph(n);
  graph[0].push_back(1);
  graph[1].push_back(2);
  graph[2].push_back(3);
  graph[2].push_back(6);
  graph[3].push_back(0);
  graph[4].push_back(6);
  graph[5].push_back(7);
  graph[5].push_back(8);
  graph[6].push_back(5);
  graph[7].push_back(4);
  graph[8].push_back(9);

  SCC scc(graph);

  vector<int> comp_ids = scc.comp();
  for (int i = 0; i < n; ++i) {
    cout << i << "th vertex: " << comp_ids[i] << "th component, whose size is ";
    cout << scc.comp_size(i) << endl;
  }

  vector<vector<int>> components = scc.scc();
  for (int i = 0; i < components.size(); ++i) {
    cout << i << "th component:\n";
    for (int v : components[i]) {
      cout << v << " ";
    }
    cout << endl;
  }
}