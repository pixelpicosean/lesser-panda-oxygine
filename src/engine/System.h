#pragma once

#include "Entity.h"

#include <string>

namespace lp {

  class System {
    public:
      std::string type;

      virtual void awake() {}
      virtual void update(float dt, float sec) {}
      virtual void render(float dt, float sec) {}
      virtual void freeze() {}

      virtual void onEntitySpawn(Entity* ent) {}
      virtual void onEntityRemove(Entity* ent) {}
  };

}
