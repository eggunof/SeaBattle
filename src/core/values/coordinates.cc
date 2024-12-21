
#include "coordinates.h"

namespace seabattle::values {

Coordinates& Coordinates::operator-() {
  x = -x;
  y = -y;
  return *this;
}

Coordinates& Coordinates::operator+=(const Coordinates& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Coordinates& Coordinates::operator-=(const Coordinates& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Coordinates& Coordinates::operator*=(const int32_t scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

Coordinates& Coordinates::operator/=(const int32_t scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}

Coordinates Coordinates::operator-() const { return -Coordinates(*this); }

Coordinates Coordinates::operator+(const Coordinates& other) const {
  return Coordinates(*this) += other;
}

Coordinates Coordinates::operator-(const Coordinates& other) const {
  return Coordinates(*this) -= other;
}
Coordinates Coordinates::operator*(const int32_t scalar) const {
  return Coordinates(*this) *= scalar;
}
Coordinates Coordinates::operator/(const int32_t scalar) const {
  return Coordinates(*this) /= scalar;
}

bool Coordinates::operator==(const Coordinates& rhs) const {
  return x == rhs.x && y == rhs.y;
}
bool Coordinates::operator!=(const Coordinates& rhs) const {
  return !(rhs == *this);
}

Coordinates::Coordinates(const json& j) : x(j["x"]), y(j["y"]) {}

Coordinates::operator json() const { return {{"x", x}, {"y", y}}; }

}  // namespace seabattle::values
