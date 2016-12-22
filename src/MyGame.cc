#include "MyGame.h"

#include "engine/Gfx.h"

namespace game {

  MyGame::MyGame() {
    this->desiredFPS = 60;

    this->addSystem<lp::Gfx>();
  }

  MyGame::~MyGame() {}

  void MyGame::awake() {
    lp::Game::awake();

    // create button Sprite
    this->button = this->spawnEntity<Button>(getStage()->getWidth() / 2, getStage()->getHeight() / 2);

    log::message("Awake\n");
  }

  void MyGame::update(float dt, float sec) {
    lp::Game::update(dt, sec);

    this->timer += sec;
    if (this->timer > 3.0f) {
      lp::engine::setGame(MakeGameFactory(MyGame));
    }
  }

  void MyGame::freeze() {
    lp::Game::freeze();

    log::message("Freeze\n");
  }

}
