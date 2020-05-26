#include "maze.hpp"

coords *positionUp(coords *position) {
  coords *up = (coords *)malloc(sizeof(coords));
  up->x = position->x;
  up->y = position->y - 1;
  return up;
}
coords *positionLeft(coords *position) {
  coords *left = (coords *)malloc(sizeof(coords));
  left->x = position->x - 1;
  left->y = position->y;
  return left;
}
coords *positionDown(coords *position) {
  coords *down = (coords *)malloc(sizeof(coords));
  down->x = position->x;
  down->y = position->y + 1;
  return down;
}
coords *positionRight(coords *position) {
  coords *right = (coords *)malloc(sizeof(coords));
  right->x = position->x + 1;
  right->y = position->y;
  return right;
}

bool Maze::valid(coords *position) {
  if (position->x >= 0 && position->x < BOARD_X && position->y >= 0 &&
      position->y < BOARD_Y) {
    return this->matrix[position->x][position->y] != -1;
  }
  return false;
}

void Maze::zeroPosition(coords *position) {
  if (valid(position)) {
    this->matrix[position->x][position->y] = 0;
  }
}

void Maze::setPacmanPosition(coords *position) {}

void Maze::debugMatrix() {
  printf("\n");
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 28; j++) {
      if (this->matrix[i][j] == -1) {
        printf("\033[0;34m%3d\033[0m", this->matrix[i][j]);
      }
      if (this->matrix[i][j] == -2) {
        printf("\033[0;33m%3d\033[0m", this->matrix[i][j]);
      }
      if (this->matrix[i][j] == 0 || this->matrix[i][j] == 10) {
        printf("\033[0;32m%3d\033[0m", this->matrix[i][j]);
      }
      if (this->matrix[i][j] == 50) {
        printf("\033[1;31m%3d\033[0m", this->matrix[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

Maze::Maze() { this->numberOfDotsRemaining = 240; }
