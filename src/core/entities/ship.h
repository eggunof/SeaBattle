
#ifndef SEABATTLE_SRC_CORE_ENTITIES_SHIP_H_
#define SEABATTLE_SRC_CORE_ENTITIES_SHIP_H_

#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

namespace seabattle::entities {
class Ship {
 public:
  static constexpr uint8_t kMinShipLength = 1;
  static constexpr uint8_t kMaxShipLength = 4;

  enum class Orientation { HORIZONTAL, VERTICAL };

  class Segment {
    uint8_t health_{kDefaultShipSegmentHealth};

   public:
    Segment() = default;
    explicit Segment(uint8_t health);

    static constexpr uint8_t kDefaultShipSegmentHealth = 3;

    void Hit(uint8_t damage = 1);
    [[nodiscard]] uint8_t GetHealth() const { return health_; }
    [[nodiscard]] bool IsSunk() const { return health_ == 0; }
  };

 private:
  uint8_t length_;
  std::vector<Segment> segments_;

 public:
  explicit Ship(uint8_t length);
  Ship(const Ship &other) = default;
  Ship(Ship &&other) noexcept = default;
  Ship &operator=(const Ship &other) = default;
  Ship &operator=(Ship &&other) noexcept = default;

  [[nodiscard]] uint8_t GetLength() const;
  [[nodiscard]] bool IsSunk() const;

  Segment &GetSegment(uint8_t index);

  explicit Ship(const json &j);
  explicit operator json() const;
};

}  // namespace seabattle::entities

#endif  // SEABATTLE_SRC_CORE_ENTITIES_SHIP_H_
