
#include "bombardment.h"

#include "../../output/game_renderer.h"

namespace seabattle::abilities {

void Bombardment::Apply() {
  std::vector<std::reference_wrapper<entities::Ship::Segment>> active_segments;
  for (auto& ship : target_ship_manager_) {
    if (ship.IsSunk()) continue;
    for (uint8_t j = 0; j < ship.GetLength(); ++j) {
      if (auto& segment = ship.GetSegment(j); !segment.IsSunk()) {
        active_segments.emplace_back(segment);
      }
    }
  }
  const auto& random_segment = rng_.GetRandom(active_segments);
  if (!is_double_damage_activated_) {
    random_segment.get().Hit(1);
  } else {
    random_segment.get().Hit(2);
    is_double_damage_activated_ = false;
  }
}

void Bombardment::RenderBy(output::GameRenderer& renderer) const {
  renderer.Render(*this);
}

}  // namespace seabattle::abilities
