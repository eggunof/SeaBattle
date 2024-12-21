
#ifndef SEABATTLE_SRC_CORE_ENTITIES_GAME_FIELD_H_
#define SEABATTLE_SRC_CORE_ENTITIES_GAME_FIELD_H_

#include <cstdint>
#include <vector>

#include "../values/area.h"
#include "../values/coordinates.h"
#include "ship.h"

using namespace seabattle::values;

namespace seabattle::entities {

class GameField {
 public:
  enum class CellState { UNKNOWN, EMPTY, SEGMENT_0HP };

  enum class AttackResult {
    MISS,
    SEGMENT_DAMAGED,
    SEGMENT_DESTROYED,
    SEGMENT_ALREADY_DESTROYED,
    SHIP_DESTROYED
  };

  struct Cell {
    bool is_revealed{false};
    Ship *ship{nullptr};
    uint8_t segment_index{0};
  };

 private:
  Coordinates dimensions_;
  std::vector<std::vector<Cell>> cells_;

  void ValidateCoordinates(const Coordinates &coordinates) const;
  void ValidateArea(const Area &area) const;

 public:
  explicit GameField(const Coordinates &dimensions = {0, 0});
  GameField(const GameField &other) = default;
  GameField &operator=(const GameField &other) = default;
  GameField(GameField &&other) noexcept = default;
  GameField &operator=(GameField &&other) noexcept = default;

  [[nodiscard]] const Coordinates &GetDimensions() const;
  [[nodiscard]] Area GetArea() const;

  [[nodiscard]] CellState GetCellState(const Coordinates &coordinates) const;
  [[nodiscard]] bool IsPlaceableOn(Area ship_area) const;
  [[nodiscard]] bool IsShip(const Coordinates &coordinates) const;
  void PlaceShip(Ship &ship, const Coordinates &coordinates,
                 Ship::Orientation orientation);
  void HideCell(const Coordinates &coordinates);
  void RevealCell(const Coordinates &coordinates);
  void HideCompletely();
  void RevealCompletely();
  AttackResult AttackCell(const Coordinates &coordinates, uint8_t damage);

  GameField(const json &j,
            const std::unordered_map<uint16_t, Ship *> &ships_ids);
  [[nodiscard]] json ToJson(
      const std::unordered_map<const Ship *, uint16_t> &ships_ids) const;
};

}  // namespace seabattle::entities

#endif  // SEABATTLE_SRC_CORE_ENTITIES_GAME_FIELD_H_
