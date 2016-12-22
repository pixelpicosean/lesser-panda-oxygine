#include "MyGame.h"

#include "engine/Gfx.h"

Resources gameRes;

MyGame::MyGame() {
  this->desiredFPS = 60;

  this->addSystem<lp::Gfx>();

  // load resources
  gameRes.loadXML("res.xml");

  // create button Sprite
  button = new Sprite();

  // setup the button
  button->setResAnim(gameRes.getResAnim("button"));
  button->setAnchor(0.5f, 0.5f);
  button->setPosition(getStage()->getSize() / 2);

  button->addEventListener(TouchEvent::CLICK, [](Event * e)->void {
    log::messageln("button clicked");
  });

  // attach button as child to the root
  auto s = this->system<lp::Gfx>();
  s->root->addChild(button);
}

MyGame::~MyGame() {}

void MyGame::awake() {
  lp::Game::awake();

  printf("Awake\n");
}

void MyGame::update(float dt, float sec) {
  lp::Game::update(dt, sec);

  this->button->setRotationDegrees(this->button->getRotationDegrees() + sec * 90);
}

void MyGame::freeze() {
  lp::Game::freeze();

  printf("Freeze\n");
}
