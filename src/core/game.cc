
#include "game.h"

#include "registries/state_registry.h"
#include "states/setup_field.h"
#include "states/state.h"

namespace seabattle {

Game::Game(output::GameRenderer& game_renderer)
    : game_renderer_(game_renderer) {
  UpdateState(new states::SetupField(*this));
}

HumanPlayer& Game::GetHumanPlayer() { return human_player_; }

BotPlayer& Game::GetBotPlayer() { return bot_player_; }

bool Game::IsRunning() const { return is_running_; }

void Game::Save(const std::string& filename) {
  std::ofstream save_file(filename);
  if (!save_file.is_open()) {
    Render("Error opening file");
    return;
  }

  json j;
  j["human_player"] = json(human_player_);
  j["bot_player"] = json(bot_player_);
  j["state_name"] = state_->GetName();
  j["state"] = json(*state_);

  save_file << j.dump(4);
  Render("Game saved");
}

void Game::Load(const std::string& filename) {
  try {
    std::ifstream load_file(filename);
    if (!load_file.is_open()) {
      Render("Error opening file");
      return;
    }
    auto j = json::parse(load_file);

    const auto& state_registry = states::StateRegistry::GetInstance();
    states::State::Name new_state_name = j["state_name"];
    if (!state_registry.Contains(new_state_name)) {
      throw std::runtime_error("Invalid state name");
    }

    human_player_ = HumanPlayer(j["human_player"]);
    bot_player_ = BotPlayer(j["bot_player"]);
    Render("Game loaded");
    auto new_state = state_registry.Create(new_state_name, *this, j["state"]);
    UpdateState(new_state.release());
  } catch (const std::runtime_error& e) {
    Render(e);
  }
}

void Game::UpdateState(states::State* new_state) { state_.reset(new_state); }

void Game::HandleCommand(const input::Command command) {
  switch (command) {
    case input::Command::INVALID:
      Render("Invalid command");
      break;
    case input::Command::QUIT:
      is_running_ = false;
      break;
    case input::Command::SAVE:
      Save("game_save.json");
      break;
    case input::Command::LOAD:
      Load("game_save.json");
      break;
    default:
      state_->HandleCommand(command);
  }
}

}  // namespace seabattle