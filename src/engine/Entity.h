#pragma once

#include "oxygine-framework.h"
#include "Types.h"

#include <string>
#include <unordered_map>
#include <functional>

namespace lp {

  class Game;
  class Entity {
    public:
      typedef std::function<Entity*(float, float)> Factory;
      static std::unordered_map<std::string, Factory> entityTypes;

      int64 id = -1;
      std::string name = "";

      bool isRemoved = false;
      bool canEverTick = false;

      Game* game;

      oxygine::spActor gfx = nullptr;
      std::string layer = "root";

      oxygine::Vector2 position;

      static void define(const std::string& type, const Factory& factory);

      Entity(float x, float y);

      void ready() {}

    private:
      static int64 nextId;
  };

}
