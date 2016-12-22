#include "engine/core.h"

#include "Loading.h"

int main(int argc, const char* argv[]) {
  lp::engine::main("LesserPanda", 640, 480, MakeGameFactory(game::Loading));

  return 0;
}
