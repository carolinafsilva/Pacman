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
  bool dead;

  bool inTunnel();
  void checkTunnel();

 public:
  orientation getOrientation();
  glm::vec3 getPosition();
  int getLives();
  bool isDead();

  void setOrientation(orientation direction);
  void setIsDead(bool dead);
  void decrementLives();

  void updatePosition(float delta);
  void reset();

  Pacman(Maze *maze);
  ~Pacman();
};

#endif
