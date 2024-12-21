
#ifndef SEABATTLE_SRC_CORE_STATES_PLAYER_MOVE_H_
#define SEABATTLE_SRC_CORE_STATES_PLAYER_MOVE_H_

#include "../entities/players/bot_player.h"
#include "../entities/players/human_player.h"
#include "state.h"

namespace seabattle::states {

class PlayerMove : public State {
  HumanPlayer& human_player_;
  BotPlayer& bot_player_;

  void Attack() const;
  void UseAbility() const;
  void MoveCursor(input::Command command) const;

  void Render() const;

 public:
  explicit PlayerMove(Game& game);
  void HandleCommand(input::Command command) override;

  static constexpr Name kName = "PlayerMove";
  [[nodiscard]] Name GetName() override;

  explicit PlayerMove(Game& game, const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_STATES_PLAYER_MOVE_H_
