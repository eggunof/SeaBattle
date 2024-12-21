
#ifndef SEABATTLE_SRC_ERRORS_INVALID_COORDINATES_ERROR_H_
#define SEABATTLE_SRC_ERRORS_INVALID_COORDINATES_ERROR_H_

#include "game_error.h"

namespace seabattle::errors {

class InvalidCoordinatesError : public GameError {
 public:
  explicit InvalidCoordinatesError()
      : GameError("Invalid coordinates provided") {}
};

}  // namespace seabattle::errors

#endif  // SEABATTLE_SRC_ERRORS_INVALID_COORDINATES_ERROR_H_
