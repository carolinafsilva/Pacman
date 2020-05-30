#include "blinky.hpp"

Blinky::Blinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->name = "blinky";
  this->position = glm::vec3(104, 84, 16);
  this->home = glm::vec2(204, -20);
  this->target = this->home;
  this->direction = right;
  this->useDoor = false;
  this->isHome = false;
}

void Blinky::updateTarget() {
  if (!this->dead) {
    switch (this->mode) {
      case scatter:
        this->target = this->home;
        break;
      case chase:
        this->target = this->maze->getCenter(this->pacman->getPosition());
        break;
      case frightened:
        break;
    }
  } else {
    this->target = this->homeExit;
  }
}

void Blinky::reset() {
  this->position = glm::vec3(104, 84, 16);
  this->direction = right;
  this->useDoor = false;
  this->isHome = false;
  this->dead = false;
}
