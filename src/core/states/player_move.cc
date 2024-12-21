
#include "player_move.h"

#include "../../errors/game_error.h"
#include "../game.h"
#include "bot_move.h"
#include "setup_bot.h"

namespace seabattle::states {

PlayerMove::PlayerMove(Game& game)
    : State(game),
      human_player_(game_.GetHumanPlayer()),
      bot_player_(game_.GetBotPlayer()) {
  Render();
}

void PlayerMove::HandleCommand(const input::Command command) {
  try {
    switch (command) {
      case input::Command::PRIMARY:
        Attack();
        break;
      case input::Command::SECONDARY:
        UseAbility();
        break;
      default:
        MoveCursor(command);
        break;
    }
  } catch (errors::GameError& e) {
    game_.Render(e);
  }
}

void PlayerMove::Attack() const {
  if (const auto attack_result = human_player_.Attack(bot_player_);
      attack_result == entities::GameField::AttackResult::SHIP_DESTROYED) {
    game_.Render("Enemy ship destroyed, new ability: " +
                 human_player_.GetAbilityManager().PeekAbility());
  }
  Render();
  if (bot_player_.GetShipManager().IsAllShipsSunk()) {
    game_.Render("You win");
    game_.UpdateState(new SetupBot(game_));
  } else {
    game_.UpdateState(new BotMove(game_));
  }
}

void PlayerMove::UseAbility() const {
  const auto ability = human_player_.ApplyAbility(bot_player_);
  game_.Render(*ability);
  Render();
  if (bot_player_.GetShipManager().IsAllShipsSunk()) {
    game_.Render("You win");
    game_.UpdateState(new SetupBot(game_));
  }
}

void PlayerMove::MoveCursor(const input::Command command) const {
  switch (command) {
    case input::Command::UP:
      if (game_.GetHumanPlayer().GetCursorPosition().y > 0)
        --game_.GetHumanPlayer().GetCursorPosition().y;
      break;
    case input::Command::DOWN:
      if (game_.GetHumanPlayer().GetCursorPosition().y <
          game_.GetBotPlayer().GetGameField().GetDimensions().y - 1)
        ++game_.GetHumanPlayer().GetCursorPosition().y;
      break;
    case input::Command::LEFT:
      if (game_.GetHumanPlayer().GetCursorPosition().x > 0)
        --game_.GetHumanPlayer().GetCursorPosition().x;
      break;
    case input::Command::RIGHT:
      if (game_.GetHumanPlayer().GetCursorPosition().x <
          game_.GetBotPlayer().GetGameField().GetDimensions().x - 1)
        ++game_.GetHumanPlayer().GetCursorPosition().x;
      break;
    default:
      break;
  }
  Render();
}

void PlayerMove::Render() const {
  game_.Render("Bot field:");
  game_.Render(bot_player_.GetGameField(), human_player_.GetCursorPosition());
}

State::Name PlayerMove::GetName() { return kName; }

PlayerMove::PlayerMove(Game& game, const json&) : PlayerMove(game) {}

PlayerMove::operator json() const { return {}; }

}  // namespace seabattle::states