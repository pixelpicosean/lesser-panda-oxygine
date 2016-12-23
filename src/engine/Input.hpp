#pragma once

#include "core/oxygine.h"
#include "SDL.h"
#include "SDL_keyboard.h"

#include "System.hpp"

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace lp {

  class Input : public System<Input> {
    public:
      Input();
      ~Input();

      void bind(SDL_Keycode key, const std::string& action);
      void unbind(SDL_Keycode key, const std::string& action);
      void unbindAll();

      bool state(const std::string& action);
      bool pressed(const std::string& action);
      bool released(const std::string& action);

      void awake() override;
      void update(float dt, float sec) override;
      void freeze() override;

    private:
      int handlerID = -1;

      std::unordered_map<SDL_Keycode, std::unordered_set<std::string> > bindings;
      std::unordered_set<SDL_Keycode> keyList;
      std::unordered_map<std::string, bool> actions;
      std::unordered_map<std::string, bool> lastPressed;
      std::unordered_map<std::string, bool> lastReleased;

      void keyHandler(oxygine::Event* evt);

      void keydown(SDL_Keycode key);
      void keyup(SDL_Keycode key);

      void resetFlags();
  };

}
