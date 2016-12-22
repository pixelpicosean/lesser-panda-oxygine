#pragma once

#include "oxygine-framework.h"

#include "System.hpp"

#include <unordered_map>

namespace lp {

  class Gfx : public System<Gfx> {
    public:
      oxygine::spActor root = nullptr;

      std::unordered_map<std::string, oxygine::spActor> layers;

      Gfx();
      ~Gfx();

      Gfx& createLayer(std::string name, std::string parent = "root");

      void awake() override;
      void freeze() override;

      void onEntitySpawn(Entity* ent) override;
      void onEntityRemove(Entity* ent) override;
  };

}
