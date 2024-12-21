
#include "core/game.h"
#include "core/registries/state_registry.h"
#include "input/cli/console_parser.h"
#include "input/game_controller.h"
#include "output/cli/console_renderer.h"

using namespace seabattle;

int main() {
  abilities::AbilityRegistry::RegisterAbilities();
  states::StateRegistry::RegisterStates();

  output::ConsoleRenderer renderer;
  Game game(renderer);
  const input::ConsoleParser parser("key_bindings.json");
  input::GameController controller(game, parser);

  while (game.IsRunning()) {
    controller.HandleInput();
  }

  return 0;
}
