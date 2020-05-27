#ifndef PACMAN_H
#define PACMAN_H

#include "maze.hpp"

enum orientation { up, left, down, right };

class Pacman {
 private:
  orientation direction;

  coords *position;

  coords *size;

  int lives;

 public:
  orientation getOrientation();
  coords getPosition();
  coords getSize();
  int getLives();

  void updatePosition();
  void setOrientation(orientation direction = left);

  void die();

  Pacman();
  ~Pacman();
};

#endif
