
#ifndef SEABATTLE_SRC_OUTPUT_GAME_RENDERER_H_
#define SEABATTLE_SRC_OUTPUT_GAME_RENDERER_H_

#include <string>

#include "../core/abilities/ability.h"
#include "../core/abilities/bombardment.h"
#include "../core/abilities/double_damage.h"
#include "../core/abilities/scanner.h"
#include "../core/entities/game_field.h"

namespace seabattle::output {

class GameRenderer {
 public:
  virtual ~GameRenderer() = default;

  virtual void Render(const std::string& string) = 0;
  virtual void Render(const std::exception& e) = 0;
  virtual void Render(const entities::GameField& field) = 0;
  virtual void Render(const entities::GameField& field, const Coordinates& cursor) = 0;
  virtual void Render(const entities::GameField& field, const Area& area) = 0;

  virtual void Render(const abilities::Ability& ability) = 0;
  virtual void Render(const abilities::Bombardment& ability) = 0;
  virtual void Render(const abilities::DoubleDamage& ability) = 0;
  virtual void Render(const abilities::Scanner& ability) = 0;
};

}  // namespace seabattle::output

#endif  // SEABATTLE_SRC_OUTPUT_GAME_RENDERER_H_
