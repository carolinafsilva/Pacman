#ifndef GHOST_H
#define GHOST_H

#include <limits.h>
#include <math.h>

#include "opengl.hpp"
#include "maze.hpp"
#include "pacman.hpp"

enum behaviour { scatter, frightened, chase };

class Ghost {
 protected:
  Pacman *pacman;
  Maze *maze;

  orientation direction;

  glm::vec3 position;
  glm::vec2 target;
  glm::vec2 home;

  static behaviour mode;

  void move(float delta);
  orientation oppositeDirection(orientation direction);
  virtual void updateTarget() = 0;
  void updateDirection();
  void checkNeighbours(float distances[]);

 public:
  static const std::string personality[4];

  static void setMode(behaviour mode);

  glm::vec3 getPosition();
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

  void updatePosition(float delta);
};

#endif
