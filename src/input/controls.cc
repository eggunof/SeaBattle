
#include "controls.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace seabattle::input {

const std::map<char, Command> Controls::defaults_ = {
    {'w', Command::UP},    {'s', Command::DOWN},    {'a', Command::LEFT},
    {'d', Command::RIGHT}, {'e', Command::PRIMARY}, {'r', Command::SECONDARY},
    {'>', Command::SAVE},  {'<', Command::LOAD},    {'q', Command::QUIT},
};

const std::map<std::string, Command> Controls::string_to_command_ = {
    {"up", Command::UP},           {"down", Command::DOWN},
    {"left", Command::LEFT},       {"right", Command::RIGHT},
    {"primary", Command::PRIMARY}, {"secondary", Command::SECONDARY},
    {"save", Command::SAVE},       {"load", Command::LOAD},
    {"quit", Command::QUIT},
};

Controls::Controls() : key_to_command_(defaults_) {}

Controls::Controls(const std::string& filename) {
  try {
    ReadKeyBindings(filename);
  } catch (const std::exception&) {
    key_to_command_ = defaults_;
  }
}

Command Controls::GetCommand(const char key) const {
  const auto it = key_to_command_.find(key);
  if (it == key_to_command_.end()) {
    return Command::INVALID;
  }
  return it->second;
}

void Controls::ReadKeyBindings(const std::string& filename) {
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }

  auto j = json::parse(input_file);
  std::map<Command, char> command_to_key;

  for (const auto& [command_json, key_json] : j.items()) {
    auto it = string_to_command_.find(command_json);
    if (it == string_to_command_.end()) {
      throw std::runtime_error("Unknown command: " + command_json);
    }
    auto command = it->second;

    auto key_str = static_cast<std::string>(key_json);
    if (key_str.size() != 1) {
      throw std::runtime_error("Invalid key: " + key_str);
    }

    auto key = key_str[0];
    if (key_to_command_.contains(key)) {
      throw std::runtime_error("Key " + key_str + " already bound");
    }
    if (command_to_key.contains(command)) {
      throw std::runtime_error("Command " + command_json + " already bound");
    }
    key_to_command_[key] = command;
    command_to_key[command] = key;
  }
}

}  // namespace seabattle::input