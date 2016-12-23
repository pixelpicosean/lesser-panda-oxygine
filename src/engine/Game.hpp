#pragma once

#include "core.hpp"
#include "Entity.hpp"
#include "System.hpp"
#include "Types.hpp"

#include <vector>
#include <string>
#include <unordered_map>

namespace lp {

  #define MakeGameFactory(gameClass) []() { return new gameClass(); }

  class Game : public SystemManager {
    public:
      int desiredFPS = 60;

      Game();
      virtual ~Game();

      template <typename T>
      T* spawnEntity(float x, float y, const std::string& layer = "root") {
        T* ent = new T(x, y);
        this->onEntitySpawn(ent, layer);
        return ent;
      }
      Entity* spawnEntity(const std::string& type, float x, float y, const std::string& layer = "root");

      void removeEntity(Entity* ent);
      void removeEntity(int64 entID);

      Entity* getEntityByName(const std::string& name);

      virtual void awake();
      virtual void update(float dt, float sec);
      virtual void render(float dt, float sec);
      virtual void freeze();

      void run(int timestamp);

    protected:
      std::unordered_map<int64, Entity*> entities;
      std::unordered_map<std::string, Entity*> namedEntities;

      struct UpdateInfo {
        int spiraling = 0;
        int last = -1;
        int realDelta = 0;
        int deltaTime = 0;
        int lastCount = 0;
        int count = 0;
        float step = 0.0f;
        float slowStep = 0.0f;
        float slowStepSec = 0.0f;
      };

      UpdateInfo updateInfo;

      void onEntitySpawn(Entity* ent, const std::string& layer);

    private:
      friend class engine;

      static uint64 nextType;
      static uint64 type() {
        static uint64 type = nextType++;
        return type;
      }
  };

}
