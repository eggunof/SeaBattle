
#include "setup_bot.h"

#include "../../errors/cannot_place_bot_ships_error.h"
#include "../game.h"
#include "player_move.h"

namespace seabattle::states {

SetupBot::SetupBot(Game& game) : State(game) {
  game_.Render("Setting up bot's ships");
  game.GetBotPlayer().GetGameField() =
      entities::GameField(game.GetHumanPlayer().GetGameField().GetDimensions());
  game.GetBotPlayer().GetShipManager() =
      entities::ShipManager(game.GetHumanPlayer().GetShipManager());
  try {
    game_.GetBotPlayer().GenerateShipsPlacement();
    game_.Render("Bot's ships placed successfully, press any key to continue");
  } catch (const errors::CannotPlaceBotShipsError& e) {
    game_.Render(e);
    game_.Render("Trying again...");
    game_.UpdateState(new SetupBot(game_));
  }
}

void SetupBot::HandleCommand(input::Command command) {
  game_.UpdateState(new PlayerMove(game_));
}

State::Name SetupBot::GetName() { return kName; }

SetupBot::SetupBot(Game& game, const json&) : SetupBot(game) {}

SetupBot::operator json() const { return {}; }

}  // namespace seabattle::states
