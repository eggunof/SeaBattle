
#include "human_player.h"

#include "player.h"

namespace seabattle::entities::players {

GameField::AttackResult HumanPlayer::Attack(Player& target) {
  const auto attack_result = Player::Attack(target);
  if (attack_result == GameField::AttackResult::SHIP_DESTROYED) {
    ability_manager_.AddRandomAbility();
  }

  return attack_result;
}

std::unique_ptr<abilities::Ability> HumanPlayer::ApplyAbility(Player& target) {
  const auto ability_name = ability_manager_.PeekAbility();
  ability_manager_.PopAbility();
  const auto& registry = abilities::AbilityRegistry::GetInstance();
  auto ability = registry.Create(ability_name, *this, target);
  ability->Apply();

  return std::move(ability);
}

abilities::AbilityManager& HumanPlayer::GetAbilityManager() {
  return ability_manager_;
}

HumanPlayer::HumanPlayer(const json& j)
    : Player(j), ability_manager_(j["ability_manager"]) {}

HumanPlayer::operator json() const {
  json j = Player::operator json();
  j["ability_manager"] = json(ability_manager_);
  return j;
}

}  // namespace seabattle::entities::players