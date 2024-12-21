
#ifndef SEABATTLE_SRC_CORE_GAME_H_
#define SEABATTLE_SRC_CORE_GAME_H_

#include <fstream>

#include "../input/command.h"
#include "../output/game_renderer.h"
#include "entities/players/bot_player.h"
#include "entities/players/human_player.h"
#include "states/setup_field.h"

namespace seabattle {

class Game {
  std::unique_ptr<states::State> state_;

  HumanPlayer human_player_;
  BotPlayer bot_player_;

  bool is_running_{true};

  output::GameRenderer& game_renderer_;

 public:
  explicit Game(output::GameRenderer& game_renderer);

  HumanPlayer& GetHumanPlayer();
  BotPlayer& GetBotPlayer();
  [[nodiscard]] bool IsRunning() const;

  void Save(const std::string& filename);
  void Load(const std::string& filename);

  void UpdateState(states::State* new_state);

  template <typename T>
  void Render(const T& object) {
    game_renderer_.Render(object);
  }

  template <typename T, typename S>
  void Render(const T& t, const S& s) {
    game_renderer_.Render(t, s);
  }

  void HandleCommand(input::Command command);
};

}  // namespace seabattle

#endif  // SEABATTLE_SRC_CORE_GAME_H_
