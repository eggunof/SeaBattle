
#include "ability_registry.h"

#include "../abilities/bombardment.h"
#include "../abilities/double_damage.h"
#include "../abilities/scanner.h"

namespace seabattle::abilities {

AbilityRegistry& AbilityRegistry::GetInstance() {
  static AbilityRegistry instance;
  return instance;
}

void AbilityRegistry::RegisterAbilities() {
  auto& registry = GetInstance();
  registry.Add(DoubleDamage::kName, [](Player& user, Player& target) {
    return std::make_unique<DoubleDamage>(user, target);
  });
  registry.Add(Bombardment::kName, [](Player& user, Player& target) {
    return std::make_unique<Bombardment>(user, target);
  });
  registry.Add(Scanner::kName, [](Player& user, Player& target) {
    return std::make_unique<Scanner>(user, target);
  });
}

}  // namespace seabattle::abilities
