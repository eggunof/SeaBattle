
#ifndef SEABATTLE_SRC_CORE_REGISTRIES_REGISTRY_H_
#define SEABATTLE_SRC_CORE_REGISTRIES_REGISTRY_H_

#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

namespace seabattle {

template <typename K, typename V, class... Args>
class Registry {
 public:
  using Factory = std::function<std::unique_ptr<V>(Args...)>;
  using Map = std::unordered_map<K, Factory>;

 protected:
  Registry() = default;

  Map entries_;

 public:
  Registry(const Registry&) = delete;
  Registry& operator=(const Registry&) = delete;

  static Registry& GetInstance() {
    static Registry instance;
    return instance;
  }

  void Add(const K& key, Factory&& factory) {
    entries_[key] = std::forward<Factory>(factory);
  }

  std::unique_ptr<V> Create(const K& key, Args&&... args) const {
    typename Map::const_iterator it = entries_.find(key);
    if (it != entries_.end()) {
      return it->second(std::forward<Args>(args)...);
    }
    return nullptr;
  }

  bool Contains(const K& key) const { return entries_.contains(key); }
  [[nodiscard]] size_t Size() const { return entries_.size(); }
  [[nodiscard]] bool IsEmpty() const { return entries_.empty(); }
  void Clear() { entries_.clear(); }

  typename Map::iterator begin() { return entries_.begin(); }
  typename Map::iterator end() { return entries_.end(); }
  typename Map::const_iterator begin() const { return entries_.cbegin(); }
  typename Map::const_iterator end() const { return entries_.cend(); }
};

}  // namespace seabattle

#endif  // SEABATTLE_SRC_CORE_REGISTRIES_REGISTRY_H_
