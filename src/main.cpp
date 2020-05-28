#include "game.hpp"

int main() {
  Game* game = new Game();
  game->setup();
  game->run();
  game->clean();
  return 0;
}
