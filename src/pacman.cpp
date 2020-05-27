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
      if (maze->valid(maze->Left(this->position))) {
        nextPosition = glm::vec3(this->position.x - delta, this->position.y,
                                 this->position.z);
      }
      break;
    case right:
      if (maze->valid(maze->Right(this->position))) {
        nextPosition = glm::vec3(this->position.x + delta, this->position.y,
                                 this->position.z);
      }
      break;
    case up:
      if (maze->valid(maze->Up(this->position))) {
        nextPosition = glm::vec3(this->position.x, this->position.y + delta,
                                 this->position.z);
      }
      break;
    case down:
      if (maze->valid(maze->Down(this->position))) {
        nextPosition = glm::vec3(this->position.x, this->position.y - delta,
                                 this->position.z);
      }
      break;
  }
}

void Pacman::setOrientation(orientation direction) {
  this->direction = direction;
}
