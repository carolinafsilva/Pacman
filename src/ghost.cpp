#include "ghost.hpp"

Ghost::Ghost(Pacman *pacman) { this->pacman = pacman; }

Ghost::~Ghost() {}

void Ghost::updatePosition() {
  // TODO: implement
}

void Ghost::setTarget(glm::vec3 target) {
  // TODO: implement
}

void Ghost::setMode(behaviour mode) {
  // TODO: implement
}

glm::vec3 Ghost::getPosition() {
  // TODO: implement
}

// TODO: add ghosts size to constructors

Blinky::Blinky(Pacman *pacman) : Ghost(pacman) {
  this->position = glm::vec3(104, 148, 16);
  this->home = glm::vec2(0, 240);
}

Pinky::Pinky(Pacman *pacman) : Ghost(pacman) {
  this->position = glm::vec3(104, 128, 16);
  this->home = glm::vec2(216, 240);
}

Inky::Inky(Pacman *pacman, Blinky *blinky) : Ghost(pacman) {
  this->blinky = blinky;
  this->position = glm::vec3(88, 128, 16);
  this->home = glm::vec2(216, 0);
}

Clyde::Clyde(Pacman *pacman) : Ghost(pacman) {
  this->distanceToPacman = 0;
  this->position = glm::vec3(120, 128, 16);
  this->home = glm::vec2(0, 0);
}

void Clyde::updateDistanceToPacman() {
  // TODO: implement
}
