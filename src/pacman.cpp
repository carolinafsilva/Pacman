#include "pacman.hpp"

Pacman::Pacman() {
  this->direction = left;

  this->position->x = 23;
  this->position->y = 13;

  this->lives = 3;
}
