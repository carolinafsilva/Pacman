#include "pacman.hpp"

Pacman::Pacman(Maze *maze) {
  this->maze = maze;
  this->direction = left;
  this->position = glm::vec3(104, 62, 16);

  this->lives = 4;
}

Pacman::~Pacman() {}

orientation Pacman::getOrientation() { return this->direction; }

glm::vec3 Pacman::getPosition() { return this->position; }

int Pacman::getLives() { return this->lives; }

void Pacman::updatePosition(float delta) {
  glm::vec3 nextPosition;
  switch (direction) {
    case left:
      nextPosition = maze->Left(nextPosition, delta);
      if (maze->valid(nextPosition)) {
        this->position = nextPosition;
      }
      break;
    case right:
      nextPosition = maze->Right(nextPosition, delta);
      if (maze->valid(nextPosition)) {
        this->position = nextPosition;
      }
      break;
    case up:
      nextPosition = maze->Up(nextPosition, delta);
      if (maze->valid(nextPosition)) {
        this->position = nextPosition;
      }
      break;
    case down:

      nextPosition = maze->Down(nextPosition, delta);
      if (maze->valid(nextPosition)) {
        this->position = nextPosition;
      }
      break;
  }
}

void Pacman::setOrientation(orientation direction) {
  this->direction = direction;
}
