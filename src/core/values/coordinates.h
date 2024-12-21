
#ifndef SEABATTLE_SRC_CORE_VALUES_COORDINATES_H_
#define SEABATTLE_SRC_CORE_VALUES_COORDINATES_H_

#include <cstdint>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace seabattle::values {

struct Coordinates {
  int32_t x;
  int32_t y;
  constexpr Coordinates() : x(0), y(0) {}
  constexpr Coordinates(const int32_t& x, const int32_t& y) : x(x), y(y) {}

  Coordinates& operator-();
  Coordinates& operator+=(const Coordinates& other);
  Coordinates& operator-=(const Coordinates& other);
  Coordinates& operator*=(int32_t scalar);
  Coordinates& operator/=(int32_t scalar);

  Coordinates operator-() const;
  Coordinates operator+(const Coordinates& other) const;
  Coordinates operator-(const Coordinates& other) const;
  Coordinates operator*(int32_t scalar) const;
  Coordinates operator/(int32_t scalar) const;

  bool operator==(const Coordinates& rhs) const;
  bool operator!=(const Coordinates& rhs) const;

  explicit Coordinates(const json& j);
  explicit operator json() const;
};

}  // namespace seabattle::values

#endif  // SEABATTLE_SRC_CORE_VALUES_COORDINATES_H_
