#include "ghost.hpp"

/**** private methods ****/
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

  if (this->maze->isDoor(block)) {
    if (this->direction == down) {
      this->isHome = true;
      this->useDoor = true;
    }
  }

  if (fabs(this->target.x - center.x) <= 0.01f &&
      fabs(this->target.y - center.y) <= 0.01f) {
    this->isHome = false;
    this->target = this->home;
    this->direction = right;
    this->useDoor = false;
  }

  // TODO: similar logic for entering house
  // if (fabs(this->target.x - center.x) <= 0.01f &&
  //     fabs(this->target.y - center.y) <= 0.01f) {
  //   this->isHome = false;
  //   this->target = this->home;
  //   this->direction = right;
  //   this->useDoor = false;
  // }
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

  if (this->mode != frightened) {
    float min = INFINITY;
    for (int i = 0; i < 4; i++) {
      if (distances[i] >= 0 && distances[i] - min <= 0.01f) {
        min = distances[i];
        this->setOrientation((orientation)i);
      }
    }
  } else {
    int randomDirection;
    do {
      randomDirection = rand() % 4;
    } while (distances[randomDirection] != -1);
    this->setOrientation((orientation)randomDirection);
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

bool Ghost::isBelowDoor() {
  glm::vec2 center = this->maze->getCenter(this->getPosition());
  if (fabs(center.x - this->target.x) <= 0.01f) {
    return true;
  }
  return false;
}

/**** public methods ****/
void Ghost::setMode(behaviour mode) { Ghost::mode = mode; }

void Ghost::setIsHome(bool isHome) { this->isHome = isHome; }

void Ghost::setUseDoor(bool door) { this->useDoor = door; }

glm::vec3 Ghost::getPosition() { return this->position; }

void Ghost::setOrientation(orientation direction) {
  this->direction = direction;
}

/**** constructors ****/
behaviour Ghost::mode = scatter;

const char *Ghost::personality[4] = {"blinky", "pinky", "inky", "clyde"};

Ghost::Ghost(Pacman *pacman, Maze *maze) {
  this->pacman = pacman;
  this->maze = maze;
}

Ghost::~Ghost() {}

Blinky::Blinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->position = glm::vec3(104, 84, 16);
  this->home = glm::vec2(204, -20);
  this->target = this->home;
  this->direction = right;
  this->useDoor = false;
  this->isHome = false;
}

Pinky::Pinky(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->position = glm::vec3(104, 104, 16);
  this->target = glm::vec2(112, 92);
  this->home = glm::vec2(20, -20);
  this->direction = up;
  this->useDoor = true;
  this->isHome = true;
}

Inky::Inky(Pacman *pacman, Maze *maze, Ghost *blinky) : Ghost(pacman, maze) {
  this->blinky = (Blinky *)blinky;
  this->position = glm::vec3(88, 104, 16);
  this->target = glm::vec2(112, 92);
  this->home = glm::vec2(220, 260);
  this->direction = right;
  this->useDoor = true;
  this->isHome = true;
}

Clyde::Clyde(Pacman *pacman, Maze *maze) : Ghost(pacman, maze) {
  this->aroundPacman = true;
  this->position = glm::vec3(120, 104, 16);
  this->target = glm::vec2(112, 92);
  this->home = glm::vec2(4, 260);
  this->direction = left;
  this->useDoor = true;
  this->isHome = true;
}

void Blinky::updateTarget() {
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
}

void Pinky::updateTarget() {
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
}

void Inky::updateTarget() {
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
}

void Clyde::updateTarget() {
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
