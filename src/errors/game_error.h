
#ifndef SEABATTLE_SRC_ERRORS_GAME_ERROR_H_
#define SEABATTLE_SRC_ERRORS_GAME_ERROR_H_

#include <stdexcept>

namespace seabattle::errors {

class GameError : public std::runtime_error {
 public:
  GameError() : std::runtime_error("Game error occurred") {}
  explicit GameError(const std::string &message)
      : std::runtime_error(message) {}
};

}  // namespace seabattle::errors

#endif  // SEABATTLE_SRC_ERRORS_GAME_ERROR_H_
