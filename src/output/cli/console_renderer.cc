
#include "console_renderer.h"

#include <iostream>

namespace seabattle::output {

void ConsoleRenderer::Render(const std::string& string) {
  std::cout << string << std::endl;
}

void ConsoleRenderer::Render(const std::exception& e) {
  std::cerr << "Error: " << e.what() << std::endl;
}

void ConsoleRenderer::Render(const entities::GameField& field) {
  static auto unknown = "?";
  static auto empty = "\033[37m~\033[0m";
  static auto destroyed_segment = "\033[90mX\033[0m";

  const auto &dimensions = field.GetDimensions();
  for (int32_t y = 0; y < dimensions.y; ++y) {
    for (int32_t x = 0; x < dimensions.x; ++x) {
      auto cell_state = field.GetCellState({x, y});
      std::string cell;
      switch (cell_state) {
        case entities::GameField::CellState::UNKNOWN:
          cell = unknown;
          break;
        case entities::GameField::CellState::EMPTY:
          cell = empty;
          break;
        case entities::GameField::CellState::SEGMENT_0HP:
          cell = destroyed_segment;
          break;
        default:
          const uint8_t health =
              static_cast<
                  std::underlying_type_t<entities::GameField::CellState>>(
                  cell_state) -
              static_cast<
                  std::underlying_type_t<entities::GameField::CellState>>(
                  entities::GameField::CellState::SEGMENT_0HP);
          cell = "\033[31;1m" + std::to_string(health) + "\033[0m";
          break;
      }
      std::cout << cell << " ";
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

void ConsoleRenderer::Render(const abilities::Ability& ability) {
  ability.RenderBy(*this);
}

void ConsoleRenderer::Render(const abilities::Bombardment& ability) {
  std::cout << "Bombardment ability activated" << std::endl;
}

void ConsoleRenderer::Render(const abilities::DoubleDamage& ability) {
  std::cout << "Double Damage ability activated" << std::endl;
}

void ConsoleRenderer::Render(const abilities::Scanner& ability) {
  if (ability.IsFound()) {
    std::cout << "Scanner ability found enemy ship" << std::endl;
  } else {
    std::cout << "Scanner ability did not detect the enemy ship" << std::endl;
  }
}

void ConsoleRenderer::Render(const entities::GameField& field,
                             const Coordinates& cursor) {
  static auto unknown = "?";
  static auto marked_unknown = "\033[4m?\033[0m";
  static auto empty = "\033[37m~\033[0m";
  static auto marked_empty = "\033[37;4m~\033[0m";
  static auto destroyed_segment = "\033[90mX\033[0m";
  static auto marked_destroyed_segment = "\033[90;4mX\033[0m";

  const auto dimensions = field.GetDimensions();
  for (int32_t y = 0; y < dimensions.y; ++y) {
    for (int32_t x = 0; x < dimensions.x; ++x) {
      Coordinates coordinates(x, y);
      const bool is_marked = coordinates == cursor;
      auto cell_state = field.GetCellState(coordinates);
      std::string cell;
      switch (cell_state) {
        case entities::GameField::CellState::UNKNOWN:
          cell = is_marked ? marked_unknown : unknown;
          break;
        case entities::GameField::CellState::EMPTY:
          cell = is_marked ? marked_empty : empty;
          break;
        case entities::GameField::CellState::SEGMENT_0HP:
          cell = is_marked ? marked_destroyed_segment : destroyed_segment;
          break;
        default:
          const uint8_t health =
              static_cast<
                  std::underlying_type_t<entities::GameField::CellState>>(
                  cell_state) -
              static_cast<
                  std::underlying_type_t<entities::GameField::CellState>>(
                  entities::GameField::CellState::SEGMENT_0HP);
          cell = is_marked ? "\033[31;1;4m" + std::to_string(health) + "\033[0m"
                           : "\033[31;1m" + std::to_string(health) + "\033[0m";
          break;
      }
      std::cout << cell << " ";
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

void ConsoleRenderer::Render(const entities::GameField& field,
                             const Area& area) {
  static auto marked_ship = "\033[35;1;4mX\033[0m";
  static auto marked_empty = "\033[34;1;4m#\033[0m";
  static auto unmarked_ship = "\033[31;1mX\033[0m";
  static auto unmarked_empty = "#";

  const auto dimensions = field.GetDimensions();
  for (int32_t y = 0; y < dimensions.y; ++y) {
    for (int32_t x = 0; x < dimensions.x; ++x) {
      Coordinates coordinates(x, y);
      const bool is_ship = field.IsShip(coordinates);
      const bool is_marked = area.Contains(coordinates);

      std::cout << (is_marked ? (is_ship ? marked_ship : marked_empty)
                              : is_ship ? unmarked_ship
                              : unmarked_empty)
                << " ";
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

}  // namespace seabattle::output