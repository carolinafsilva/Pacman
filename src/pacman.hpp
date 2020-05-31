#ifndef PACMAN_H
#define PACMAN_H

#include "opengl.hpp"
#include "maze.hpp"

class Pacman {
 private:
  // ---------------------------------------------------------------------------
  // Attributes

  Maze *maze;

  orientation direction;
  glm::vec3 position;

  int lives;
  bool dead;

  // ---------------------------------------------------------------------------
  // Methods

  bool inTunnel();
  void checkTunnel();

 public:
  // ---------------------------------------------------------------------------
  // Getters

  orientation getOrientation();
  glm::vec3 getPosition();
  int getLives();
  bool isDead();

  // ---------------------------------------------------------------------------
  // Setters

  void setOrientation(orientation direction);
  void setIsDead(bool dead);

  // ---------------------------------------------------------------------------
  // Methods

  void updatePosition(float delta);
  void decrementLives();
  void reset(bool restart);

  // ---------------------------------------------------------------------------
  // Constructors

  Pacman(Maze *maze);
  ~Pacman();
};

#endif
