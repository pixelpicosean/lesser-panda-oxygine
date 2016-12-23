#pragma once

#include "oxygine-framework.h"

#include "../engine/Game.hpp"
#include "../engine/Entity.hpp"

#include "global.hpp"

using namespace oxygine;

namespace game {

  class Button : public lp::Entity {
    public:
      Button(float x, float y): lp::Entity(x, y) {
        this->canEverTick = true;

        // Components
        auto g = new Sprite();
        auto res = global::gameRes.getResAnim("button");
        g->setResAnim(res);
        g->setAnchor(0.5f, 0.5f);

        g->addEventListener(TouchEvent::CLICK, [](Event * e)->void {
          log::messageln("button clicked");
        });

        this->gfx = g;
      }

      void update(float dt, float sec) override {
        lp::Entity::update(dt, sec);

        this->gfx->setRotationDegrees(this->gfx->getRotationDegrees() + sec * 90);
      }
  };

  class MyGame : public lp::Game {
    public:
      MyGame();
      ~MyGame();

      void awake() override;
      void update(float dt, float sec) override;
      void freeze() override;

    private:
      Button *button = nullptr;
      float timer = 0.0f;
  };

}
