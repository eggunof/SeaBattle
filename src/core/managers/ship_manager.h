
#ifndef SEABATTLE_SRC_CORE_ENTITIES_SHIP_MANAGER_H_
#define SEABATTLE_SRC_CORE_ENTITIES_SHIP_MANAGER_H_

#include "../entities/ship.h"

namespace seabattle::entities {

class ShipManager {
  std::vector<Ship> ships_;

 public:
  explicit ShipManager(const std::vector<uint8_t> &lengths = {});
  ShipManager(const ShipManager &other) = default;
  ShipManager(ShipManager &&other) noexcept = default;
  ShipManager &operator=(const ShipManager &other) = default;
  ShipManager &operator=(ShipManager &&other) noexcept = default;

  [[nodiscard]] bool IsAllShipsSunk() const;
  [[nodiscard]] uint16_t GetNumberOfShips() const { return ships_.size(); }

  using iterator = std::vector<Ship>::iterator;
  using const_iterator = std::vector<Ship>::const_iterator;
  iterator begin() { return ships_.begin(); }
  iterator end() { return ships_.end(); }
  [[nodiscard]] const_iterator begin() const { return ships_.cbegin(); }
  [[nodiscard]] const_iterator end() const { return ships_.cend(); }

  explicit ShipManager(const json &j);
};

}  // namespace seabattle::entities

#endif  // SEABATTLE_SRC_CORE_ENTITIES_SHIP_MANAGER_H_
