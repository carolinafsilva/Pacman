#include "pacman.hpp"

Pacman::Pacman(Maze *maze) {
  this->maze = maze;
  this->direction = left;
  this->position = glm::vec3(104, 180, 16);

  this->lives = 4;
}

Pacman::~Pacman() {}

orientation Pacman::getOrientation() { return this->direction; }

glm::vec3 Pacman::getPosition() { return this->position; }

int Pacman::getLives() { return this->lives; }

void Pacman::updatePosition(float delta) {
  // FIXME: Dont enter walls
  // Calculate next position
  glm::vec3 nextPosition;
  switch (this->direction) {
    case up:
      nextPosition = glm::vec3(this->position.x, this->position.y + delta,
                               this->position.z);
      break;
    case left:
      nextPosition = glm::vec3(this->position.x - delta, this->position.y,
                               this->position.z);
      break;
    case down:
      nextPosition = glm::vec3(this->position.x, this->position.y - delta,
                               this->position.z);
      break;
    case right:
      nextPosition = glm::vec3(this->position.x + delta, this->position.y,
                               this->position.z);
      break;
  }
  // if next position is valid, move there
  glm::vec2 center = this->maze->getCenter(nextPosition);
  glm::ivec2 block = this->maze->pixelToBlock(center);
  if (this->maze->valid(block)) {
    this->position = nextPosition;
  }
}

void Pacman::setOrientation(orientation direction) {
  this->direction = direction;
}
