
#ifndef SEABATTLE_SRC_ERRORS_CANNOT_PLACE_BOT_SHIPS_ERROR_H_
#define SEABATTLE_SRC_ERRORS_CANNOT_PLACE_BOT_SHIPS_ERROR_H_

#include "game_error.h"

namespace seabattle::errors {

class CannotPlaceBotShipsError : public GameError {
 public:
  CannotPlaceBotShipsError() : GameError("Can't place bot ships") {}
};

}  // namespace seabattle::errors

#endif  // SEABATTLE_SRC_ERRORS_CANNOT_PLACE_BOT_SHIPS_ERROR_H_
