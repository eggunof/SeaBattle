
#ifndef SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_PLAYER_H_
#define SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_PLAYER_H_

#include "../../managers/ship_manager.h"
#include "../game_field.h"

namespace seabattle::entities::players {

class Player {
 protected:
  ShipManager ship_manager_;
  GameField game_field_;
  bool is_double_damage_activated{false};
  Coordinates cursor_position;

 public:
  Player() = default;
  Player(const Player& other) = default;
  Player(Player&& other) noexcept = default;
  Player& operator=(const Player& other) = default;
  Player& operator=(Player&& other) noexcept = default;
  virtual ~Player() = default;

  [[nodiscard]] GameField& GetGameField();
  [[nodiscard]] ShipManager& GetShipManager();
  [[nodiscard]] bool& IsDoubleDamageActivated();
  [[nodiscard]] Coordinates& GetCursorPosition();

  virtual GameField::AttackResult Attack(Player& target);

  explicit Player(const json& j);
  virtual explicit operator json() const;
};

}  // namespace seabattle::entities::players

#endif  // SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_PLAYER_H_
