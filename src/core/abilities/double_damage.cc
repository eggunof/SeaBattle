
#include "double_damage.h"

#include "../../output/game_renderer.h"

namespace seabattle::abilities {

void DoubleDamage::Apply() { is_double_damage_activated_ = true; }

void DoubleDamage::RenderBy(output::GameRenderer& renderer) const {
  renderer.Render(*this);
}

}  // namespace seabattle::abilities
