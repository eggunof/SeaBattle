
#include "player.h"

#include "../../values/coordinates.h"

namespace seabattle::entities::players {

GameField& Player::GetGameField() { return game_field_; }

ShipManager& Player::GetShipManager() { return ship_manager_; }

bool& Player::IsDoubleDamageActivated() { return is_double_damage_activated; }

Coordinates& Player::GetCursorPosition() { return cursor_position; }

GameField::AttackResult Player::Attack(Player& target) {
  const auto attack_result = target.game_field_.AttackCell(
      cursor_position, is_double_damage_activated ? 2 : 1);
  is_double_damage_activated = false;

  return attack_result;
}

Player::Player(const json& j)
    : ship_manager_(j["ship_manager"]),
      game_field_(j["game_field"],
                  [&] {
                    std::unordered_map<uint16_t, Ship*> temp;
                    for (uint16_t i = 0; auto& ship : ship_manager_) {
                      temp[i++] = &ship;
                    }
                    return temp;
                  }()),
      is_double_damage_activated(j["is_double_damage_activated"]),
      cursor_position(j["cursor_position"]) {}

Player::operator json() const {
  json j;
  j["ship_manager"] = json(ship_manager_);
  std::unordered_map<const Ship*, uint16_t> ships_ids;
  for (uint16_t i = 0; const auto& ship : ship_manager_) {
    ships_ids[&ship] = i++;
  }
  j["game_field"] = game_field_.ToJson(ships_ids);
  j["is_double_damage_activated"] = is_double_damage_activated;
  j["cursor_position"] = json(cursor_position);
  return j;
}

}  // namespace seabattle::entities::players