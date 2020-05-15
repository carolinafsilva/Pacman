#ifndef PACMAN_H
#define PACMAN_H

struct position {
  int x;
  int y;
};

class Pacman {
 private:
  position pos;
  int lives;

 public:
  position getPosition();

  void setPosition(position pos);

  Pacman();
};

#endif
