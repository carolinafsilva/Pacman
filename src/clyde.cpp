#include "clyde.hpp"

Clyde::Clyde(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->name = "clyde";
  this->aroundPacman = true;
  this->position = glm::vec3(120, 104, 16);
  this->target = this->homeExit;
  this->home = glm::vec2(4, 260);
  this->direction = left;
  this->useDoor = true;
  this->isHome = true;
}

void Clyde::updateTarget() {
  if (!this->dead) {
    switch (this->mode) {
      case scatter:
        this->target = this->home;
        break;
      case chase:
        this->checkDistanceToPacman();
        if (this->aroundPacman) {
          this->target = this->home;
        } else {
          this->target = this->maze->getCenter(this->pacman->getPosition());
        }
        break;
      case frightened:
        break;
    }
  } else {
    this->target = this->homeExit;
  }
}

void Clyde::checkDistanceToPacman() {
  glm::vec3 originalPosition = this->position;
  orientation originalDirection = this->direction;

  glm::vec2 pacmanCenter = this->maze->getCenter(this->pacman->getPosition());
  glm::ivec2 pacmanBlock = this->maze->pixelToBlock(pacmanCenter);

  glm::vec2 center;
  glm::ivec2 block;
  this->aroundPacman = false;
  int moves = 8;
  while (moves > 0) {
    updateDirection();
    move(8.0f);
    center = this->maze->getCenter(this->position);
    block = this->maze->pixelToBlock(center);
    if (block.x == pacmanBlock.x && block.y == pacmanBlock.y) {
      this->aroundPacman = true;
      break;
    }
    moves -= 1;
  }

  this->position = originalPosition;
  this->direction = originalDirection;
}

void Clyde::reset() {
  this->position = glm::vec3(120, 104, 16);
  this->target = glm::vec2(112, 92);
  this->direction = left;
  this->useDoor = true;
  this->isHome = true;
  this->dead = false;
}
