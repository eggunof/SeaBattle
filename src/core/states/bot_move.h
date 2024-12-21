
#ifndef SEABATTLE_SRC_CORE_STATES_BOT_MOVE_H_
#define SEABATTLE_SRC_CORE_STATES_BOT_MOVE_H_

#include "../entities/players/bot_player.h"
#include "../entities/players/human_player.h"
#include "state.h"

namespace seabattle::states {

class BotMove : public State {
  HumanPlayer& human_player_;
  BotPlayer& bot_player_;

  bool did_make_move_{false};

  void MakeMove() const;
  void Render() const;

 public:
  explicit BotMove(Game& game, bool did_make_move = false);
  void HandleCommand(input::Command command) override;

  static constexpr Name kName = "BotMove";
  [[nodiscard]] Name GetName() override;

  explicit BotMove(Game& game, const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_STATES_BOT_MOVE_H_
