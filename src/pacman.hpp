#ifndef PACMAN_H
#define PACMAN_H

#include "maze.hpp"

enum orientation { up, left, down, right };

class Pacman {
 private:
  orientation direction;

  coords *position;

  int lives;

 public:
  orientation getOrientation();
  coords getPosition();
  int getLives();

  void setPosition(coords position);
  void setOrientation(orientation direction = left);
  void die();

  Pacman();
  ~Pacman();
};

#endif
