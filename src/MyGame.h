#pragma once

#include "oxygine-framework.h"

#include "engine/Game.h"

using namespace oxygine;

class MyGame : public lp::Game {
  public:
    MyGame();
    ~MyGame();

    void awake() override;
    void update(float dt, float sec) override;
    void freeze() override;

  private:
    spSprite button = nullptr;
};
