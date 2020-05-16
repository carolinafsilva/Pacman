#include "pacman.hpp"

Pacman::Pacman() {
  this->direction = left;

  this->position = (coords *)malloc(sizeof(coords));

  this->position->x = 23;
  this->position->y = 13;

  this->lives = 4;
}

Pacman::~Pacman() { free(this->position); }
