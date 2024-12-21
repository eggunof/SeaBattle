
#ifndef SEABATTLE_SRC_CORE_ABILITIES_BOMBARDMENT_H_
#define SEABATTLE_SRC_CORE_ABILITIES_BOMBARDMENT_H_

#include "../../utilities/random_generator.h"
#include "../entities/players/player.h"
#include "../managers/ship_manager.h"
#include "ability.h"

namespace seabattle::abilities {

class Bombardment : public Ability {
  bool& is_double_damage_activated_;
  entities::ShipManager& target_ship_manager_;
  inline static utilities::RandomGenerator rng_{};

 public:
  Bombardment(entities::players::Player& user,
              entities::players::Player& target)
      : is_double_damage_activated_(user.IsDoubleDamageActivated()),
        target_ship_manager_(target.GetShipManager()) {}
  void Apply() override;

  static constexpr Name kName = "Bombardment";

  void RenderBy(output::GameRenderer& renderer) const override;
};

}  // namespace seabattle::abilities

#endif  // SEABATTLE_SRC_CORE_ABILITIES_BOMBARDMENT_H_
