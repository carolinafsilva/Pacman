#ifndef GHOST_H
#define GHOST_H

#include "pacman.hpp"

enum behaviour { scatter, chase, frightened, eaten };

class Ghost {
 protected:
  position pos;
  position target;

  behaviour mode;

 public:
  position getPosition();

  void setMode(behaviour mode);
  void setPosition(position pos);
  void setTarget(position target);

  Ghost();
};

class Blinky : public Ghost {
 private:
  Pacman *pacman;

  int ignoreScatterLimit;

 public:
  void move();
  void increaseIgnoreScatterLimit();
  Blinky();
};

class Pinky : public Ghost {
 private:
  Pacman *pacman;

 public:
  void move();
  Pinky();
};

class Inky : public Ghost {
 private:
  Pacman *pacman;

 public:
  void move();
  Inky();
};

class Clyde : public Ghost {
 private:
  Pacman *pacman;

 public:
  void move();
  Clyde();
};

#endif
