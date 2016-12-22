#include "core.h"
#include "Game.h"

namespace lp {

  Game* engine::game = nullptr;
  Game* engine::nextGame = nullptr;

  float engine::speed = 1.0f;

  void engine::setGame(GameFactory factory) {
    nextGame = factory();
  }

  void engine::update(int timestamp) {
    if (nextGame) {
      if (game) {
        game->freeze();
        delete game;
      }

      game = nextGame;
      game->awake();

      nextGame = nullptr;
    }

    if (game) {
      game->run(timestamp);
    }
  }

  void engine::discard() {
    // Destroy alive game instances
    if (nextGame) {
      nextGame->freeze();
      delete nextGame;
      nextGame = nullptr;
    }

    if (game) {
      game->freeze();
      delete game;
      game = nullptr;
    }
  }

}
