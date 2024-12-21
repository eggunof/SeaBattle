

#include "game_field.h"

#include "../../errors/impossible_ship_position_error.h"
#include "../../errors/invalid_coordinates_error.h"
#include "ship.h"

namespace seabattle::entities {

GameField::GameField(const Coordinates &dimensions)
    : dimensions_(dimensions),
      cells_(dimensions.y, std::vector<Cell>(dimensions.x)) {}

const Coordinates &GameField::GetDimensions() const { return dimensions_; }

Area GameField::GetArea() const {
  return {{0, 0}, {dimensions_.x - 1, dimensions_.y - 1}};
}

bool GameField::IsPlaceableOn(Area ship_area) const {
  try {
    ValidateArea(ship_area);
  } catch (const errors::InvalidCoordinatesError &) {
    return false;
  }
  ship_area.start -= {1, 1};
  ship_area.end += {1, 1};
  ship_area = ship_area.Intersection(GetArea());

  for (int32_t y = ship_area.start.y; y <= ship_area.end.y; ++y) {
    for (int32_t x = ship_area.start.x; x <= ship_area.end.x; ++x) {
      if (cells_[y][x].ship) {
        return false;
      }
    }
  }
  return true;
}

void GameField::PlaceShip(Ship &ship, const Coordinates &coordinates,
                          const Ship::Orientation orientation) {
  const auto &ship_length = ship.GetLength();
  const auto offset = orientation == Ship::Orientation::HORIZONTAL
                          ? Coordinates(1, 0)
                          : Coordinates(0, 1);
  if (const auto ship_area =
          Area(coordinates, coordinates + offset * (ship_length - 1));
      !IsPlaceableOn(ship_area)) {
    throw errors::ImpossibleShipPositionError();
  }

  for (uint8_t i = 0; i < ship_length; ++i) {
    auto &cell =
        cells_[coordinates.y + i * offset.y][coordinates.x + i * offset.x];
    cell.ship = &ship;
    cell.segment_index = i;
  }
}

void GameField::HideCell(const Coordinates &coordinates) {
  ValidateCoordinates(coordinates);
  cells_[coordinates.y][coordinates.x].is_revealed = false;
}

void GameField::RevealCell(const Coordinates &coordinates) {
  ValidateCoordinates(coordinates);
  cells_[coordinates.y][coordinates.x].is_revealed = true;
}

void GameField::ValidateCoordinates(const Coordinates &coordinates) const {
  if (!GetArea().Contains(coordinates)) {
    throw errors::InvalidCoordinatesError();
  }
}

void GameField::ValidateArea(const Area &area) const {
  if (!GetArea().Contains(area)) {
    throw errors::InvalidCoordinatesError();
  }
}

GameField::AttackResult GameField::AttackCell(const Coordinates &coordinates,
                                              const uint8_t damage) {
  RevealCell(coordinates);
  const auto &cell = cells_[coordinates.y][coordinates.x];
  const auto ship = cell.ship;
  if (!ship) return AttackResult::MISS;

  auto &segment = ship->GetSegment(cell.segment_index);
  if (segment.IsSunk()) return AttackResult::SEGMENT_ALREADY_DESTROYED;

  segment.Hit(damage);
  if (ship->IsSunk()) return AttackResult::SHIP_DESTROYED;
  if (segment.IsSunk()) return AttackResult::SEGMENT_DESTROYED;

  return AttackResult::SEGMENT_DAMAGED;
}

GameField::CellState GameField::GetCellState(
    const Coordinates &coordinates) const {
  ValidateCoordinates(coordinates);
  if (!cells_[coordinates.y][coordinates.x].is_revealed) {
    return CellState::UNKNOWN;
  }

  if (const auto ship = cells_[coordinates.y][coordinates.x].ship) {
    const auto health =
        ship->GetSegment(cells_[coordinates.y][coordinates.x].segment_index)
            .GetHealth();
    return static_cast<CellState>(
        static_cast<std::underlying_type_t<CellState>>(CellState::SEGMENT_0HP) +
        health);
  }
  return CellState::EMPTY;
}

void GameField::HideCompletely() {
  for (auto &row : cells_) {
    for (auto &cell : row) {
      cell.is_revealed = false;
    }
  }
}

void GameField::RevealCompletely() {
  for (auto &row : cells_) {
    for (auto &cell : row) {
      cell.is_revealed = true;
    }
  }
}

bool GameField::IsShip(const Coordinates &coordinates) const {
  ValidateCoordinates(coordinates);
  return cells_[coordinates.y][coordinates.x].ship != nullptr;
}

GameField::GameField(const json &j,
                     const std::unordered_map<uint16_t, Ship *> &ships_ids)
    : GameField(Coordinates(j["dimensions"])) {
  const auto &cells_json = j["cells"];
  for (size_t y = 0; y < cells_json.size(); ++y) {
    const auto &row_json = cells_json[y];
    for (size_t x = 0; x < row_json.size(); ++x) {
      const auto &cell_json = row_json[x];
      auto &[is_revealed, ship, index] = cells_[y][x];
      is_revealed = static_cast<bool>(cell_json["is_revealed"]);
      if (cell_json["ship_id"] != -1) ship = ships_ids.at(cell_json["ship_id"]);
      index = cell_json["segment_index"];
    }
  }
}

json GameField::ToJson(
    const std::unordered_map<const Ship *, uint16_t> &ships_ids) const {
  json j;
  j["dimensions"] = json(dimensions_);
  j["cells"] = json::array();
  for (int32_t y = 0; y < dimensions_.y; ++y) {
    j["cells"].emplace_back(json::array());
    for (int32_t x = 0; x < dimensions_.x; ++x) {
      const auto &[is_revealed, ship, segment_index] = cells_[y][x];
      j["cells"].back().push_back({{"is_revealed", is_revealed},
                                   {"ship_id", ship ? ships_ids.at(ship) : -1},
                                   {"segment_index", segment_index}});
    }
  }
  return j;
}

}  // namespace seabattle::entities
