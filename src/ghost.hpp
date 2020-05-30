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
  bool useDoor;
  bool isHome;

  static behaviour mode;

  void move(float delta);
  orientation oppositeDirection(orientation direction);
  virtual void updateTarget() = 0;
  void updateDirection();
  void checkNeighbours(float distances[]);
  bool isBelowDoor();

 public:
  static const char *personality[4];

  void turnAround();
  void setMode(behaviour mode);

  void setIsHome(bool isHome);
  void setUseDoor(bool door);
  void setOrientation(orientation direction);

  glm::vec3 getPosition();
  behaviour getMode();

  void updatePosition(float delta);

  Ghost(Pacman *pacman, Maze *maze);
  virtual ~Ghost();
};

class Blinky : public Ghost {
 private:
  int ignoreScatter[19] = {20, 30, 40, 40, 40,  50,  50,  50,  60, 60,
                           60, 80, 80, 80, 100, 100, 100, 100, 120};

  void updateTarget();

 public:
  Blinky(Pacman *pacman, Maze *maze);
};

class Pinky : public Ghost {
 private:
  void updateTarget();

 public:
  Pinky(Pacman *pacman, Maze *maze);
};

class Inky : public Ghost {
 private:
  Blinky *blinky;

  void updateTarget();

 public:
  Inky(Pacman *pacman, Maze *maze, Ghost *blinky);
};

class Clyde : public Ghost {
 private:
  bool aroundPacman;

  void checkDistanceToPacman();

  void updateTarget();

 public:
  Clyde(Pacman *pacman, Maze *maze);
};

#endif
