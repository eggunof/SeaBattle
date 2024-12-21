
#ifndef SEABATTLE_SRC_ERRORS_IMPOSSIBLE_SHIP_POSITION_ERROR_H_
#define SEABATTLE_SRC_ERRORS_IMPOSSIBLE_SHIP_POSITION_ERROR_H_

#include "game_error.h"

namespace seabattle::errors {

class ImpossibleShipPositionError : public GameError {
 public:
  ImpossibleShipPositionError()
      : GameError("The ship cannot be placed in the specified position") {}
};

}  // namespace seabattle::errors

#endif  // SEABATTLE_SRC_ERRORS_IMPOSSIBLE_SHIP_POSITION_ERROR_H_
