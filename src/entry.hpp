#pragma once

#include <string>

#include "oxygine-framework.h"

#include "engine/core.hpp"

#include "game/Loading.hpp"

namespace game {

  void setup(oxygine::core::init_desc& desc) {
    desc.w = 640;
    desc.h = 480;
    desc.title = "LesserPanda Native";
  }

  void start() {
    lp::engine::setGame(MakeGameFactory(game::Loading));
  }

}
