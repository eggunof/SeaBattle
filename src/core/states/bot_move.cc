
#include "bot_move.h"

#include "../game.h"
#include "player_move.h"
#include "setup_bot.h"

namespace seabattle::states {

BotMove::BotMove(Game& game, const bool did_make_move)
    : State(game),
      human_player_(game_.GetHumanPlayer()),
      bot_player_(game_.GetBotPlayer()),
      did_make_move_(did_make_move) {
  game_.Render("Press any key to continue");
}

void BotMove::HandleCommand(input::Command command) {
  if (!did_make_move_) {
    MakeMove();
    did_make_move_ = true;
    if (human_player_.GetShipManager().IsAllShipsSunk()) {
      game_.Render("You lose");
      game_.UpdateState(new SetupField(game_));
      return;
    }
    if (bot_player_.GetShipManager().IsAllShipsSunk()) {
      game_.Render("You win");
      game_.UpdateState(new SetupBot(game_));
      return;
    }
    game_.Render("Press any key to continue");
  } else {
    game_.UpdateState(new PlayerMove(game_));
  }
}

void BotMove::MakeMove() const {
  game_.Render("Bot is making move...");
  bot_player_.MoveCursor(human_player_.GetGameField());
  const auto attack_result = bot_player_.Attack(human_player_);
  Render();
  const auto a = bot_player_.CheckAttackResult(attack_result);

  game_.Render("Next strategy is ");
  switch (a) {
    case BotPlayer::Strategy::RANDOM:
      game_.Render("RANDOM");
      break;
    case BotPlayer::Strategy::FINISH_OFF:
      game_.Render("FINISH_OFF");
      break;
    case BotPlayer::Strategy::FIND_OUT_ORIENTATION:
      game_.Render("FIND_OUT_ORIENTATION");
      break;
    case BotPlayer::Strategy::REACH_EDGE:
      game_.Render("REACH_EDGE");
      break;
    case BotPlayer::Strategy::FINISH_LAST_SEGMENTS:
      game_.Render("FINISH_LAST_SEGMENTS");
      break;
  }
}

void BotMove::Render() const {
  game_.Render("Human field:");
  game_.Render(human_player_.GetGameField(), bot_player_.GetCursorPosition());
}

State::Name BotMove::GetName() { return kName; }

BotMove::BotMove(Game& game, const json& j)
    : BotMove(game, static_cast<bool>(j["did_make_move"])) {}

BotMove::operator json() const {
  json j;
  j["did_make_move"] = json(did_make_move_);
  return j;
}

}  // namespace seabattle::states
