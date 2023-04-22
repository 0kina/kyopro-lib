/**
 * @file coordinates_compression.hpp
 * @brief 座標圧縮に関するコード。
 */
#ifndef OKINA_COORDINATES_COMPRESSION
#define OKINA_COORDINATES_COMPRESSION

#include <vector>

template <typename T>
class CoordComp {
public:
  CoordComp(const std::vector<T> &original) : _order(original) {
    std::sort(begin(_order), end(_order));
    _order.erase(std::unique(begin(_order), end(_order)), end(_order));
  }

  /**
   * @brief 圧縮後の座標を返す。O(log n)。
   * @param coordinate 圧縮前の座標。
   * @return 圧縮後の座標。
   */
  int pos(const T coordinate) {
    return std::lower_bound(begin(_order), end(_order), coordinate) - begin(_order);
  }

  std::vector<T> get_coords() const {
    return _order;
  }

private:
  std::vector<T> _order;
};

#endif // OKINA_COORDINATES_COMPRESSION