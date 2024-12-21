
#include "console_parser.h"

#include <iostream>
#include <utility>

namespace seabattle::input {

ConsoleParser::ConsoleParser(const std::string& filename)
    : controls_(filename) {}

ConsoleParser::ConsoleParser(Controls controls)
    : controls_(std::move(controls)) {}

Command ConsoleParser::Parse() const {
  char c;
  while (std::cin.peek() == '\n') std::cin.ignore();
  std::cin.get(c);
  if (std::cin.good()) {
    return controls_.GetCommand(c);
  }
  return Command::INVALID;
}

}  // namespace seabattle::input