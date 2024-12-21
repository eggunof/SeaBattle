
#ifndef SEABATTLE_SRC_CORE_ABILITIES_ABILITY_H_
#define SEABATTLE_SRC_CORE_ABILITIES_ABILITY_H_

#include <string>

namespace seabattle::output {

class GameRenderer;

}  // namespace seabattle::output

namespace seabattle::abilities {

class Ability {
 public:
  using Name = std::string;
  virtual ~Ability() = default;
  virtual void Apply() = 0;
  virtual void RenderBy(output::GameRenderer& renderer) const = 0;
};

}  // namespace seabattle::abilities

#endif  // SEABATTLE_SRC_CORE_ABILITIES_ABILITY_H_
