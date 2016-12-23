#include "Input.hpp"

#include <utility>

namespace lp {

  using namespace oxygine;

  Input::Input() {}

  Input::~Input() {}

  void Input::bind(SDL_Keycode key, const std::string &action) {
    this->keyList.insert(key);

    auto list = this->bindings[key];
    list.insert(action);
    this->bindings[key] = list;

    this->lastPressed[action] = false;
    this->lastReleased[action] = false;
  }

  void Input::unbind(SDL_Keycode key, const std::string &action) {
    if (this->keyList.find(key) != this->keyList.end()) {
      auto list = this->bindings[key];
      list.erase(action);

      this->lastPressed.erase(action);
      this->lastReleased.erase(action);
    }
  }

  void Input::unbindAll() {
    this->keyList.clear();
    this->bindings.clear();
    this->lastPressed.clear();
    this->lastReleased.clear();
  }

  bool Input::state(const std::string &action) {
    return this->actions[action];
  }

  bool Input::pressed(const std::string &action) {
    return this->lastPressed[action];
  }

  bool Input::released(const std::string &action) {
    return this->lastReleased[action];
  }

  void Input::awake() {
    this->resetFlags();

    this->handlerID = core::getDispatcher()->addEventListener(core::EVENT_SYSTEM, CLOSURE(this, &Input::keyHandler));
  }

  void Input::update(float dt, float sec) {
    this->resetFlags();
  }

  void Input::freeze() {
    core::getDispatcher()->removeEventListener(this->handlerID);

    this->resetFlags();
  }

  void Input::keyHandler(oxygine::Event *evt) {
    SDL_Event *event = (SDL_Event*)evt->userData;

    if (event->key.repeat != 0) {
      return;
    }

    if (event->type == SDL_KEYDOWN) {
      this->keydown(event->key.keysym.sym);
    }
    else if (event->type == SDL_KEYUP) {
      this->keyup(event->key.keysym.sym);
    }
  }

  void Input::keydown(SDL_Keycode key) {
    if (this->keyList.find(key) != this->keyList.end()) {
      auto list = this->bindings[key];
      for (auto act : list) {
        this->actions[act] = true;
        this->lastPressed[act] = true;
      }
    }
  }

  void Input::keyup(SDL_Keycode key) {
    if (this->keyList.find(key) != this->keyList.end()) {
      auto list = this->bindings[key];
      for (auto act : list) {
        this->actions[act] = false;
        this->lastReleased[act] = true;
      }
    }
  }

  void Input::resetFlags() {
    for (auto i : this->lastPressed) {
      i.second = false;
    }

    for (auto i : this->lastReleased) {
      i.second = false;
    }
  }

}
