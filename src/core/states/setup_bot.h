
#ifndef SEABATTLE_SRC_CORE_STATES_SETUP_BOT_H_
#define SEABATTLE_SRC_CORE_STATES_SETUP_BOT_H_

#include "../entities/game_field.h"
#include "state.h"

namespace seabattle::states {

class SetupBot : public State {
 public:
  explicit SetupBot(Game& game);
  void HandleCommand(input::Command command) override;

  static constexpr Name kName = "SetupBot";
  [[nodiscard]] Name GetName() override;

  explicit SetupBot(Game& game, const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_STATES_SETUP_BOT_H_
