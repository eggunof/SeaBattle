
#ifndef SEABATTLE_SRC_CORE_STATES_STATE_H_
#define SEABATTLE_SRC_CORE_STATES_STATE_H_

#include <nlohmann/json.hpp>

#include "../../input/command.h"

using json = nlohmann::json;

namespace seabattle {

class Game;

}  // namespace seabattle

namespace seabattle::states {

class State {
 public:
  using Name = std::string;

 protected:
  Game& game_;

 public:
  explicit State(Game& game);
  virtual ~State() = default;
  virtual void HandleCommand(input::Command command) = 0;

  virtual explicit operator json() const = 0;

  [[nodiscard]] virtual Name GetName()  = 0;
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_STATES_STATE_H_
