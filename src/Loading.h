#pragma once

#include "engine/Game.h"

#include "global.h"
#include "MyGame.h"

namespace game {

  class Loading : public lp::Game {
    public:
      void awake() {
        lp::Game::awake();

        // load resources
        global::gameRes.loadXML("res.xml");

        this->isLoaded = true;
      }

      void update(float dt, float sec) {
        lp::Game::update(dt, sec);

        // Switch to the first game
        if (this->isLoaded) {
          lp::engine::setGame(MakeGameFactory(MyGame));
        }
      }
    private:
      bool isLoaded = false;
  };

}
