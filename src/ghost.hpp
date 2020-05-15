#ifndef GHOST_H
#define GHOST_H

#include "maze.hpp"
#include "pacman.hpp"

enum behaviour { scatter, chase, frightened, eaten };

class Ghost {
 protected:
  Pacman *pacman;

  coords position;
  coords target;

  behaviour mode;

  void setPosition(coords position);
  void setTarget(coords target);

 public:
  coords getPosition();

  void setMode(behaviour mode);
  void move();

  Ghost(Pacman *pacman);
};

class Blinky : public Ghost {
 private:
  int ignoreScatterLimit;

 public:
  void increaseIgnoreScatterLimit();

  Blinky();
};

class Pinky : public Ghost {
 private:
 public:
  Pinky();
};

class Inky : public Ghost {
 private:
  Blinky *blinky;

 public:
  Inky();
};

class Clyde : public Ghost {
 private:
  int distanceToPacman;

  void updateDistanceToPacman();

 public:
  Clyde();
};

#endif
