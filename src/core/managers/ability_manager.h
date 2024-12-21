
#ifndef SEABATTLE_SRC_CORE_ENTITIES_ABILITY_MANAGER_H_
#define SEABATTLE_SRC_CORE_ENTITIES_ABILITY_MANAGER_H_

#include <queue>

#include "../../utilities/random_generator.h"
#include "../abilities/ability.h"
#include "../registries/ability_registry.h"

namespace seabattle::abilities {

class AbilityManager {
  inline static const AbilityRegistry &registry_ =
      AbilityRegistry::GetInstance();
  std::queue<Ability::Name> abilities_;
  inline static utilities::RandomGenerator rng_{};

 public:
  AbilityManager();

  [[nodiscard]] size_t Size() const;
  [[nodiscard]] bool IsEmpty() const;

  void AddAbility(const Ability::Name &ability_name);
  void AddRandomAbility();
  [[nodiscard]] const Ability::Name &PeekAbility() const;
  void PopAbility();

  explicit AbilityManager(const json &j);
  explicit operator json() const;
};

}  // namespace seabattle::abilities

#endif  // SEABATTLE_SRC_CORE_ENTITIES_ABILITY_MANAGER_H_
