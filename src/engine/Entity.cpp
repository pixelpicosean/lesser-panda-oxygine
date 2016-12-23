#include "Entity.hpp"
#include "Game.hpp"

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

  Entity::Entity(float x, float y): id(nextId++), position(x, y) {}

  Entity::~Entity() {
    if (this->gfx) {
      this->gfx = nullptr;
    }
  }

  void Entity::ready() {
    if (this->gfx) {
      this->gfx->setPosition(this->position);
    }
  }

  void Entity::remove() {
    if (this->game) {
      this->game->removeEntity(this);
    }
  }

}
