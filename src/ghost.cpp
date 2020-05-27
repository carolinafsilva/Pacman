#include "ghost.hpp"

Ghost::Ghost(Pacman *pacman) { this->pacman = pacman; }

Ghost::~Ghost() {}

void Ghost::setPosition(glm::vec3 position) {
  // TODO: implement
}

void Ghost::setTarget(glm::vec3 target) {
  // TODO: implement
}

void Ghost::setMode(behaviour mode) {
  // TODO: implement
}

void Ghost::move() {
  // TODO: implement
}

glm::vec3 Ghost::getSize() {
  // TODO: implement
}

glm::vec3 Ghost::getPosition() {
  // TODO: implement
}

// TODO: add ghosts size to constructors

Blinky::Blinky(Pacman *pacman) : Ghost(pacman) {
  this->position.x = 11;
  // this->position->y = 13;
  // this->home->x = 1;
  // this->home->y = 26;
}

Pinky::Pinky(Pacman *pacman) : Ghost(pacman) {
  // this->position->x = 14;
  // this->position->y = 13;
  // this->home->x = 1;
  // this->home->y = 1;
}

Inky::Inky(Pacman *pacman, Blinky *blinky) : Ghost(pacman) {
  this->blinky = blinky;
  // this->position->x = 12;
  // this->position->y = 13;
  // this->home->x = 29;
  // this->home->y = 26;
}

Clyde::Clyde(Pacman *pacman) : Ghost(pacman) {
  this->distanceToPacman = 0;
  // this->position->x = 16;
  // this->position->y = 13;
  // this->home->x = 29;
  // this->home->y = 1;
}

void Clyde::updateDistanceToPacman() {
  // TODO: implement
}
