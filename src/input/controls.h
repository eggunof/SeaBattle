
#ifndef SEABATTLE_SRC_INPUT_CONTROLS_H_
#define SEABATTLE_SRC_INPUT_CONTROLS_H_

#include <map>
#include <string>

#include "command.h"

namespace seabattle::input {

class Controls {
  static const std::map<char, Command> defaults_;
  static const std::map<std::string, Command> string_to_command_;
  std::map<char, Command> key_to_command_;

 public:
  Controls();
  explicit Controls(const std::string& filename);
  [[nodiscard]] Command GetCommand(char key) const;
  void ReadKeyBindings(const std::string& filename);
};

}  // namespace seabattle::input

#endif  // SEABATTLE_SRC_INPUT_CONTROLS_H_
