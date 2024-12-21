
#include "bot_player.h"

#include "../../../errors/cannot_place_bot_ships_error.h"

namespace seabattle::entities::players {

std::vector<std::pair<Coordinates, Ship::Orientation>>
BotPlayer::GetAvailableShipPositions(const uint8_t ship_length) const {
  const auto& dimensions = game_field_.GetDimensions();
  std::vector<std::pair<Coordinates, Ship::Orientation>> available_positions;
  for (int32_t y = 0; y < dimensions.y; ++y) {
    for (int32_t x = 0; x < dimensions.x; ++x) {
      const Coordinates coordinates(x, y);

      auto ship_area = Area(
          coordinates, coordinates + Coordinates(1, 0) * (ship_length - 1));
      if (game_field_.IsPlaceableOn(ship_area))
        available_positions.emplace_back(coordinates,
                                         Ship::Orientation::HORIZONTAL);
      ship_area = Area(coordinates,
                       coordinates + Coordinates(0, 1) * (ship_length - 1));
      if (game_field_.IsPlaceableOn(ship_area))
        available_positions.emplace_back(coordinates,
                                         Ship::Orientation::VERTICAL);
    }
  }
  return available_positions;
}

void BotPlayer::GenerateShipsPlacement() {
  for (auto& ship : ship_manager_) {
    auto available_positions = GetAvailableShipPositions(ship.GetLength());
    if (available_positions.empty()) {
      throw errors::CannotPlaceBotShipsError();
    }
    auto [coordinates, orientation] = rng_.GetRandom(available_positions);
    game_field_.PlaceShip(ship, coordinates, orientation);
  }
}

BotPlayer::Strategy BotPlayer::CheckAttackResult(
    const GameField::AttackResult attack_result) {
  switch (strategy_) {
    case Strategy::RANDOM:
      switch (attack_result) {
        case GameField::AttackResult::SEGMENT_DAMAGED:
          strategy_ = Strategy::FINISH_OFF;
          break;
        case GameField::AttackResult::SEGMENT_DESTROYED:
          strategy_ = Strategy::FIND_OUT_ORIENTATION;
          break;
        default:
          strategy_ = Strategy::RANDOM;
          break;
      }
      break;
    case Strategy::FINISH_OFF:
      switch (attack_result) {
        case GameField::AttackResult::SEGMENT_DAMAGED:
          strategy_ = Strategy::FINISH_OFF;
          break;
        case GameField::AttackResult::SHIP_DESTROYED:
          InitializeBeforeNextShip();
          strategy_ = Strategy::RANDOM;
          break;
        default:
          if (!ship_orientation_.first)
            strategy_ = Strategy::FIND_OUT_ORIENTATION;
          else if (!reached_ship_edge_)
            strategy_ = Strategy::REACH_EDGE;
          else
            strategy_ = Strategy::FINISH_LAST_SEGMENTS;
          break;
      }
      break;
    case Strategy::FIND_OUT_ORIENTATION:
      switch (attack_result) {
        case GameField::AttackResult::MISS:
          if (!chosen_directions_.empty()) {
            auto& offset = direction_map_.at(chosen_directions_.back());
            cursor_position -= offset;
          }
          strategy_ = Strategy::FIND_OUT_ORIENTATION;
          break;
        case GameField::AttackResult::SEGMENT_DAMAGED:
          if (!ship_orientation_.first)
            ship_orientation_ = {
                true, chosen_directions_.back() == Direction::UP ||
                              chosen_directions_.back() == Direction::DOWN
                          ? Ship::Orientation::VERTICAL
                          : Ship::Orientation::HORIZONTAL};
          strategy_ = Strategy::FINISH_OFF;
          break;
        case GameField::AttackResult::SEGMENT_DESTROYED:
        case GameField::AttackResult::SEGMENT_ALREADY_DESTROYED:
          if (ship_orientation_.first)
            ship_orientation_ = {
                true, chosen_directions_.back() == Direction::UP ||
                              chosen_directions_.back() == Direction::DOWN
                          ? Ship::Orientation::VERTICAL
                          : Ship::Orientation::HORIZONTAL};
          strategy_ = Strategy::REACH_EDGE;
          break;
        case GameField::AttackResult::SHIP_DESTROYED:
          InitializeBeforeNextShip();
          strategy_ = Strategy::RANDOM;
          break;
      }
      break;
    case Strategy::REACH_EDGE:
      switch (attack_result) {
        case GameField::AttackResult::MISS:
          reached_ship_edge_ = true;
          strategy_ = Strategy::FINISH_LAST_SEGMENTS;
          break;
        case GameField::AttackResult::SEGMENT_DAMAGED:
          strategy_ = Strategy::FINISH_OFF;
          break;
        case GameField::AttackResult::SHIP_DESTROYED:
          InitializeBeforeNextShip();
          strategy_ = Strategy::RANDOM;
          break;
        default:
          strategy_ = Strategy::REACH_EDGE;
          break;
      }
      break;
    case Strategy::FINISH_LAST_SEGMENTS:
      switch (attack_result) {
        case GameField::AttackResult::SEGMENT_DAMAGED:
          strategy_ = Strategy::FINISH_OFF;
          break;
        case GameField::AttackResult::SHIP_DESTROYED:
          InitializeBeforeNextShip();
          strategy_ = Strategy::RANDOM;
          break;
        default:
          strategy_ = Strategy::FINISH_LAST_SEGMENTS;
          break;
      }
      break;
  }
  return strategy_;
}

void BotPlayer::MoveCursor(const GameField& target_game_field) {
  switch (strategy_) {
    case Strategy::RANDOM:
      MoveCursorRandom(target_game_field);
      break;
    case Strategy::FINISH_OFF:
      // Don't move cursor
      break;
    case Strategy::FIND_OUT_ORIENTATION:
      MoveCursorFindOutOrientation(target_game_field);
      break;
    case Strategy::REACH_EDGE:
      MoveCursorReachEdge(target_game_field);
      break;
    case Strategy::FINISH_LAST_SEGMENTS:
      MoveCursorFinishLastSegments(target_game_field);
      break;
  }
}

void BotPlayer::MoveCursorRandom(const GameField& target_game_field) {
  auto& dimensions = target_game_field.GetDimensions();
  GameField::CellState cell_state;
  do {
    cursor_position.x = rng_.GetRandomInt(dimensions.x - 1);
    cursor_position.y = rng_.GetRandomInt(dimensions.y - 1);
    cell_state = target_game_field.GetCellState(cursor_position);
  } while (cell_state != GameField::CellState::UNKNOWN);
}

void BotPlayer::MoveCursorFindOutOrientation(
    const GameField& target_game_field) {
  std::vector<Direction> available_directions;
  for (const auto& [direction, offset] : direction_map_) {
    if (std::find(chosen_directions_.begin(), chosen_directions_.end(),
                  direction) != chosen_directions_.end())
      continue;
    Coordinates new_cursor_position = cursor_position + offset;
    if (!target_game_field.GetArea().Contains(new_cursor_position)) continue;
    switch (target_game_field.GetCellState(new_cursor_position)) {
      case GameField::CellState::EMPTY:
        continue;
      case GameField::CellState::UNKNOWN:
        available_directions.push_back(direction);
        break;
      default:
        ship_orientation_ = {
            true, direction == Direction::UP || direction == Direction::DOWN
                      ? Ship::Orientation::VERTICAL
                      : Ship::Orientation::HORIZONTAL};
        strategy_ = Strategy::REACH_EDGE;
        MoveCursorReachEdge(target_game_field);
        return;
    }
  }
  if (!available_directions.empty()) {
    if (available_directions.size() == 1) {
      ship_orientation_ = {
          true, available_directions.front() == Direction::UP ||
                        available_directions.front() == Direction::DOWN
                    ? Ship::Orientation::VERTICAL
                    : Ship::Orientation::HORIZONTAL};
      strategy_ = Strategy::REACH_EDGE;
      MoveCursorReachEdge(target_game_field);
      return;
    }
    chosen_directions_.push_back(rng_.GetRandom(available_directions));
    cursor_position += direction_map_.at(chosen_directions_.back());
  } else {
    strategy_ = Strategy::RANDOM;
  }
}

void BotPlayer::MoveCursorReachEdge(const GameField& target_game_field) {
  Direction direction;
  switch (ship_orientation_.second) {
    case Ship::Orientation::VERTICAL:
      direction = Direction::UP;
      break;
    case Ship::Orientation::HORIZONTAL:
      direction = Direction::LEFT;
      break;
  }

  GameField::CellState cell_state;
  do {
    cursor_position += direction_map_.at(direction);
    if (!target_game_field.GetArea().Contains(cursor_position)) {
      reached_ship_edge_ = true;
      strategy_ = Strategy::FINISH_LAST_SEGMENTS;
      MoveCursorFinishLastSegments(target_game_field);
      return;
    }
    cell_state = target_game_field.GetCellState(cursor_position);
    if (cell_state == GameField::CellState::EMPTY) {
      reached_ship_edge_ = true;
      strategy_ = Strategy::FINISH_LAST_SEGMENTS;
      MoveCursorFinishLastSegments(target_game_field);
      return;
    }
  } while (cell_state != GameField::CellState::UNKNOWN);
}

void BotPlayer::MoveCursorFinishLastSegments(
    const GameField& target_game_field) {
  Direction direction;
  switch (ship_orientation_.second) {
    case Ship::Orientation::VERTICAL:
      direction = Direction::UP;
      break;
    case Ship::Orientation::HORIZONTAL:
      direction = Direction::LEFT;
      break;
  }
  auto& offset = direction_map_.at(direction);
  GameField::CellState cell_state;
  do {
    cursor_position -= offset;
    cell_state = target_game_field.GetCellState(cursor_position);
    if (cell_state == GameField::CellState::EMPTY) {
      InitializeBeforeNextShip();
      strategy_ = Strategy::RANDOM;
      MoveCursorRandom(target_game_field);
      return;
    }
  } while (cell_state != GameField::CellState::UNKNOWN);
}

void BotPlayer::InitializeBeforeNextShip() {
  ship_orientation_.first = false;
  chosen_directions_.clear();
  reached_ship_edge_ = false;
}

BotPlayer::BotPlayer(const json& j)
    : Player(j),
      strategy_(static_cast<Strategy>(j["strategy"])),
      ship_orientation_(
          j["ship_orientation"]["confirmed"],
          static_cast<Ship::Orientation>(j["ship_orientation"]["orientation"])),
      chosen_directions_([&] {
        std::vector<Direction> temp;
        for (const auto& direction_json : j["chosen_directions"]) {
          temp.push_back(direction_json);
        }
        return temp;
      }()),
      reached_ship_edge_(j["reached_ship_edge"]) {}

BotPlayer::operator json() const {
  json j = Player::operator json();
  j["strategy"] = strategy_;
  j["ship_orientation"]["confirmed"] = ship_orientation_.first;
  j["ship_orientation"]["orientation"] = ship_orientation_.second;
  j["chosen_directions"] = json::array();
  for (const auto& direction : chosen_directions_) {
    j["chosen_directions"].push_back(direction);
  }
  j["reached_ship_edge"] = reached_ship_edge_;
  return j;
}

}  // namespace seabattle::entities::players
