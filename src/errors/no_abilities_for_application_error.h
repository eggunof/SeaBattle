
#ifndef SEABATTLE_SRC_ERRORS_NO_ABILITIES_FOR_APPLICATION_ERROR_H_
#define SEABATTLE_SRC_ERRORS_NO_ABILITIES_FOR_APPLICATION_ERROR_H_

#include "game_error.h"

namespace seabattle::errors {

class NoAbilitiesForApplicationError : public GameError {
 public:
  NoAbilitiesForApplicationError()
      : GameError("No abilities available for application") {}
};

}  // namespace seabattle::errors

#endif  // SEABATTLE_SRC_ERRORS_NO_ABILITIES_FOR_APPLICATION_ERROR_H_
