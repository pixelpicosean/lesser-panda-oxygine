#pragma once

#include "oxygine-framework.h"
#include "Types.h"

#include <string>

namespace lp {

  class Entity {
    public:
      std::string name = "";

      bool isRemoved = false;
      bool canEverTick = false;

      oxygine::spActor gfx = nullptr;
      std::string layer = "root";

      Entity(float x, float y);

    private:
      int64 id;

      static int64 nextId;
  };

}
