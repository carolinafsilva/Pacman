#include "inky.hpp"

Inky::Inky(Pacman *pacman, Maze *maze, Ghost *blinky) : Ghost(pacman, maze) {
  this->name = "inky";
  this->blinky = (Blinky *)blinky;
  this->position = glm::vec3(88, 104, 16);
  this->target = this->homeExit;
  this->home = glm::vec2(220, 260);
  this->direction = right;
  this->useDoor = true;
  this->isHome = true;
}

void Inky::updateTarget() {
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
        glm::vec2 blinkyCenter =
            this->maze->getCenter(this->blinky->getPosition());
        orientation pacmanDirection = this->pacman->getOrientation();
        glm::vec2 pivot;
        switch (pacmanDirection) {
          case up:
            pivot = glm::vec2(pacmanCenter.x, pacmanCenter.y + 2 * 8);
            break;
          case left:
            pivot = glm::vec2(pacmanCenter.x - 2 * 8, pacmanCenter.y);
            break;
          case down:
            pivot = glm::vec2(pacmanCenter.x, pacmanCenter.y - 2 * 8);
            break;
          case right:
            pivot = glm::vec2(pacmanCenter.x + 2 * 8, pacmanCenter.y);
            break;
        }
        glm::vec2 vectr(pivot.x - blinkyCenter.x, pivot.y - blinkyCenter.y);
        this->target = glm::vec2(pivot.x + vectr.x, pivot.y + vectr.y);
        break;
    }
  } else {
    this->target = this->homeExit;
  }
}

void Inky::reset() {
  this->position = glm::vec3(88, 104, 16);
  this->target = glm::vec2(112, 92);
  this->direction = right;
  this->useDoor = true;
  this->isHome = true;
  this->dead = false;
}
