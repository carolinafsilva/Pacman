#include "ghost.hpp"

// -----------------------------------------------------------------------------
// Protected methods

void Ghost::move(float delta) {
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
  this->position = nextPosition;

  glm::vec2 center = this->maze->getCenter(this->position);
  glm::ivec2 block = this->maze->pixelToBlock(center);

  // inside house
  if (fabs(center.x - this->homeEntrance.x) <= 0.01f &&
      fabs(center.y - this->homeEntrance.y) <= 0.01f) {
    this->isHome = true;
    this->useDoor = true;
    this->dead = false;
  }

  // outside house
  if (fabs(this->target.x - this->homeExit.x) <= 0.01f &&
      fabs(this->target.y - this->homeExit.y) <= 0.01f) {
    // centered
    if (fabs(this->target.x - center.x) <= 0.01f &&
        fabs(this->target.y - center.y) <= 0.01f) {
      if (this->dead) {
        this->direction = down;
      } else {
        this->target = this->home;

        this->isHome = false;
        this->useDoor = false;

        if (this->name.compare("blinky") == 0) {
          this->direction = right;
        }
        if (this->name.compare("pinky") == 0) {
          this->direction = left;
        }
        if (this->name.compare("inky") == 0) {
          this->direction = right;
        }
        if (this->name.compare("clyde") == 0) {
          this->direction = left;
        }
      }
    }
  }

  this->checkTunnel();
}

orientation Ghost::oppositeDirection(orientation direction) {
  switch (direction) {
    case up:
      return down;
      break;
    case left:
      return right;
      break;
    case down:
      return up;
      break;
    case right:
      return left;
      break;
  }
}

void Ghost::updateDirection() {
  float distances[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
  checkNeighbours(distances);

  if (this->mode != frightened || this->dead) {
    float min = INFINITY;
    for (int i = 0; i < 4; i++) {
      if (distances[i] >= 0 && distances[i] - min < 0.01f) {
        min = distances[i];
        this->setOrientation((orientation)i);
      }
    }
  } else {
    bool flag = false;
    for (int i = 0; i < 4; i++) {
      if (distances[i] >= 0) {
        flag = true;
      }
    }

    if (flag) {
      int randomDirection;
      do {
        randomDirection = rand() % 4;
      } while (fabs(distances[randomDirection] + 1) <= 0.01);
      this->setOrientation((orientation)randomDirection);
    }
  }
}

void Ghost::checkNeighbours(float distances[]) {
  glm::vec2 ghostCenter = this->maze->getCenter(this->position);
  glm::ivec2 ghostBlock = this->maze->pixelToBlock(ghostCenter);
  glm::vec2 blockCenter = this->maze->blockToPixel(ghostBlock);
  orientation oppositeDir = this->oppositeDirection(this->direction);
  bool centered = fabs(ghostCenter.x - blockCenter.x) <= 0.01f &&
                  fabs(ghostCenter.y - blockCenter.y) <= 0.01f;

  glm::vec2 nextPos;
  glm::ivec2 testBlock;
  for (int i = 0; i < 4; i++) {
    testBlock = this->maze->blockNext(ghostBlock, (orientation)i);
    if (oppositeDir != (orientation)i &&
        ((this->isHome || centered) &&
         this->maze->valid(testBlock, this->useDoor))) {
      if (this->mode != frightened) {
        nextPos = this->maze->blockToPixel(testBlock);
        distances[i] = this->maze->euclidianDist(nextPos, this->target);
      } else {
        distances[i] = 1.0f;
      }
    }
  }
}

void Ghost::checkTunnel() {
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

bool Ghost::isBelowDoor() {
  glm::vec2 center = this->maze->getCenter(this->getPosition());
  if (fabs(center.x - this->target.x) <= 0.01f) {
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------
// Getters

std::vector<std::string> Ghost::getPersonality() { return Ghost::personality; }

behaviour Ghost::getMode() { return Ghost::mode; }

orientation Ghost::getOrientation() { return this->direction; }

glm::vec3 Ghost::getPosition() { return this->position; }

bool Ghost::isDead() { return this->dead; }

// -----------------------------------------------------------------------------
// Setters

void Ghost::setMode(behaviour mode) { Ghost::mode = mode; }

void Ghost::setOrientation(orientation direction) {
  this->direction = direction;
}

void Ghost::setIsHome(bool isHome) { this->isHome = isHome; }

void Ghost::setUseDoor(bool door) { this->useDoor = door; }

void Ghost::setDead(bool dead) { this->dead = dead; }

// -----------------------------------------------------------------------------
// Public methods

void Ghost::updatePosition(float delta) {
  if (!this->isHome) {
    this->updateTarget();
    this->updateDirection();
  } else {
    if (isBelowDoor()) {
      this->direction = up;
    }
  }
  this->move(delta);
}

void Ghost::turnAround() {
  if (!this->isDead()) {
    this->direction = this->oppositeDirection(this->direction);
  }
}

// -----------------------------------------------------------------------------
// Initialization

behaviour Ghost::mode = scatter;

std::vector<std::string> Ghost::personality =
    std::vector<std::string>({"blinky", "pinky", "inky", "clyde"});

// -----------------------------------------------------------------------------
// Constructors

Ghost::Ghost(Pacman *pacman, Maze *maze) {
  this->pacman = pacman;
  this->maze = maze;
  this->homeExit = glm::vec2(112, 92);
  this->homeEntrance = glm::vec2(112, 112);
  this->dead = false;
}

Ghost::~Ghost() {}
