
#ifndef SEABATTLE_SRC_INPUT_GAME_CONTROLLER_H_
#define SEABATTLE_SRC_INPUT_GAME_CONTROLLER_H_

#include <concepts>

#include "../core/game.h"
#include "command.h"

namespace seabattle::input {

template <typename T>
concept HasParseMethod = requires(T t) {
  { t.Parse() } -> std::same_as<Command>;
};

template <HasParseMethod CommandParser>
class GameController {
  Game& game_;
  CommandParser parser_;

 public:
  GameController(Game& game, const CommandParser& parser)
      : game_(game), parser_(parser) {}
  explicit GameController(Game& game) : game_(game) {}

  void HandleInput() {
    auto command = parser_.Parse();
    game_.HandleCommand(command);
  }
};

}  // namespace seabattle::input

#endif  // SEABATTLE_SRC_INPUT_GAME_CONTROLLER_H_
