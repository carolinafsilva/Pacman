#ifndef BLINKY_H
#define BLINKY_H

#include "ghost.hpp"

#include "pacman.hpp"
#include "maze.hpp"

class Blinky : public Ghost {
 private:
  int ignoreScatter[19] = {20, 30, 40, 40, 40,  50,  50,  50,  60, 60,
                           60, 80, 80, 80, 100, 100, 100, 100, 120};

  void updateTarget();

 public:
  Blinky(Pacman *pacman, Maze *maze);
  void reset();
};

#endif
