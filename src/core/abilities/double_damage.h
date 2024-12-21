
#ifndef SEABATTLE_SRC_CORE_ABILITIES_DOUBLE_DAMAGE_H_
#define SEABATTLE_SRC_CORE_ABILITIES_DOUBLE_DAMAGE_H_

#include "../entities/players/player.h"
#include "ability.h"

namespace seabattle::abilities {

class DoubleDamage : public Ability {
  bool& is_double_damage_activated_;

 public:
  DoubleDamage(entities::players::Player& user,
               entities::players::Player&)
      : is_double_damage_activated_(user.IsDoubleDamageActivated()) {}
  void Apply() override;

  static constexpr Name kName = "DoubleDamage";

  void RenderBy(output::GameRenderer& renderer) const override;
};

}  // namespace seabattle::abilities

#endif  // SEABATTLE_SRC_CORE_ABILITIES_DOUBLE_DAMAGE_H_
