#include "Entity.h"

#include <utility>

namespace lp {

  int64 Entity::nextId = 0;
  std::unordered_map<std::string, Entity::Factory> Entity::entityTypes;

  void Entity::define(const std::string &type, const Factory& factory) {
    auto p = Entity::entityTypes.find(type);
    if (p == Entity::entityTypes.end()) {
      Entity::entityTypes.insert(std::make_pair(type, factory));
    }
  }

  Entity::Entity(float x, float y): id(nextId++) {}

}
