#include "maze.hpp"

glm::vec2 Maze::getCenter(glm::vec3 position) {
  return glm::vec2(position.x + position.z / 2, position.y + position.z / 2);
}

int Maze::getDotsRemaining() { return this->dotsRemaining; }
void Maze::decrementDotsRemaining() { this->dotsRemaining -= 1; }

glm::ivec2 Maze::pixelToBlock(glm::vec2 center) {
  int c = floor(center.x / 8);
  int l = floor(center.y / 8);
  return glm::ivec2(l, c);
}

glm::vec2 Maze::blockToPixel(glm::ivec2 block) {
  int x = block.y * 8 + 4;
  int y = block.x * 8 + 4;
  return glm::vec2(x, y);
}

glm::ivec2 Maze::blockNext(glm::ivec2 block, orientation direction) {
  int c, l;
  switch (direction) {
    case up:
      l = block.x - 1;
      c = block.y;
      break;
    case left:
      l = block.x;
      c = block.y - 1;
      break;
    case down:
      l = block.x + 1;
      c = block.y;
      break;
    case right:
      l = block.x;
      c = block.y + 1;
      break;
  }
  return glm::ivec2(l, c);
}

bool Maze::valid(glm::ivec2 block, bool door) {
  if (block.x >= 0 && block.x < BLOCK_L && block.y >= 0 && block.y < BLOCK_C) {
    return (door && this->isDoor(block)) || this->matrix[block.x][block.y] >= 0;
  }
  return false;
}

bool Maze::isDoor(glm::ivec2 block) {
  return this->matrix[block.x][block.y] == -2;
}

int Maze::eat(glm::ivec2 block) {
  int points = 0;
  if (valid(block, false)) {
    points = matrix[block.x][block.y];
    matrix[block.x][block.y] = 0;
  }
  return points;
}

int Maze::value(glm::ivec2 block) {
  int points = 0;
  if (valid(block, false)) {
    points = matrix[block.x][block.y];
  }
  return points;
}

float Maze::euclidianDist(glm::vec2 position1, glm::vec2 position2) {
  return sqrtf(powf(position1.x - position2.x, 2) +
               powf(position1.y - position2.y, 2));
}

glm::vec2 Maze::getTunnelLeft() { return this->tunnelLeft; }

glm::vec2 Maze::getTunnelRight() { return this->tunnelRight; };

void Maze::reset() {
  this->dotsRemaining = 244;
  for (int i = 0; i < BLOCK_L; i++) {
    for (int j = 0; j < BLOCK_C; j++) {
      this->matrix[i][j] = this->backup[i][j];
    }
  }
}

Maze::Maze() {
  this->dotsRemaining = 244;
  this->tunnelLeft = glm::vec2(-16, 108);
  this->tunnelRight = glm::vec2(224, 108);
  for (int i = 0; i < BLOCK_L; i++) {
    for (int j = 0; j < BLOCK_C; j++) {
      this->backup[i][j] = this->matrix[i][j];
    }
  }
}
