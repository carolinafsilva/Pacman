#include "game.hpp"

int main() {
  Game* game = new Game();
  game->debugMatrix();
  game->setup();
  game->run();
  game->clean();
  return 0;
}
