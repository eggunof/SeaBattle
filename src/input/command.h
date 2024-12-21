
#ifndef SEABATTLE_SRC_INPUT_COMMAND_H_
#define SEABATTLE_SRC_INPUT_COMMAND_H_

namespace seabattle::input {

enum class Command {
  INVALID,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  PRIMARY,
  SECONDARY,
  SAVE,
  LOAD,
  QUIT,
  TOTAL_COMMANDS
};

}  // namespace seabattle::input

#endif  // SEABATTLE_SRC_INPUT_COMMAND_H_
