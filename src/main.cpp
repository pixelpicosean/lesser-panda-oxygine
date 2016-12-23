#include "oxygine-framework.h"

#include "engine/core.hpp"
#include "entry.hpp"


using namespace oxygine;


// This function is called each frame
int mainloop() {
  // Update oxygine
  bool done = core::update();

  // Update the active scene tree
  getStage()->update();

  // Render
  if (core::beginRendering()) {
    // Update the engine
    lp::engine::update(getTimeMS());

    // Clear and render the active scene tree
    Color clearColor(32, 32, 32, 255);
    Rect viewport(Point(0, 0), core::getDisplaySize());

    getStage()->render(clearColor, viewport);

    core::swapDisplayBuffers();
  }

  return done ? 1 : 0;
}

// Application entry point
void run() {
  ObjectBase::__startTracingLeaks();

  // Initialize
  core::init_desc desc;
  game::setup(desc);
  core::init(&desc);

  // Create the stage. Stage is a root node for all updateable and drawable objects
  Stage::instance = new Stage(true);
  Point size = core::getDisplaySize();
  getStage()->setSize(size);

  // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
  DebugActor::show();

  // Initializes
  game::start();

#ifdef EMSCRIPTEN
  /*
   If you build for Emscripten, mainloop is called automatically and shouldn't be called here.
   See emscripten_set_main_loop in the EMSCRIPTEN section below
   */
  return;
#endif

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
  // On iPhone mainloop is called automatically by CADisplayLink, see int main() below
  return;
#endif

  // This is the main game loop.
  while (1) {
    int done = mainloop();
    if (done) break;
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

  lp::engine::discard();

  // Releases all internal components and the stage
  core::release();

  // The dump list should be empty by now,
  // we want to make sure that there aren't any memory leaks, so we call it again.
  ObjectBase::dumpCreatedObjects();

  ObjectBase::__stopTracingLeaks();
}


#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C" {

  void one(void* param) { mainloop(); }
  void oneEmsc() { mainloop(); }

  int main(int argc, char* argv[]) {
    run();

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
    // If parameter 2 is set to 1, refresh rate will be 60 fps, 2 - 30 fps, 3 - 15 fps.
    SDL_iPhoneSetAnimationCallback(core::getWindow(), 1, one, nullptr);
#endif

#if EMSCRIPTEN
    emscripten_set_main_loop(oneEmsc, 0, 0);
#endif

    return 0;
  }

};
#endif
