
#ifndef SEABATTLE_SRC_CORE_REGISTRIES_STATE_REGISTRY_H_
#define SEABATTLE_SRC_CORE_REGISTRIES_STATE_REGISTRY_H_

#include <nlohmann/json.hpp>

#include "../states/state.h"
#include "registry.h"

using json = nlohmann::json;

namespace seabattle::states {

class StateRegistry : public Registry<State::Name, State, Game&, json&> {
 public:
  static StateRegistry& GetInstance();
  static void RegisterStates();
};

}  // namespace seabattle::states

#endif  // SEABATTLE_SRC_CORE_REGISTRIES_STATE_REGISTRY_H_
