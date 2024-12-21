
#include "place_ships.h"

#include "../../errors/impossible_ship_position_error.h"
#include "../game.h"
#include "setup_bot.h"

namespace seabattle::states {

PlaceShips::PlaceShips(Game& game, const size_t current_ship_index,
                       const entities::Ship::Orientation selected_orientation,
                       const Coordinates& selected_position)
    : State(game),
      game_field_(game.GetHumanPlayer().GetGameField()),
      current_ship_(game.GetHumanPlayer().GetShipManager().begin() +
                    static_cast<long>(current_ship_index)),
      selected_orientation_(selected_orientation),
      selected_position_(selected_position) {
  game_.Render(
      "Place ships on field (UP/DOWN, LEFT/RIGHT to adjust position, SECONDARY "
      "to rotate ship, PRIMARY to continue)");
  game_field_.RevealCompletely();
  Render();
}

void PlaceShips::HandleCommand(const input::Command command) {
  switch (command) {
    case input::Command::PRIMARY:
      try {
        game_field_.PlaceShip(*current_ship_, selected_position_,
                              selected_orientation_);
        game_.Render("Ship placed successfully");
      } catch (const errors::ImpossibleShipPositionError& e) {
        game_.Render(e);
        break;
      }
      ++current_ship_;
      if (current_ship_ != game_.GetHumanPlayer().GetShipManager().end()) {
        game_.Render("Next ship's length is " +
                     std::to_string(current_ship_->GetLength()));
        selected_position_ = {0, 0};
        selected_orientation_ = entities::Ship::Orientation::VERTICAL;
      } else {
        game_.Render("All ships placed!");
        game_.Render(game_field_);
        game_field_.HideCompletely();
        game_.GetHumanPlayer().GetAbilityManager() =
            abilities::AbilityManager();
        game_.UpdateState(new SetupBot(game_));
        return;
      }
      break;
    case input::Command::SECONDARY:
      selected_orientation_ =
          selected_orientation_ == entities::Ship::Orientation::HORIZONTAL
              ? entities::Ship::Orientation::VERTICAL
              : entities::Ship::Orientation::HORIZONTAL;
      break;
    case input::Command::UP:
      if (selected_position_.y > 0) --selected_position_.y;
      break;
    case input::Command::DOWN:
      if ((selected_orientation_ == entities::Ship::Orientation::VERTICAL &&
           selected_position_.y <
               game_field_.GetDimensions().y - current_ship_->GetLength()) ||
          (selected_orientation_ == entities::Ship::Orientation::HORIZONTAL &&
           selected_position_.y < game_field_.GetDimensions().y - 1)) {
        ++selected_position_.y;
      }
      break;
    case input::Command::LEFT:
      if (selected_position_.x > 0) --selected_position_.x;
      break;
    case input::Command::RIGHT:
      if ((selected_orientation_ == entities::Ship::Orientation::HORIZONTAL &&
           selected_position_.x <
               game_field_.GetDimensions().x - current_ship_->GetLength()) ||
          (selected_orientation_ == entities::Ship::Orientation::VERTICAL &&
           selected_position_.x < game_field_.GetDimensions().x - 1)) {
        ++selected_position_.x;
      }
      break;
    default:
      break;
  }
  Render();
}

void PlaceShips::Render() const {
  auto end_of_mark = selected_position_;
  switch (selected_orientation_) {
    case entities::Ship::Orientation::VERTICAL:
      end_of_mark.y += current_ship_->GetLength() - 1;
      break;
    case entities::Ship::Orientation::HORIZONTAL:
      end_of_mark.x += current_ship_->GetLength() - 1;
      break;
  }
  game_.Render(game_field_, Area{selected_position_, end_of_mark});
}

State::Name PlaceShips::GetName() { return kName; }

PlaceShips::PlaceShips(Game& game, const json& j)
    : PlaceShips(
          game, j["current_ship_index"],
          static_cast<entities::Ship::Orientation>(j["selected_orientation"]),
          Coordinates(j["selected_position"])) {}

PlaceShips::operator json() const {
  json j;
  j["current_ship_index"] =
      current_ship_ - game_.GetHumanPlayer().GetShipManager().begin();
  j["selected_orientation"] = selected_orientation_;
  j["selected_position"] = json(selected_position_);
  return j;
}

}  // namespace seabattle::states
