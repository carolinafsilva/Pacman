#include "ghost.hpp"

behaviour Ghost::mode = scatter;

Ghost::Ghost(Pacman *pacman, Maze *maze) {
  this->pacman = pacman;
  this->maze = maze;
  this->direction = left;
}

Ghost::~Ghost() {}

void Ghost::setMode(behaviour mode) { Ghost::mode = mode; }

glm::vec3 Ghost::getPosition() { return this->position; }

void Ghost::setTarget(glm::vec2 target) { this->target = target; }

Blinky::Blinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->position = glm::vec3(104, 148, 16);
  this->home = glm::vec2(4, 244);
}

Pinky::Pinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->position = glm::vec3(104, 128, 16);
  this->home = glm::vec2(220, 244);
}

Inky::Inky(Pacman *pacman, Maze *maze, Blinky *blinky) : Ghost(pacman, maze) {
  this->blinky = blinky;
  this->position = glm::vec3(88, 128, 16);
  this->home = glm::vec2(220, 4);
}

Clyde::Clyde(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->distanceToPacman = 0;
  this->position = glm::vec3(120, 128, 16);
  this->home = glm::vec2(4, 4);
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
