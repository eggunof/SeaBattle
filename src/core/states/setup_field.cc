
#include "setup_field.h"

#include <string>

#include "../game.h"
#include "setup_ships_lengths.h"

namespace seabattle::states {

SetupField::SetupField(Game& game, const Coordinates &current_field_size_)
    : State(game), current_field_size_(current_field_size_) {
  game_.Render(
      "Select field size (UP/DOWN, LEFT/RIGHT to adjust size, PRIMARY to "
      "continue)");
  Render();
}

void SetupField::Render() const {
  game_.Render("Field size: " + std::to_string(current_field_size_.x) + "x" +
               std::to_string(current_field_size_.y));
}

void SetupField::HandleCommand(const input::Command command) {
  switch (command) {
    case input::Command::UP:
      --current_field_size_.y;
      Render();
      break;
    case input::Command::DOWN:
      ++current_field_size_.y;
      Render();
      break;
    case input::Command::LEFT:
      --current_field_size_.x;
      Render();
      break;
    case input::Command::RIGHT:
      ++current_field_size_.x;
      Render();
      break;
    case input::Command::PRIMARY:
      game_.Render(
          "Setting field size: " + std::to_string(current_field_size_.x) + "x" +
          std::to_string(current_field_size_.y));
      game_.GetHumanPlayer().GetGameField() =
          entities::GameField(current_field_size_);

      game_.UpdateState(new SetupShipsLengths(game_));
      break;
    default:
      break;
  }
}

State::Name SetupField::GetName() { return kName; }

SetupField::SetupField(Game& game, const json& j)
    : SetupField(game, Coordinates(j["current_field_size"])) {}

SetupField::operator json() const {
  json j;
  j["current_field_size"] = json(current_field_size_);
  return j;
}

}  // namespace seabattle::states