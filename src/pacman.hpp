#ifndef PACMAN_H
#define PACMAN_H

#include "opengl.hpp"
#include "maze.hpp"

enum orientation { up, left, down, right };

class Pacman {
 private:
  orientation direction;

  glm::vec3 position;

  int lives;

 public:
  orientation getOrientation();
  glm::vec3 getPosition();
  int getLives();

  void setOrientation(orientation direction = left);

  void updatePosition();

  Pacman();
  ~Pacman();
};

#endif
