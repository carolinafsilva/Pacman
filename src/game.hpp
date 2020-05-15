#ifndef GAME_H
#define GAME_H

#include "ghost.hpp"
#include "maze.hpp"
#include "pacman.hpp"
#include "window.hpp"

class Game {
 private:
  Window *window;

  Maze *maze;

  Pacman *pacman;

  Blinky *blinky;
  Pinky *pinky;
  Inky *inky;
  Clyde *clide;

 public:
  void setup();
  void run();
  void clean();

  Game();
};

#endif
