#ifndef GAME_H
#define GAME_H

#include <vector>

#include "ghost.hpp"
#include "maze.hpp"
#include "pacman.hpp"
#include "window.hpp"

class Game {
 private:
  Window *window;

  Maze *maze;

  Pacman *pacman;

  std::vector<Ghost *> ghosts;

  int score;

 public:
  void setup();
  void run();
  void clean();

  void debugMatrix();

  Game();
};

#endif
