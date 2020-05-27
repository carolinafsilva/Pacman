#include "pacman.hpp"

Pacman::Pacman() {
  this->direction = left;
  this->position = glm::vec3(23, 13, 13);  // FIXME: pixel coordinates

  // TODO: add size

  this->lives = 4;
}

Pacman::~Pacman() {}

orientation Pacman::getOrientation() {
  // TODO: implement
}

glm::vec3 Pacman::getPosition() {
  // TODO: implement
}

glm::vec3 Pacman::getSize() {
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
