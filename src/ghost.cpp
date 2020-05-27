#include "ghost.hpp"

Ghost::Ghost(Pacman *pacman) {
  this->pacman = pacman;
  this->position = (coords *)malloc(sizeof(coords));
  this->target = (coords *)malloc(sizeof(coords));
  this->home = (coords *)malloc(sizeof(coords));
}

Ghost::~Ghost() {
  free(this->position);
  free(this->target);
  free(this->home);
}

void Ghost::setPosition(coords position) {
  // TODO: implement
}

void Ghost::setTarget(coords target) {
  // TODO: implement
}

void Ghost::setMode(behaviour mode) {
  // TODO: implement
}

void Ghost::move() {
  // TODO: implement
}

coords Ghost::getSize() {
  // TODO: implement
}

coords Ghost::getPosition() {
  // TODO: implement
}

// TODO: add ghosts size to constructors

Blinky::Blinky(Pacman *pacman) : Ghost(pacman) {
  this->position->x = 11;
  this->position->y = 13;
  this->home->x = 1;
  this->home->y = 26;
}

Pinky::Pinky(Pacman *pacman) : Ghost(pacman) {
  this->position->x = 14;
  this->position->y = 13;
  this->home->x = 1;
  this->home->y = 1;
}

Inky::Inky(Pacman *pacman, Blinky *blinky) : Ghost(pacman) {
  this->blinky = blinky;
  this->position->x = 12;
  this->position->y = 13;
  this->home->x = 29;
  this->home->y = 26;
}

Clyde::Clyde(Pacman *pacman) : Ghost(pacman) {
  this->distanceToPacman = 0;
  this->position->x = 16;
  this->position->y = 13;
  this->home->x = 29;
  this->home->y = 1;
}

void Clyde::updateDistanceToPacman() {
  // TODO: implement
}
