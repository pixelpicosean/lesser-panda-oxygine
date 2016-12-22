#include "Gfx.hpp"

namespace lp {

  Gfx::Gfx() {
    this->root = this->layers["root"] = new oxygine::Actor();
  }

  Gfx::~Gfx() {
    this->root = nullptr;

    for (auto i : this->layers) {
      i.second = nullptr;
    }
    this->layers.clear();
  }

  Gfx& Gfx::createLayer(std::string name, std::string parent) {
    if (this->layers.find(name) == this->layers.end()) {
      auto layer = new oxygine::Actor();
      this->layers[name] = layer;

      auto p = this->layers[parent];
      if (p) {
        p->addChild(layer);
      }
    }

    return *this;
  }

  void Gfx::awake() {
    oxygine::getStage()->addChild(this->root);
  }

  void Gfx::freeze() {
    oxygine::getStage()->removeChild(this->root);
  }

  void Gfx::onEntitySpawn(lp::Entity *ent) {
    auto layer = (ent->layer.size() > 0) ? ent->layer : "root";
    if (ent->gfx) {
      auto p = this->layers.find(layer);
      if (p != this->layers.end()) {
        p->second->addChild(ent->gfx);
      }
      else {
        // TODO: assert layer not found
      }
    }
  }

  void Gfx::onEntityRemove(lp::Entity *ent) {
    if (ent->gfx) {
      ent->gfx->detach();
    }
  }

}
