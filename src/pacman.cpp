#include "pacman.hpp"

// -----------------------------------------------------------------------------
// Private methods

bool Pacman::inTunnel() {
  glm::vec2 tunnel = this->maze->getTunnelLeft();
  // glm::vec2 tunnelRight = this->maze->getTunnelRight();
  if (this->direction == left && this->position.y == tunnel.y &&
      this->position.x < 44) {
    return true;
  }

  if (this->direction == right && this->position.y == tunnel.y &&
      this->position.x > 180) {
    return true;
  }

  return false;
}

void Pacman::checkTunnel() {
  glm::vec2 tunnel;
  glm::vec2 newPos;
  if (this->direction == left) {
    tunnel = this->maze->getTunnelLeft();
    if (fabs(this->position.x - tunnel.x) <= 0.001 &&
        fabs(this->position.y - tunnel.y) <= 0.001) {
      newPos = this->maze->getTunnelRight();
      this->position = glm::vec3(newPos.x, newPos.y, this->position.z);
    }
  } else if (this->direction == right) {
    tunnel = this->maze->getTunnelRight();
    if (fabs(this->position.x - tunnel.x) <= 0.001 &&
        fabs(this->position.y - tunnel.y) <= 0.001) {
      newPos = this->maze->getTunnelLeft();
      this->position = glm::vec3(newPos.x, newPos.y, this->position.z);
    }
  }
}

// -----------------------------------------------------------------------------
// Getters

orientation Pacman::getOrientation() { return this->direction; }

glm::vec3 Pacman::getPosition() { return this->position; }

int Pacman::getLives() { return this->lives; }

bool Pacman::isDead() { return this->dead; }

// -----------------------------------------------------------------------------
// Setters

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

void Pacman::setIsDead(bool dead) { this->dead = dead; }

// -----------------------------------------------------------------------------
// Methods

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

  bool inTunnel = this->inTunnel();

  if (inTunnel || !alligned || this->maze->valid(nextBlock, false)) {
    this->position = nextPosition;
  }

  this->checkTunnel();
}

void Pacman::decrementLives() { this->lives -= 1; }

void Pacman::reset(bool restart) {
  this->position = glm::vec3(104.0f, 180.0f, 16.0f);
  this->direction = left;
  if (restart) {
    this->lives = 4;
    this->dead = false;
  }
}

// -----------------------------------------------------------------------------
// Constructors

Pacman::Pacman(Maze *maze) {
  this->maze = maze;
  this->direction = left;
  this->position = glm::vec3(104.0f, 180.0f, 16.0f);

  this->lives = 4;
  this->dead = false;
}

Pacman::~Pacman() {}
