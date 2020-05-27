#include "pacman.hpp"

Pacman::Pacman() {
  this->direction = left;

  this->position = (coords *)malloc(sizeof(coords));

  this->position->x = 23;  // FIXME: pixel coordinates
  this->position->y = 13;  // FIXME: pixel coordinates

  // TODO: add size

  this->lives = 4;
}

Pacman::~Pacman() { free(this->position); }

orientation Pacman::getOrientation() {
  // TODO: implement
}

coords Pacman::getPosition() {
  // TODO: implement
}

coords Pacman::getSize() {
  // TODO: implement
}

int Pacman::getLives() {
  // TODO: implement
}

void Pacman::updatePosition() {
  // TODO: implement
}

void Pacman::setOrientation(orientation direction) {
  // TODO: implement
}
