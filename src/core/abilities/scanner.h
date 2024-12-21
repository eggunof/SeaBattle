
#ifndef SEABATTLE_SRC_CORE_ABILITIES_SCANNER_H_
#define SEABATTLE_SRC_CORE_ABILITIES_SCANNER_H_

#include "../entities/game_field.h"
#include "../entities/players/player.h"
#include "ability.h"

namespace seabattle::abilities {

class Scanner : public Ability {
  const entities::GameField& target_game_field_;
  const Coordinates& start_coordinates_;
  bool is_found_{false};

 public:
  Scanner(entities::players::Player& user, entities::players::Player& target)
      : target_game_field_(target.GetGameField()),
        start_coordinates_{user.GetCursorPosition()} {}
  void Apply() override;

  static constexpr Name kName = "Scanner";

  [[nodiscard]] bool IsFound() const;

  static constexpr Coordinates kScannerRange{2, 2};

  void RenderBy(output::GameRenderer& renderer) const override;
};

}  // namespace seabattle::abilities

#endif  // SEABATTLE_SRC_CORE_ABILITIES_SCANNER_H_
