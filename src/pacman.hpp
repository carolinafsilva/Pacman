#ifndef PACMAN_H
#define PACMAN_H

#include "opengl.hpp"
#include "maze.hpp"

enum orientation { up, left, down, right };

class Pacman {
 private:
  orientation direction;

  glm::vec3 position;

  glm::vec3 size;

  int lives;

 public:
  orientation getOrientation();
  glm::vec3 getPosition();
  glm::vec3 getSize();
  int getLives();

  void updatePosition();
  void setOrientation(orientation direction = left);

  void die();

  Pacman();
  ~Pacman();
};

#endif
