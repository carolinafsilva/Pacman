#include "maze.hpp"

Maze::Maze() {}

void Maze::debugMatrix() {
  printf("\n");
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 28; j++) {
      if (this->matrix[i][j] == -1) {
        printf("\033[0;34m%3d\033[0m", this->matrix[i][j]);
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
