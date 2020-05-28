#ifndef GHOST_H
#define GHOST_H

#include "opengl.hpp"
#include "maze.hpp"
#include "pacman.hpp"

enum behaviour { scatter, chase, frightened, eaten };

class Ghost {
 protected:
  Pacman *pacman;
  Maze *maze;

  orientation direction;

  glm::vec3 position;
  glm::vec2 target;
  glm::vec2 home;

  static behaviour mode;

  void setTarget(glm::vec2 target);

 public:
  static void setMode(behaviour mode);

  glm::vec3 getPosition();

  void updatePosition(float delta);

  Ghost(Pacman *pacman, Maze *maze);
  ~Ghost();
};

class Blinky : public Ghost {
 private:
  int ignoreScatter[19] = {20, 30, 40, 40, 40,  50,  50,  50,  60, 60,
                           60, 80, 80, 80, 100, 100, 100, 100, 120};

  void setTarget(glm::vec2 target);

 public:
  Blinky(Pacman *pacman, Maze *maze);

  void updatePosition(float delta);
};

class Pinky : public Ghost {
 private:
  void setTarget(glm::vec2 target);

 public:
  Pinky(Pacman *pacman, Maze *maze);

  void updatePosition(float delta);
};

class Inky : public Ghost {
 private:
  Blinky *blinky;

  void setTarget(glm::vec2 target);

 public:
  Inky(Pacman *pacman, Maze *maze, Blinky *blinky);

  void updatePosition(float delta);
};

class Clyde : public Ghost {
 private:
  int distanceToPacman;

  void updateDistanceToPacman();

  void setTarget(glm::vec2 target);

 public:
  Clyde(Pacman *pacman, Maze *maze);

  void updatePosition(float delta);
};

#endif
