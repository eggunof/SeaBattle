
#ifndef SEABATTLE_SRC_UTILS_RANDOM_GENERATOR_H_
#define SEABATTLE_SRC_UTILS_RANDOM_GENERATOR_H_

#include <algorithm>
#include <random>

namespace seabattle::utilities {

class RandomGenerator {
  std::mt19937 rng_;

 public:
  explicit RandomGenerator(unsigned long seed = std::random_device{}());

  template <typename T>
  T GetRandomInt(T min, T max) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(rng_);
  }

  template <typename T>
  T GetRandomInt(T max) {
    std::uniform_int_distribution<T> dist(0, max);
    return dist(rng_);
  }

  template <typename T>
  T GetRandomReal(T min, T max) {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(rng_);
  }

  template <typename T>
  void Shuffle(std::vector<T>& arr) {
    std::shuffle(arr.begin(), arr.end(), rng_);
  }

  template <typename T>
  const T& GetRandom(const std::vector<T>& arr) {
    std::uniform_int_distribution<size_t> dist(0, arr.size() - 1);
    return arr[dist(rng_)];
  }

  template <typename T>
  T& GetRandom(std::vector<T>& arr) {
    std::uniform_int_distribution<size_t> dist(0, arr.size() - 1);
    return arr[dist(rng_)];
  }
};

}  // namespace seabattle::utilities

#endif  // SEABATTLE_SRC_UTILS_RANDOM_GENERATOR_H_
