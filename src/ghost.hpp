#ifndef GHOST_H
#define GHOST_H

#include <math.h>

#include <limits>
#include <string>

#include "opengl.hpp"
#include "maze.hpp"

#include "pacman.hpp"

enum behaviour { scatter, frightened, chase };

class Ghost {
 protected:
  std::string name;

  Pacman *pacman;
  Maze *maze;

  orientation direction;

  glm::vec3 position;
  glm::vec2 target;
  glm::vec2 home;
  glm::vec2 homeExit;
  glm::vec2 homeEntrance;

  bool useDoor;
  bool isHome;
  bool dead;

  static behaviour mode;

  void move(float delta);
  orientation oppositeDirection(orientation direction);
  virtual void updateTarget() = 0;
  void updateDirection();
  void checkNeighbours(float distances[]);
  void checkTunnel();
  bool isBelowDoor();

 public:
  static const char *personality[4];

  void turnAround();
  static void setMode(behaviour mode);

  void setIsHome(bool isHome);
  void setUseDoor(bool door);
  void setDead(bool dead);
  void setOrientation(orientation direction);

  glm::vec3 getPosition();
  orientation getOrientation();
  static behaviour getMode();
  bool isDead();

  void updatePosition(float delta);
  virtual void reset() = 0;

  Ghost(Pacman *pacman, Maze *maze);
  virtual ~Ghost();
};

#endif
