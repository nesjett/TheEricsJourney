//#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "src/public/game.h" // Init the game instance
//#include "src/public/Engine.h" // INit the graphics engine

#define kVel 5

int main() {
  
  game *gameinstance = game::Instance();
  gameinstance->init();
  gameinstance->run();
  return EXIT_SUCCESS;
}