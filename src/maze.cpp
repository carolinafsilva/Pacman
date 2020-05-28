#include "maze.hpp"

glm::vec2 Maze::getCenter(glm::vec3 position) {
  return glm::vec2(position.x + position.z / 2, position.y + position.z / 2);
}

glm::ivec2 Maze::getBlock(glm::vec2 center) {
  int c = floor(center.x / 8);
  int l = BLOCK_L * 8 - floor(center.y / 8);
  return glm::ivec2(l, c);
}

glm::ivec2 Maze::blockUp(glm::ivec2 block) {
  int c = block.x;
  int l = block.y - 1;
  return glm::ivec2(l, c);
}

glm::ivec2 Maze::blockLeft(glm::ivec2 block) {
  int c = block.x - 1;
  int l = block.y;
  return glm::ivec2(l, c);
}

glm::ivec2 Maze::blockDown(glm::ivec2 block) {
  int c = block.x;
  int l = block.y + 1;
  return glm::ivec2(l, c);
}

glm::ivec2 Maze::blockRight(glm::ivec2 block) {
  int c = block.x;
  int l = block.y;
  return glm::ivec2(l, c + 1);
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

float Maze::euclidianDist(glm::vec3 position1, glm::vec3 position2) {
  glm::vec2 center1 = Maze::getCenter(position1);
  glm::vec2 center2 = Maze::getCenter(position2);

  return sqrtf(powf(center1.x - center2.x, 2) + powf(center1.y - center2.y, 2));
}

void Maze::movePacman(glm::vec3 position) {}

void Maze::moveGhost(glm::vec3 position) {}

Maze::Maze() { this->numberOfDotsRemaining = 240; }
