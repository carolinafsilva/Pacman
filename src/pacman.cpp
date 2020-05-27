#include "pacman.hpp"

Pacman::Pacman() {
  this->direction = left;
  this->position = glm::vec3(104, 62, 16);

  this->lives = 4;
}

Pacman::~Pacman() {}

orientation Pacman::getOrientation() {
  // TODO: implement
}

glm::vec3 Pacman::getPosition() {
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
