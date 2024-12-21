
#include "area.h"

namespace seabattle::values {

bool Area::Contains(const Coordinates& coordinates) const {
  return start.x <= coordinates.x && coordinates.x <= end.x &&
         start.y <= coordinates.y && coordinates.y <= end.y;
}

bool Area::Contains(const Area& other) const {
  return start.x <= other.start.x && other.end.x <= end.x &&
         start.y <= other.start.y && other.end.y <= end.y;
}

bool Area::Intersects(const Area& other) const {
  return start.x <= other.end.x && other.start.x <= end.x &&
         start.y <= other.end.y && other.start.y <= end.y;
}

Area Area::Intersection(const Area& other) const {
  if (!Intersects(other)) return {};
  return {{std::max(start.x, other.start.x), std::max(start.y, other.start.y)},
          {std::min(end.x, other.end.x), std::min(end.y, other.end.y)}};
}

}  // namespace seabattle::values
