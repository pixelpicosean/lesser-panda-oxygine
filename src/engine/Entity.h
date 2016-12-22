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

      static void define(const std::string& type, const Factory& factory);

      Entity(float x, float y);
      virtual ~Entity();

      void setPosition(float x, float y) {
        this->position.set(x, y);
        if (this->gfx) {
          this->gfx->setPosition(this->position);
        }
      }
      oxygine::Vector2 getPosition(float x, float y) {
        return this->position;
      }

      virtual void ready();
      virtual void update(float dt, float sec) {}
      virtual void render(float dt, float sec) {}
      virtual void remove();

    protected:
      oxygine::Vector2 position = { 0.0f, 0.0f };

    private:
      static int64 nextId;
  };

}
