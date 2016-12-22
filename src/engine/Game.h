#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "Entity.h"
#include "System.h"

namespace lp {

  DECLARE_SMART(Game, GamePtr);
  class Game : public SystemManager {
    public:
      int desiredFPS = 60;

      Game() {}
      virtual ~Game() {}

      virtual void awake();
      virtual void update(float dt, float sec);
      virtual void render(float dt, float sec);
      virtual void freeze();

      void run(int timestamp);

    protected:
      std::vector<Entity*> entities;
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
  };

}
