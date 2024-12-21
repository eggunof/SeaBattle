
#ifndef SEABATTLE_SRC_OUTPUT_CLI_CONSOLE_RENDERER_H_
#define SEABATTLE_SRC_OUTPUT_CLI_CONSOLE_RENDERER_H_

#include <string>

#include "../game_renderer.h"

namespace seabattle::output {

class ConsoleRenderer : public GameRenderer {
 public:
  void Render(const std::string& string) override;
  void Render(const std::exception& e) override;
  void Render(const entities::GameField& field) override;
  void Render(const entities::GameField& field, const Coordinates& cursor) override;
  void Render(const entities::GameField& field, const Area& area) override;

  void Render(const abilities::Ability& ability) override;
  void Render(const abilities::Bombardment& ability) override;
  void Render(const abilities::DoubleDamage& ability) override;
  void Render(const abilities::Scanner& ability) override;
};

}  // namespace seabattle::output

#endif  // SEABATTLE_SRC_OUTPUT_CLI_CONSOLE_RENDERER_H_
