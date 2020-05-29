#include "pacman.hpp"

Pacman::Pacman(Maze *maze) {
  this->maze = maze;
  this->direction = left;
  this->position = glm::vec3(104.0f, 180.0f, 16.0f);

  this->lives = 4;
}

Pacman::~Pacman() {}

orientation Pacman::getOrientation() { return this->direction; }

glm::vec3 Pacman::getPosition() { return this->position; }

int Pacman::getLives() { return this->lives; }

void Pacman::updatePosition(float delta) {
  // Calculate next position
  glm::vec3 nextPosition;
  switch (this->direction) {
    case up:
      nextPosition = glm::vec3(this->position.x, this->position.y - delta,
                               this->position.z);
      break;
    case left:
      nextPosition = glm::vec3(this->position.x - delta, this->position.y,
                               this->position.z);
      break;
    case down:
      nextPosition = glm::vec3(this->position.x, this->position.y + delta,
                               this->position.z);
      break;
    case right:
      nextPosition = glm::vec3(this->position.x + delta, this->position.y,
                               this->position.z);
      break;
  }
  // if next position is valid, move there
  glm::vec2 center = this->maze->getCenter(this->position);
  glm::ivec2 currentBlock = this->maze->pixelToBlock(center);
  glm::vec2 blockCenter = this->maze->blockToPixel(currentBlock);

  glm::ivec2 nextBlock = this->maze->blockNext(currentBlock, this->direction);

  bool alligned;
  if (this->direction == left || this->direction == right) {
    alligned = fabs(center.x - blockCenter.x) <= 0.01f;
  } else {
    alligned = fabs(center.y - blockCenter.y) <= 0.01f;
  }

  if (!alligned || this->maze->valid(nextBlock, false)) {
    this->position = nextPosition;
  }
}

void Pacman::setOrientation(orientation direction) {
  glm::vec2 center = this->maze->getCenter(this->position);
  glm::ivec2 currentBlock = this->maze->pixelToBlock(center);
  glm::vec2 blockCenter = this->maze->blockToPixel(currentBlock);

  glm::ivec2 nextBlock = this->maze->blockNext(currentBlock, direction);

  bool centered;
  centered = fabs(center.x - blockCenter.x) <= 0.01f &&
             fabs(center.y - blockCenter.y) <= 0.01f;

  if (centered && this->maze->valid(nextBlock, false)) {
    this->direction = direction;
  }
}
