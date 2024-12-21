
#ifndef SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_BOT_PLAYER_H_
#define SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_BOT_PLAYER_H_

#include <map>

#include "../../../utilities/random_generator.h"
#include "player.h"

namespace seabattle::entities::players {

class BotPlayer : public Player {
 public:
  enum class Strategy {
    RANDOM,
    FINISH_OFF,
    FIND_OUT_ORIENTATION,
    REACH_EDGE,
    FINISH_LAST_SEGMENTS
  };

 private:
  enum class Direction { UP, DOWN, LEFT, RIGHT };
  inline static const std::map<Direction, Coordinates> direction_map_ = {
      {Direction::UP, {0, -1}},
      {Direction::DOWN, {0, 1}},
      {Direction::LEFT, {-1, 0}},
      {Direction::RIGHT, {1, 0}}};

  Strategy strategy_{Strategy::RANDOM};
  std::pair<bool, Ship::Orientation> ship_orientation_{false,
                                                       Ship::Orientation()};
  std::vector<Direction> chosen_directions_;
  bool reached_ship_edge_{false};

  void InitializeBeforeNextShip();

  void MoveCursorRandom(const GameField& target_game_field);
  void MoveCursorFindOutOrientation(const GameField& target_game_field);
  void MoveCursorReachEdge(const GameField& target_game_field);
  void MoveCursorFinishLastSegments(const GameField& target_game_field);

  [[nodiscard]] std::vector<std::pair<Coordinates, Ship::Orientation>>
  GetAvailableShipPositions(uint8_t ship_length) const;

  inline static utilities::RandomGenerator rng_{};

 public:
  BotPlayer() : Player() {}

  void GenerateShipsPlacement();
  void MoveCursor(const GameField& target_game_field);
  Strategy CheckAttackResult(GameField::AttackResult attack_result);


  explicit BotPlayer(const json& j);
  explicit operator json() const override;
};

}  // namespace seabattle::entities::players

#endif  // SEABATTLE_SRC_CORE_ENTITIES_PLAYERS_BOT_PLAYER_H_
