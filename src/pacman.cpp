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
      nextPosition = glm::vec3(this->position.x - delta, this->position.y,
                               this->position.z);
      if (maze->valid(maze->Left(nextPosition))) {
        this->position = nextPosition;
      }
      break;
    case right:
      nextPosition = glm::vec3(this->position.x + delta, this->position.y,
                               this->position.z);
      if (maze->valid(maze->Right(nextPosition))) {
        this->position = nextPosition;
      }
      break;
    case up:
      nextPosition = glm::vec3(this->position.x, this->position.y + delta,
                               this->position.z);
      if (maze->valid(maze->Up(nextPosition))) {
        this->position = nextPosition;
      }
      break;
    case down:
      nextPosition = glm::vec3(this->position.x, this->position.y - delta,
                               this->position.z);
      if (maze->valid(maze->Down(nextPosition))) {
        this->position = nextPosition;
      }
      break;
  }
}

void Pacman::setOrientation(orientation direction) {
  this->direction = direction;
}
