
#include "scanner.h"

#include "../../output/game_renderer.h"

namespace seabattle::abilities {

void Scanner::Apply() {
  const auto& field_area = target_game_field_.GetArea();
  const auto end_coordinates = start_coordinates_ + kScannerRange;
  for (int32_t y = start_coordinates_.y; y < end_coordinates.y; ++y) {
    for (int32_t x = start_coordinates_.x; x < end_coordinates.x; ++x) {
      Coordinates coordinates(x, y);
      if (!field_area.Contains(coordinates)) continue;
      if (target_game_field_.IsShip(coordinates)) {
        is_found_ = true;
        return;
      }
    }
  }
}

bool Scanner::IsFound() const { return is_found_; }

void Scanner::RenderBy(output::GameRenderer& renderer) const {
  renderer.Render(*this);
}

}  // namespace seabattle::abilities
