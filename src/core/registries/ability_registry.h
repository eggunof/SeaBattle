
#ifndef SEABATTLE_SRC_CORE_REGISTRIES_ABILITY_REGISTRY_H_
#define SEABATTLE_SRC_CORE_REGISTRIES_ABILITY_REGISTRY_H_

#include <string>

#include "../abilities/ability.h"
#include "../entities/players/player.h"
#include "registry.h"

using namespace seabattle::entities::players;

namespace seabattle::abilities {

class AbilityRegistry
    : public Registry<Ability::Name, Ability, Player&, Player&> {
 public:
  static AbilityRegistry& GetInstance();
  static void RegisterAbilities();
};

}  // namespace seabattle::abilities

#endif  // SEABATTLE_SRC_CORE_REGISTRIES_ABILITY_REGISTRY_H_
