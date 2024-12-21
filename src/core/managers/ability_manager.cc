
#include "ability_manager.h"

#include "../../errors/ability_not_registered_error.h"
#include "../../errors/no_abilities_for_application_error.h"

namespace seabattle::abilities {

AbilityManager::AbilityManager() {
  auto& registry = AbilityRegistry::GetInstance();
  std::vector<Ability::Name> ability_names;
  for (const auto& ability_name : registry | std::views::keys)
    ability_names.push_back(ability_name);
  rng_.Shuffle(ability_names);
  for (const auto& name : ability_names) {
    abilities_.push(name);
  }
}

void AbilityManager::AddAbility(const Ability::Name& ability_name) {
  if (!registry_.Contains(ability_name)) {
    throw errors::AbilityNotRegisteredError(ability_name);
  }
  abilities_.push(ability_name);
}

void AbilityManager::AddRandomAbility() {
  auto& registry = AbilityRegistry::GetInstance();
  auto it = registry.begin();
  std::advance(it, rng_.GetRandomInt(registry.Size() - 1));
  abilities_.push(it->first);
}

const Ability::Name& AbilityManager::PeekAbility() const {
  if (IsEmpty()) {
    throw errors::NoAbilitiesForApplicationError();
  }
  return abilities_.front();
}

void AbilityManager::PopAbility() {
  if (IsEmpty()) {
    throw errors::NoAbilitiesForApplicationError();
  }
  abilities_.pop();
}

size_t AbilityManager::Size() const { return abilities_.size(); }

bool AbilityManager::IsEmpty() const { return abilities_.empty(); }

AbilityManager::AbilityManager(const json& j) {
  for (const auto& ability_json : std::ranges::reverse_view(j["abilities"])) {
    AddAbility(ability_json);
  }
}

AbilityManager::operator json() const {
  json j;
  j["abilities"] = json::array();
  auto abilities_copy(abilities_);
  while (!abilities_copy.empty()) {
    j["abilities"].push_back(abilities_copy.front());
    abilities_copy.pop();
  }
  return j;
}

}  // namespace seabattle::abilities