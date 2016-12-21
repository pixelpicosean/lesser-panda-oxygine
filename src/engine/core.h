#pragma once

#include "oxygine-framework.h"
#include "Game.h"

#include <functional>
#include <string>

namespace lp {

  class engine {
    public:
      static std::string version;

      static Game* game;
      static float speed;

      typedef std::function<Game*()> GameFactory;

      static void main(const char* title, int width, int height, GameFactory factory);
      static void setGame(GameFactory factory);

    private:
      static Game* nextGame;

      static void init(GameFactory factory);
      static void update(int timestamp);
      static void discard();

      static int animationLoop();
  };

}
