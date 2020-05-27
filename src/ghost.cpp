#include "ghost.hpp"

Ghost::Ghost(Pacman *pacman, Maze *maze) {
  this->pacman = pacman;
  this->maze = maze;
}

Ghost::~Ghost() {}

void Ghost::setMode(behaviour mode) { Ghost::mode = mode; }

glm::vec3 Ghost::getPosition() { return this->position; }

void Ghost::setTarget(glm::vec2 target) { this->target = target; }

Blinky::Blinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->position = glm::vec3(104, 148, 16);
  this->home = glm::vec2(0, 240);
}

Pinky::Pinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->position = glm::vec3(104, 128, 16);
  this->home = glm::vec2(216, 240);
}

Inky::Inky(Pacman *pacman, Maze *maze, Blinky *blinky) : Ghost(pacman, maze) {
  this->blinky = blinky;
  this->position = glm::vec3(88, 128, 16);
  this->home = glm::vec2(216, 0);
}

Clyde::Clyde(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->distanceToPacman = 0;
  this->position = glm::vec3(120, 128, 16);
  this->home = glm::vec2(0, 0);
}

void Blinky::updatePosition(float delta) {
  // TODO: implement
}

void Pinky::updatePosition(float delta) {
  // TODO: implement
}

void Inky::updatePosition(float delta) {
  // TODO: implement
}

void Clyde::updatePosition(float delta) {
  // TODO: implement
}

void Clyde::updateDistanceToPacman() {
  // TODO: implement
}
