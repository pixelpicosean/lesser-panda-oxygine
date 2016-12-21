#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.h"
#include "System.h"

namespace lp {

  class Game {
    public:
      int desiredFPS = 60;

      System* sys(const char* name);

      Game() {}
      virtual ~Game() {}

      virtual void awake();
      virtual void update(float dt, float sec);
      virtual void render(float dt, float sec);
      virtual void freeze();

      Game& addSystem(System* sys);

      void run(int timestamp);

    protected:
      std::vector<System*> systems;
      std::map<std::string, System*> namedSystems;

      std::vector<Entity*> entities;
      std::map<std::string, Entity*> namedEntities;

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
  };

}
