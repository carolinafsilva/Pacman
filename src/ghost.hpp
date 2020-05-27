#ifndef GHOST_H
#define GHOST_H

#include "opengl.hpp"
#include "maze.hpp"
#include "pacman.hpp"

enum behaviour { scatter, chase, frightened, eaten };

class Ghost {
 protected:
  Pacman *pacman;

  glm::vec3 position;
  glm::vec2 target;
  glm::vec2 home;

  static behaviour mode;

  void setTarget(glm::vec3 target);

 public:
  static void setMode(behaviour mode);

  glm::vec3 getPosition();

  void updatePosition();

  Ghost(Pacman *pacman);
  ~Ghost();
};

class Blinky : public Ghost {
 private:
  int ignoreScatter[19] = {20, 30, 40, 40, 40,  50,  50,  50,  60, 60,
                           60, 80, 80, 80, 100, 100, 100, 100, 120};

 public:
  Blinky(Pacman *pacman);
};

class Pinky : public Ghost {
 private:
 public:
  Pinky(Pacman *pacman);
};

class Inky : public Ghost {
 private:
  Blinky *blinky;

 public:
  Inky(Pacman *pacman, Blinky *blinky);
};

class Clyde : public Ghost {
 private:
  int distanceToPacman;

  void updateDistanceToPacman();

 public:
  Clyde(Pacman *pacman);
};

#endif
