#include "MyGame.hpp"

#include "../engine/Gfx.hpp"
#include "../engine/Input.hpp"

namespace game {

  MyGame::MyGame() {
    this->desiredFPS = 60;

    this->addSystem<lp::Gfx>();
    this->addSystem<lp::Input>();
  }

  MyGame::~MyGame() {}

  void MyGame::awake() {
    lp::Game::awake();

    // create button Sprite
    this->button = this->spawnEntity<Button>(getStage()->getWidth() / 2, getStage()->getHeight() / 2);

    // Bind input actions
    auto input = this->system<lp::Input>();
    input->bind(SDLK_LEFT, "left");
    input->bind(SDLK_RIGHT, "right");
    input->bind(SDLK_UP, "jump");

    log::message("Awake\n");
  }

  void MyGame::update(float dt, float sec) {
    lp::Game::update(dt, sec);

    static const float Speed = 160.0f;

    bool left = this->system<lp::Input>()->state("left");
    bool right = this->system<lp::Input>()->state("right");
    if (left != right) {
      if (left) {
        this->button->setPosition(this->button->getPosition().x - Speed * sec, this->button->getPosition().y);
      }
      else {
        this->button->setPosition(this->button->getPosition().x + Speed * sec, this->button->getPosition().y);
      }
    }
    if (this->system<lp::Input>()->pressed("jump")) {
      lp::engine::setGame(MakeGameFactory(MyGame));
    }
  }

  void MyGame::freeze() {
    lp::Game::freeze();

    // Bind input actions
    auto input = this->system<lp::Input>();
    input->unbind(SDLK_LEFT, "left");
    input->unbind(SDLK_RIGHT, "right");
    input->unbind(SDLK_UP, "jump");

    log::message("Freeze\n");
  }

}
