#ifndef INKY_H
#define INKY_H

#include "ghost.hpp"

#include "pacman.hpp"
#include "maze.hpp"
#include "blinky.hpp"

class Inky : public Ghost {
 private:
  Blinky *blinky;

  void updateTarget();

 public:
  Inky(Pacman *pacman, Maze *maze, Ghost *blinky);
  void reset();
};

#endif
