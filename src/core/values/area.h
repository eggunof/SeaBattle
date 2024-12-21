
#ifndef SEABATTLE_SRC_CORE_VALUES_AREA_H_
#define SEABATTLE_SRC_CORE_VALUES_AREA_H_

#include <algorithm>

#include "coordinates.h"

namespace seabattle::values {

struct Area {
  Coordinates start;
  Coordinates end;

  constexpr Area() = default;
  constexpr Area(const Coordinates& first, const Coordinates& second)
      : start(first), end(second) {
    if (start.x > end.x) std::swap(start.x, end.x);
    if (start.y > end.y) std::swap(start.y, end.y);
  }

  [[nodiscard]] bool Contains(const Coordinates& coordinates) const;
  [[nodiscard]] bool Contains(const Area& other) const;
  [[nodiscard]] bool Intersects(const Area& other) const;
  [[nodiscard]] Area Intersection(const Area& other) const;
};

}  // namespace seabattle::values

#endif  // SEABATTLE_SRC_CORE_VALUES_AREA_H_
