
#ifndef SEABATTLE_SRC_ERRORS_ABILITY_NOT_REGISTERED_ERROR_H_
#define SEABATTLE_SRC_ERRORS_ABILITY_NOT_REGISTERED_ERROR_H_

#include "../core/abilities/ability.h"
#include "game_error.h"

namespace seabattle::errors {

class AbilityNotRegisteredError : public GameError {
  const abilities::Ability::Name ability_name_;

 public:
  explicit AbilityNotRegisteredError(
      const abilities::Ability::Name& ability_name)
      : GameError("The ability \"" + ability_name + "\" is not registered"),
        ability_name_(ability_name) {}

  [[nodiscard]] const abilities::Ability::Name& GetAbilityName() const {
    return ability_name_;
  }
};

}  // namespace seabattle::errors

#endif  // SEABATTLE_SRC_ERRORS_ABILITY_NOT_REGISTERED_ERROR_H_
