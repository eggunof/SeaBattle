
#ifndef SEABATTLE_SRC_INPUT_CLI_CONSOLE_PARSER_H_
#define SEABATTLE_SRC_INPUT_CLI_CONSOLE_PARSER_H_

#include "../command.h"
#include "../controls.h"

namespace seabattle::input {

class ConsoleParser {
  Controls controls_;

 public:
  ConsoleParser() = default;
  explicit ConsoleParser(const std::string& filename);
  explicit ConsoleParser(Controls controls);
  [[nodiscard]] Command Parse() const;
};

}  // namespace seabattle::input

#endif  // SEABATTLE_SRC_INPUT_CLI_CONSOLE_PARSER_H_
