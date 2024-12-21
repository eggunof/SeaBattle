
#include "ship_manager.h"

namespace seabattle::entities {

ShipManager::ShipManager(const std::vector<uint8_t> &lengths) {
  ships_.reserve(lengths.size());
  for (const auto &length : lengths) {
    ships_.emplace_back(length);
  }
}

bool ShipManager::IsAllShipsSunk() const {
  return std::ranges::all_of(ships_.begin(), ships_.end(),
                             [](const Ship &ship) { return ship.IsSunk(); });
}

ShipManager::ShipManager(const json &j) {
  ships_.reserve(j.size());
  for (const auto &ship_json : j) {
    ships_.emplace_back(ship_json);
  }
}

}  // namespace seabattle::entities