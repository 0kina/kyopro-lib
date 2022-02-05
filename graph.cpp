#include <vector>

template <typename T = int>
struct Edge {
 public:
  int from, to, id;
  T weight;

  Edge(int from, int to, T weight = 1, int id = -1) : from(from), to(to), weight(weight), id(id) {}
};

template <typename T = int>
struct Graph {
 public:
  std::vector<std::vector<Edge<T>>> g;
  
  explicit Graph(int n) :g(n), siz(0) {}

  void add_edge(int from, int to, T weight = 1) {
    g[from].emplace_back(from, to, weight, siz);
    g[to].emplace_back(to, from, weight, siz++);
  }

  void add_directed_edge(int from, int to, T weight = 1) {
    g[from].emplace_back(from, to, weight, siz++);
  }

  std::vector<Edge<T>> &operator[](int const &k) {
    return g[k];
  }

  std::size_t size() {
    return g.size();
  }

 private:
  int siz;
};