#ifndef PACMAN_H
#define PACMAN_H

#include "opengl.hpp"
#include "maze.hpp"

class Pacman {
 private:
  Maze *maze;

  orientation direction;
  glm::vec3 position;

  int lives;

 public:
  orientation getOrientation();
  glm::vec3 getPosition();
  int getLives();

  void setOrientation(orientation direction);

  void updatePosition(float delta);

  Pacman(Maze *maze);
  ~Pacman();
};

#endif
