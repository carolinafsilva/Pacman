#include "maze.hpp"

glm::vec2 Maze::getCenter(glm::vec3 position) {
  return glm::vec2(position.x + position.z / 2, position.y + position.z / 2);
}

glm::ivec2 Maze::pixelToBlock(glm::vec2 center) {
  int c = floor(center.x / 8);
  int l = (BLOCK_L - 1) - floor(center.y / 8);
  return glm::ivec2(l, c);
}

glm::vec2 Maze::blockToPixel(glm::ivec2 block) {
  int x = block.y * 8 + 4;
  int y = (BLOCK_L - 1 - block.x) * 8 + 4;
  return glm::vec2(x, y);
}

glm::ivec2 Maze::blockNext(glm::ivec2 block, orientation direction) {
  int c, l;
  switch (direction) {
    case up:
      c = block.x;
      l = block.y - 1;
      break;
    case left:
      c = block.x - 1;
      l = block.y;
      break;
    case down:
      c = block.x;
      l = block.y + 1;
      break;
    case right:
      c = block.x + 1;
      l = block.y;
      break;
  }
  return glm::ivec2(l, c);
}

bool Maze::valid(glm::ivec2 block) {
  if (block.x >= 0 && block.x < BLOCK_L && block.y >= 0 && block.y < BLOCK_C) {
    return this->matrix[block.x][block.y] >= 0;
  }
  return false;
}

int Maze::eat(glm::ivec2 block) {
  int points = 0;
  if (valid(block)) {
    points = matrix[block.x][block.y];
    matrix[block.x][block.y] = 0;
  }
  return points;
}

float Maze::euclidianDist(glm::vec2 position1, glm::vec2 position2) {
  return sqrtf(powf(position1.x - position2.x, 2) +
               powf(position1.y - position2.y, 2));
}

void Maze::movePacman(glm::vec3 position) {}

void Maze::moveGhost(glm::vec3 position) {}

Maze::Maze() { this->numberOfDotsRemaining = 240; }
