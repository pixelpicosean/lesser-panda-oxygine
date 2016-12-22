#pragma once

#include "oxygine-framework.h"

#include <functional>

namespace lp {

  static const char* version = "v0.0.1";

  class Game;

  typedef std::function<Game*()> GameFactory;

  struct engine {
    static Game* game;
    static float speed;

    static void setGame(GameFactory factory);

    static void update(int timestamp);
    static void discard();

    static Game* nextGame;
  };

}
