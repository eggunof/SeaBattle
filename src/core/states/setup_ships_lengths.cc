
#include "setup_ships_lengths.h"

#include "../game.h"
#include "place_ships.h"

namespace seabattle::states {

SetupShipsLengths::SetupShipsLengths(Game& game,
                                     const std::vector<uint8_t>& ship_sizes,
                                     const size_t selected_ship_index)
    : State(game),
      cells_(game_.GetHumanPlayer().GetGameField().GetDimensions().x *
             game_.GetHumanPlayer().GetGameField().GetDimensions().y),
      ship_sizes_(ship_sizes),
      selected_ship_index_(selected_ship_index) {
  game_.Render(
      "Select ships' lengths (UP/DOWN to adjust size, LEFT/RIGHT to select "
      "ship, SECONDARY to delete ship, PRIMARY to continue)");
  Render();
}

void SetupShipsLengths::HandleCommand(const input::Command command) {
  switch (command) {
    case input::Command::PRIMARY:
      game_.GetHumanPlayer().GetShipManager() =
          entities::ShipManager(ship_sizes_);
      game_.UpdateState(new PlaceShips(game_));
      return;
    case input::Command::SECONDARY:
      if (ship_sizes_.size() <= 1) {
        game_.Render("At least one ship must be placed");
        break;
      }
      ship_sizes_.erase(ship_sizes_.begin() +
                        static_cast<long>(selected_ship_index_));
      if (selected_ship_index_ >= ship_sizes_.size()) {
        selected_ship_index_ = ship_sizes_.size() - 1;
      }
      Render();
      break;
    case input::Command::UP:
      if (ship_sizes_[selected_ship_index_] >= entities::Ship::kMaxShipLength) {
        game_.Render("Ship max length exceeded");
        break;
      }
      if (CountOccupiedCells() + 3 > cells_) {
        game_.Render("Not enough free cells available");
        break;
      }
      for (auto it = ship_sizes_.rbegin(); it != ship_sizes_.rend(); ++it) {
      }
      ++ship_sizes_[selected_ship_index_];
      break;
    case input::Command::DOWN:
      if (ship_sizes_[selected_ship_index_] <= entities::Ship::kMinShipLength) {
        game_.Render("Ship min length exceeded");
        break;
      }
      --ship_sizes_[selected_ship_index_];
      break;
    case input::Command::RIGHT:
      ++selected_ship_index_;
      if (selected_ship_index_ >= ship_sizes_.size()) {
        if (CountOccupiedCells() + 9 > cells_) {
          game_.Render("Not enough free cells available");
          --selected_ship_index_;
          break;
        }
        ship_sizes_.resize(selected_ship_index_ + 1, 1);
      }
      break;
    case input::Command::LEFT:
      if (selected_ship_index_ > 0) {
        --selected_ship_index_;
      }
      break;
    default:
      break;
  }
  Render();
}

void SetupShipsLengths::Render() const {
  std::string message = "Ship sizes: ";
  for (size_t i = 0; i < ship_sizes_.size(); ++i) {
    if (i == selected_ship_index_) {
      message += "[" + std::to_string(ship_sizes_[i]) + "] ";
    } else {
      message += std::to_string(ship_sizes_[i]) + " ";
    }
  }
  game_.Render(message);
}

uint32_t SetupShipsLengths::CountOccupiedCells() const {
  uint32_t occupied_cells = 0;
  for (const auto& ship_size : ship_sizes_) {
    occupied_cells += ship_size * 3 + 6;
  }
  return occupied_cells;
}

State::Name SetupShipsLengths::GetName() { return kName; }

SetupShipsLengths::SetupShipsLengths(Game& game, const json& j)
    : SetupShipsLengths(
          game,
          [&] {
            std::vector<uint8_t> ship_sizes;
            for (const auto& ship_size_json : j["ship_sizes"]) {
              ship_sizes.push_back(ship_size_json);
            }
            return ship_sizes;
          }(),
          j["selected_ship_index"]) {}

SetupShipsLengths::operator json() const {
  json j;
  j["ship_sizes"] = json(ship_sizes_);
  j["selected_ship_index"] = json(selected_ship_index_);
  return j;
}

}  // namespace seabattle::states