
#include "state_registry.h"

#include <memory>

#include "../states/bot_move.h"
#include "../states/place_ships.h"
#include "../states/player_move.h"
#include "../states/setup_bot.h"
#include "../states/setup_field.h"
#include "../states/setup_ships_lengths.h"

namespace seabattle::states {

StateRegistry& StateRegistry::GetInstance() {
  static StateRegistry instance;
  return instance;
}

void StateRegistry::RegisterStates() {
  auto& registry = GetInstance();

  registry.Add(SetupField::kName, [](Game& game, json& j) {
    return std::make_unique<SetupField>(game, j);
  });
  registry.Add(SetupShipsLengths::kName, [](Game& game, json& j) {
    return std::make_unique<SetupShipsLengths>(game, j);
  });
  registry.Add(PlaceShips::kName, [](Game& game, json& j) {
    return std::make_unique<PlaceShips>(game, j);
  });
  registry.Add(SetupBot::kName, [](Game& game, json& j) {
    return std::make_unique<SetupBot>(game, j);
  });
  registry.Add(PlayerMove::kName, [](Game& game, json& j) {
    return std::make_unique<PlayerMove>(game, j);
  });
  registry.Add(BotMove::kName, [](Game& game, json& j) {
    return std::make_unique<BotMove>(game, j);
  });
}

}  // namespace seabattle::states