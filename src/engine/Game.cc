#include "Game.h"
#include "core.h"

#include <cmath>

namespace lp {

  Entity* Game::spawnEntity(const std::string &type, float x, float y) {
    auto p = Entity::entityTypes.find(type);
    if (p != Entity::entityTypes.end()) {
      auto ent = p->second(x, y);

      this->onEntitySpawn(ent);

      return ent;
    }

    // TODO: assertion
    return nullptr;
  }

  void Game::removeEntity(Entity* ent) {
    // Mark as removed
    ent->isRemoved = true;

    // Remove from name list
    if (ent->name.size() > 0) {
      this->namedEntities.erase(ent->name);
    }

    // Notify systems
    for (auto s: this->systems) {
      s.second->onEntityRemove(ent);
    }
  }

  void Game::removeEntity(int64 entID) {
    auto p = this->entities.find(entID);
    if (p != this->entities.end()) {
      this->removeEntity(p->second);
    }
  }

  void Game::awake() {
    for (auto s: this->systems) {
      s.second->awake();
    }
  }

  void Game::update(float dt, float sec) {
    for (auto s: this->systems) {
      s.second->update(dt, sec);
    }
  }

  void Game::render(float dt, float sec) {
    for (auto s: this->systems) {
      s.second->render(dt, sec);
    }
  }

  void Game::freeze() {
    for (auto s: this->systems) {
      s.second->freeze();
    }
  }

  void Game::run(int timestamp) {
    if (updateInfo.last > 0) {
      updateInfo.realDelta = timestamp - updateInfo.last;
    }
    updateInfo.last = timestamp;

    // If the logic time is spiraling upwards, skip a frame entirely
    if (updateInfo.spiraling > 1) {
      // Reset the deltaTime accumulator which will cause all pending dropped frames to be permanently skipped
      updateInfo.deltaTime = 0;
      updateInfo.spiraling = 0;
    }
    else {
      // Step size
      updateInfo.step = 1000.0f / this->desiredFPS;
      updateInfo.slowStep = updateInfo.step * lp::engine::speed;
      updateInfo.slowStepSec = updateInfo.slowStep * 0.001f;

      // Accumulate time until the step threshold is met or exceeded... up to a limit of 3 catch-up frames at step intervals
      updateInfo.deltaTime += std::fmax(std::fmin(updateInfo.step * 3.0f, updateInfo.realDelta), 0.0f);

      // Call the game update logic multiple times if necessary to "catch up" with dropped frames
      // unless forceSingleUpdate is true
      updateInfo.count = 0;

      while (updateInfo.deltaTime >= updateInfo.step) {
        updateInfo.deltaTime -= updateInfo.step;

        // Fixed update
        this->update(updateInfo.slowStep, updateInfo.slowStepSec);

        updateInfo.count += 1;
      }

      // Detect spiraling (if the catch-up loop isn't fast enough, the number of iterations will increase constantly)
      if (updateInfo.count > updateInfo.lastCount) {
        updateInfo.spiraling += 1;
      }
      else if (updateInfo.count < updateInfo.lastCount) {
        // Looks like it caught up successfully, reset the spiral alert counter
        updateInfo.spiraling = 0;
      }

      updateInfo.lastCount = updateInfo.count;
    }

    // Idle update
    this->render(updateInfo.realDelta, updateInfo.realDelta * 0.001f);
  }

  void Game::onEntitySpawn(lp::Entity *ent) {
    ent->game = this;

    // Add to list
    this->entities.insert(std::make_pair(ent->id, ent));

    // Add to name list if name exist
    this->namedEntities.insert(std::make_pair(ent->name, ent));

    // Notify systems
    for (auto s: this->systems) {
      s.second->onEntitySpawn(ent);
    }

    // Entity is ready to rock :D
    ent->ready();
  }

}
