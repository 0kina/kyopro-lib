#ifndef OKINA_GRID_TO_GRAPH
#define OKINA_GRID_TO_GRAPH

#include <cassert>
#include <map>
#include <queue>
#include <vector>

namespace okina_kyopro {

class GridToGraph {
private:
  const std::vector<std::vector<char>> grid_;
  char wall_char_;
  int h_, w_;
  int current_vertex_ID_;
  int current_edge_ID_ = 1;
  std::vector<std::vector<int>> point_type, edge_ID_;
  std::vector<std::vector<int>> edge_ID_to_vertex_ID_;
  const int UNKNOWN_ = -5, IN_VERTEX, IN_EDGE_ = -3, IN_VERTEX_ = -2, UNSET_ = -1;
  std::queue<std::pair<int, int>> vertex_qu_, edge_qu_;

  const std::vector<std::vector<int>> direction{
    std::vector<int>{-1, 0},
    std::vector<int>{1, 0},
    std::vector<int>{-1, -1},
    std::vector<int>{1, -1}
  };

  bool is_vertex_(int y_, int x_) {
    if (point_type[y_][x_] >= UNSET_) return true;
    if (grid_[y_][x_] == wall_char_) return false;

    if (grid_[y_][x_] != wall_char_ && grid_[y_][x_ - 1] != wall_char_
        && grid_[y_ - 1][x_] != wall_char_ && grid_[y_ - 1][x_ - 1] != wall_char_) {
      point_type[y_][x_] = UNSET_;
      if (point_type[y_][x_ - 1] == UNKNOWN_) point_type[y_][x_ - 1] = UNSET_;
      if (point_type[y_ - 1][x_] == UNKNOWN_) point_type[y_ - 1][x_] = UNSET_;
      if (point_type[y_ - 1][x_ - 1] == UNKNOWN_) point_type[y_ - 1][x_ - 1] = UNSET_;
      return true;
    }
    if (grid_[y_][x_] != wall_char_ && grid_[y_][x_ + 1] != wall_char_
        && grid_[y_ - 1][x_] != wall_char_ && grid_[y_ - 1][x_ + 1] != wall_char_) {
      point_type[y_][x_] = UNSET_;
      if (point_type[y_][x_ + 1] == UNKNOWN_) point_type[y_][x_ + 1] = UNSET_;
      if (point_type[y_ - 1][x_] == UNKNOWN_) point_type[y_ - 1][x_] = UNSET_;
      if (point_type[y_ - 1][x_ + 1] == UNKNOWN_) point_type[y_ - 1][x_ + 1] = UNSET_;
      return true;
    }
    if (grid_[y_][x_] != wall_char_ && grid_[y_][x_ - 1] != wall_char_
        && grid_[y_ + 1][x_] != wall_char_ && grid_[y_ + 1][x_ - 1] != wall_char_) {
      point_type[y_][x_] = UNSET_;
      if (point_type[y_][x_ - 1] == UNKNOWN_) point_type[y_][x_ - 1] = UNSET_;
      if (point_type[y_ + 1][x_] == UNKNOWN_) point_type[y_ + 1][x_] = UNSET_;
      if (point_type[y_ + 1][x_ - 1] == UNKNOWN_) point_type[y_ + 1][x_ - 1] = UNSET_;
      return true;
    }
    if (grid_[y_][x_] != wall_char_ && grid_[y_][x_ + 1] != wall_char_
        && grid_[y_ + 1][x_] != wall_char_ && grid_[y_ + 1][x_ + 1] != wall_char_) {
      point_type[y_][x_] = UNSET_;
      if (point_type[y_][x_ + 1] == UNKNOWN_) point_type[y_][x_ + 1] = UNSET_;
      if (point_type[y_ + 1][x_] == UNKNOWN_) point_type[y_ + 1][x_] = UNSET_;
      if (point_type[y_ + 1][x_ + 1] == UNKNOWN_) point_type[y_ + 1][x_ + 1] = UNSET_;
      return true;
    }

    point_type[y_][x_] = IN_EDGE_;
    return false;
  }

  int calc_vertex_ID_(int y_, int x_) {
    if (point_type[y_][x_] > UNSET_) return point_type[y_][x_];
    int vid = 2 * (w_ * y_ + x_);
    point_type[y_][x_] = vid;
    return vid;
  }

  void construct_vertex(int i_, int j_) {
    vertex_qu_.push({i_, j_});
    while (!vertex_qu_.empty()) {
      auto [y_, x_] = vertex_qu_.front();
      vertex_qu_.pop();
      for (auto [dy, dx] : direction) {
        if (is_vertex_(y_ + dy, x_ + dx) {
          if (&& point_type[y_ + dy][x_ + dx] != point_type[y_][x_]) {
            point_type[y_ + dy][x_ + dx] = point_type[y_][x_];
            vertex_qu_.emplace(y_ + dy, x_ + dx);
          }
        } else {
          // if (point_type[])
        }
      }
    }
  }


public:
  GridToGraph(const std::vector<std::vector<char>> &grid, char wall_char)
    : wall_char_(wall_char), h_(grid.size()), w_(grid[0].size()), grid_(h_ + 2, std::vector<char>(w_ + 2), wall_char_), point_type(h_ + 2, std::vector<int>(w_ + 2, UNKNOWN_)) {
    for (int i_ = 1; i_ <= h_; ++i_) {
      for (int j_ = 1; j_ <= w_; ++j_) {
        grid_[i_][j_] = grid[i_ - 1][j_ - 1];
      }
    }

    for (int i_ = 1; i_ <= h_; ++i_) {
      for (int j_ = 1; j_ <= w_; ++j_) {
        if (grid_[i_][j_] == wall_char_) continue;

  
        if (is_vertex(i_, j_)) {
          if (point_type[i_][j_] > UNSET_) continue;
          current_edge_ID_ = calc_vertex_ID_(i_, j_);
          vertex_qu.push({i_, j_});
        } else {
          edge_qu.push({i_, j_});
        }


      }
    }

  }

  bool is_vertex(int y, int x) {
    return point_type[y + 1][x + 1] % 2 == 0;
  }

  int get_vertex_ID(int y, int x) {
    assert(is_vertex(y, x));
    return point_type[y + 1][x + 1];
  }
}

} // namespace okina_kyopro

#endif // OKINA_GRID_TO_GRAPH