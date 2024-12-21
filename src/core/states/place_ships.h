
#ifndef SEABATTLE_SRC_CORE_STATES_PLACE_SHIPS_H_
#define SEABATTLE_SRC_CORE_STATES_PLACE_SHIPS_H_

#include "../entities/game_field.h"
#include "../entities/ship.h"
#include "../managers/ship_manager.h"
#include "state.h"

namespace seabattle::states {

class PlaceShips : public State {
  entities::GameField& game_field_;
  entities::ShipManager::iterator current_ship_;
  entities::Ship::Orientation selected_orientation_;
  Coordinates selected_position_;

  void Render() const;

 public:
  explicit PlaceShips(Game& game, size_t current_ship_index = 0,
                      entities::Ship::Orientation selected_orientation =
                          entities::Ship::Orientation::VERTICAL,
                      const Coordinates& selected_position = {0, 0});
  void HandleCommand(input::Command command) override;

  static constexpr Name kName = "PlaceShips";
  [[nodiscard]] Name GetName() override;

  explicit PlaceShips(Game& game, const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_STATES_PLACE_SHIPS_H_
