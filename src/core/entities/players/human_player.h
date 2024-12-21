
#ifndef SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_HUMAN_PLAYER_H_
#define SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_HUMAN_PLAYER_H_

#include "../../managers/ability_manager.h"
#include "player.h"

namespace seabattle::entities::players {

class HumanPlayer : public Player {
  abilities::AbilityManager ability_manager_;

 public:
  HumanPlayer() : Player() {}
  std::unique_ptr<abilities::Ability> ApplyAbility(Player& target);
  GameField::AttackResult Attack(Player& target) override;

  abilities::AbilityManager& GetAbilityManager();

  explicit HumanPlayer(const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::entities::players

#endif  // SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_HUMAN_PLAYER_H_
