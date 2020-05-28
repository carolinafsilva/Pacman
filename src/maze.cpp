#include "maze.hpp"

glm::vec3 Maze::Up(glm::vec3 position, float delta) {
  // FIXME: convert to matrix index
  // up.x = position.x;
  // up.y = position.y - 1;
  // return up;
}
glm::vec3 Maze::Left(glm::vec3 position, float delta) {
  // FIXME: convert to matrix index
  // left.x = position.x - 1;
  // left.y = position.y;
  // return left;
}
glm::vec3 Maze::Down(glm::vec3 position, float delta) {
  // FIXME: convert to matrix index
  // down.x = position.x;
  // down.y = position.y + 1;
  // return down;
}
glm::vec3 Maze::Right(glm::vec3 position, float delta) {
  // FIXME: convert to matrix index
  // right.x = position.x + 1;
  // right.y = position.y;
  // return right;
}

glm::vec2 Maze::getCenter(glm::vec3 position) {
  return glm::vec2(position.x + position.z / 2, position.y + position.z / 2);
}

float Maze::euclidianDist(glm::vec3 position1, glm::vec3 position2) {
  glm::vec2 center1 = Maze::getCenter(position1);
  glm::vec2 center2 = Maze::getCenter(position2);

  return sqrtf(powf(center1.x - center2.x, 2) + powf(center1.y - center2.y, 2));
}

bool Maze::valid(glm::vec3 position) {
  // if (position->x >= 0 && position->x < BOARD_X && position->y >= 0 &&
  //    position->y < BOARD_Y) {
  // FIXME: convert to matrix index
  // return this->matrix[position->x][position->y] != -1;
  //}
  return false;
}

void Maze::eat(glm::vec3 position) {
  if (valid(position)) {
    // FIXME: convert to matrix index
    // this->matrix[position.x][position.y] = 0;
  }
}

void Maze::movePacman(glm::vec3 position) {}

void Maze::moveGhost(glm::vec3 position) {}

Maze::Maze() { this->numberOfDotsRemaining = 240; }
