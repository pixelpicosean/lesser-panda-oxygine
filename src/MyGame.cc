#include "MyGame.h"

#include "engine/Gfx.h"

namespace game {

  MyGame::MyGame() {
    this->desiredFPS = 60;

    this->addSystem<lp::Gfx>();

    // load resources
    gameRes.loadXML("res.xml");

    // create button Sprite
    this->button = this->spawnEntity<Button>(getStage()->getWidth() / 2, getStage()->getHeight() / 2);
  }

  MyGame::~MyGame() {}

  void MyGame::awake() {
    lp::Game::awake();

    log::message("Awake\n");
  }

  void MyGame::update(float dt, float sec) {
    lp::Game::update(dt, sec);
  }

  void MyGame::freeze() {
    lp::Game::freeze();

    log::message("Freeze\n");
  }

}
