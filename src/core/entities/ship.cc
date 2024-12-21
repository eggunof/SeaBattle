
#include "ship.h"

#include <stdexcept>

namespace seabattle::entities {

void Ship::Segment::Hit(const uint8_t damage) {
  if (health_ < damage) {
    health_ = 0;
  } else {
    health_ -= damage;
  }
}

Ship::Segment::Segment(const uint8_t health) : health_(health) {}

Ship::Ship(const uint8_t length) : length_(length), segments_(length) {}

Ship::Segment &Ship::GetSegment(const uint8_t index) {
  if (index >= length_) {
    throw std::out_of_range("Segment index out of range");
  }
  return segments_[index];
}

uint8_t Ship::GetLength() const { return length_; }

bool Ship::IsSunk() const {
  return std::ranges::all_of(
      segments_.begin(), segments_.end(),
      [](const Segment &segment) { return segment.IsSunk(); });
}

Ship::Ship(const json &j) {
  length_ = j["length"];
  segments_.reserve(length_);
  for (const auto &health : j["segments"]) {
    segments_.emplace_back(health);
  }
}

Ship::operator json() const {
  json j;
  j["length"] = length_;
  j["segments"] = json::array();
  for (const auto &segment : segments_) {
    j["segments"].emplace_back(segment.GetHealth());
  }
  return j;
}

}  // namespace seabattle::entities