#ifndef PINKY_H
#define PINKY_H

#include "ghost.hpp"

#include "pacman.hpp"
#include "maze.hpp"

class Pinky : public Ghost {
 private:
  void updateTarget();

 public:
  Pinky(Pacman *pacman, Maze *maze);
  void reset();
};

#endif
