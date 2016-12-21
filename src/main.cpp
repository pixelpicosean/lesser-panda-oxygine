#include "engine/core.h"

#include "engine/Game.h"

using namespace oxygine;

Resources gameRes;

class MyGame : public lp::Game {
  public:
    MyGame() {
      this->root = new Actor();

      // load resources
      gameRes.loadXML("res.xml");

      // create button Sprite
      spSprite button = new Sprite();

      // setup it
      // set button.png image. Resource 'button' defined in 'res.xml'
      button->setResAnim(gameRes.getResAnim("button"));

      // centered button at screen
      Vector2 pos = getStage()->getSize() / 2 - button->getSize() / 2;
      button->setPosition(pos);

      button->addEventListener(TouchEvent::CLICK, [](Event * e)->void {
        log::messageln("button clicked");
      });

      // attach button as child to the root
      this->root->addChild(button);
    }
    void awake() {
      lp::Game::awake();

      getStage()->addChild(this->root);

      printf("Awake\n");
    }
    void freeze() {
      lp::Game::freeze();

      getStage()->removeChild(this->root);
      this->root = nullptr;
    }

  private:
    spActor root = nullptr;
};

int main(int argc, const char* argv[]) {
  lp::engine::main("LesserPanda", 640, 480, [] {
    return new MyGame();
  });

  return 0;
}
