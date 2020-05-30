#include "pinky.hpp"

Pinky::Pinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->name = "pinky";
  this->position = glm::vec3(104, 104, 16);
  this->target = this->homeExit;
  this->home = glm::vec2(20, -20);
  this->direction = up;
  this->useDoor = true;
  this->isHome = true;
}

void Pinky::updateTarget() {
  if (!this->dead) {
    switch (this->mode) {
      case scatter:
        this->target = this->home;
        break;
      case frightened:
        break;
      case chase:
        glm::vec2 pacmanCenter =
            this->maze->getCenter(this->pacman->getPosition());
        orientation pacmanDirection = this->pacman->getOrientation();
        switch (pacmanDirection) {
          case up:
            this->target = glm::vec2(pacmanCenter.x, pacmanCenter.y + 4 * 8);
            break;
          case left:
            this->target = glm::vec2(pacmanCenter.x - 4 * 8, pacmanCenter.y);
            break;
          case down:
            this->target = glm::vec2(pacmanCenter.x, pacmanCenter.y - 4 * 8);
            break;
          case right:
            this->target = glm::vec2(pacmanCenter.x + 4 * 8, pacmanCenter.y);
            break;
        }
        break;
    }
  } else {
    this->target = this->homeExit;
  }
}

void Pinky::reset() {
  this->position = glm::vec3(104, 104, 16);
  this->target = glm::vec2(112, 92);
  this->direction = up;
  this->useDoor = true;
  this->isHome = true;
  this->dead = false;
}
