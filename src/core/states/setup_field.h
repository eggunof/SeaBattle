
#ifndef SEABATTLE_SRC_CORE_STATES_SETUP_FIELD_H_
#define SEABATTLE_SRC_CORE_STATES_SETUP_FIELD_H_

#include "../entities/game_field.h"
#include "state.h"

namespace seabattle::states {

class SetupField : public State {
  Coordinates current_field_size_;

  void Render() const;

 public:
  explicit SetupField(Game& game,
                      const Coordinates&
                      current_field_size_ = {5, 5});

  void HandleCommand(input::Command command) override;

  static constexpr Name kName = "SetupField";
  [[nodiscard]] Name GetName() override;

  explicit SetupField(Game& game, const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_STATES_SETUP_FIELD_H_
