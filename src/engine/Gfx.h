#pragma once

#include "System.h"
#include "oxygine-framework.h"

#include <unordered_map>

namespace lp {

  class Gfx : public System<Gfx> {
    public:
      oxygine::spActor root = nullptr;

      std::unordered_map<std::string, oxygine::spActor> layers;

      Gfx() {
        this->root = this->layers["root"] = new oxygine::Actor();
      }
      ~Gfx() {
        this->root = nullptr;

        for (auto i : this->layers) {
          i.second = nullptr;
        }
        this->layers.clear();
      }

      Gfx& createLayer(std::string name, std::string parent = "root") {
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

      void awake() override {
        oxygine::getStage()->addChild(this->root);
      }
      void freeze() override {
        oxygine::getStage()->removeChild(this->root);
      }

      void onEntitySpawn(Entity* ent) override {}
      void onEntityRemove(Entity* ent) override {}
  };

}
