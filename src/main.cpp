#include "engine/core.h"

#include "MyGame.h"

int main(int argc, const char* argv[]) {
  lp::engine::main("LesserPanda", 640, 480, [] {
    return new MyGame();
  });

  return 0;
}
