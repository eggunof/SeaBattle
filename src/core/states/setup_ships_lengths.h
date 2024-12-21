
#ifndef SEABATTLE_SRC_CORE_STATES_SETUP_SHIPS_LENGTHS_H_
#define SEABATTLE_SRC_CORE_STATES_SETUP_SHIPS_LENGTHS_H_

#include <cstdint>

#include "../entities/players/human_player.h"
#include "../entities/ship.h"
#include "state.h"

namespace seabattle::states {

class SetupShipsLengths : public State {
  const uint32_t cells_;
  std::vector<uint8_t> ship_sizes_{entities::Ship::kMinShipLength};
  size_t selected_ship_index_{0};

  [[nodiscard]] uint32_t CountOccupiedCells() const;

  void Render() const;

 public:
  explicit SetupShipsLengths(Game& game,
      const std::vector<uint8_t>& ship_sizes =
                                 {entities::Ship::kMinShipLength},
                             size_t selected_ship_index = 0);
  void HandleCommand(input::Command command) override;

  static constexpr Name kName = "SetupLengths";
  [[nodiscard]] Name GetName() override;

  explicit SetupShipsLengths(Game& game, const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_STATES_SETUP_SHIPS_LENGTHS_H_
