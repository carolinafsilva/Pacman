#ifndef CLYDE_H
#define CLYDE_H

#include "ghost.hpp"

#include "pacman.hpp"
#include "maze.hpp"

class Clyde : public Ghost {
 private:
  bool aroundPacman;

  void checkDistanceToPacman();

  void updateTarget();

 public:
  Clyde(Pacman *pacman, Maze *maze);
  void reset();
};

#endif
