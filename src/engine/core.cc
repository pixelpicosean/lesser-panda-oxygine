#include "core.h"
#include "Game.h"

namespace lp {

  using namespace oxygine;

  char* engine::version = version;
  Game* engine::game = nullptr;
  Game* engine::nextGame = nullptr;
  float engine::speed = 1.0f;

  // This function is called each idle frame
  int engine::animationLoop() {
    // Handle input stuff
    bool done = core::update();

    // Full update
    update(oxygine::getTimeMS());

    return done ? 1 : 0;
  }

  // Application entry point
  void engine::main(const char* title, int width, int height, GameFactory factory) {
    oxygine::ObjectBase::__startTracingLeaks();

    // Initialize Oxygine's internal stuff
    core::init_desc desc;
    desc.title = title;

#if OXYGINE_SDL || OXYGINE_EMSCRIPTEN
    // The initial window size can be set up here on SDL builds
    desc.w = width;
    desc.h = height;
#endif

    core::init(&desc);

    // Create the stage. Stage is a root node for all updateable and drawable objects
    Stage::instance = new Stage(true);
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
    DebugActor::show();

    // Initializes
    init(factory);

#ifdef EMSCRIPTEN
    // If you build for Emscripten, mainloop is called automatically and shouldn't be called here.
    // See emscripten_set_main_loop in the EMSCRIPTEN section below
    return;
#endif



#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
    // On iPhone mainloop is called automatically by CADisplayLink, see int main() below
    return;
#endif

    // This is the main game loop.
    while (1) {
      int done = animationLoop();
      if (done) {
        break;
      }
    }
    /*
     If we get here, the user has requested the Application to terminate.
     We dump and log all our created objects that have not been freed yet
     */
    ObjectBase::dumpCreatedObjects();

    /*
     Let's clean up everything right now and call ObjectBase::dumpObjects() again.
     We need to free all allocated resources and delete all created actors.
     All actors/sprites are smart-pointer objects and don't need to be removed by hand.
     But now we want to delete it by hand.
     */

    // See example.cpp for the shutdown function implementation
    discard();

    // Releases all internal components and the stage
    core::release();

    // The dump list should be empty by now,
    // we want to make sure that there aren't any memory leaks, so we call it again.
    ObjectBase::dumpCreatedObjects();

    ObjectBase::__stopTracingLeaks();
  }

  void engine::setGame(GameFactory factory) {
    nextGame = factory();
  }

  void engine::init(GameFactory factory) {
    nextGame = factory();
  }

  void engine::update(int timestamp) {
    if (nextGame) {
      if (game) {
        game->freeze();
        delete game;
      }

      game = nextGame;
      game->awake();

      nextGame = nullptr;
    }

    // Update stage and all its child actors
    getStage()->update();

    // Render things
    if (core::beginRendering()) {
      Color clearColor(32, 32, 32, 255);
      Rect viewport(Point(0, 0), core::getDisplaySize());

      if (game) {
        game->run(timestamp);
      }

      getStage()->render(clearColor, viewport);

      core::swapDisplayBuffers();
    }
  }

  void engine::discard() {
    // Destroy alive game instances
    if (nextGame) {
      nextGame->freeze();
      delete nextGame;
      nextGame = nullptr;
    }

    if (game) {
      game->freeze();
      delete game;
      game = nullptr;
    }
  }

}
