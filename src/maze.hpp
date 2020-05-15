#ifndef MAZE_H
#define MAZE_H

#define BOARD_X 31
#define BOARD_Y 28

struct coords {
  int x;
  int y;
};

class Maze {
 private:
  int matrix[BOARD_X][BOARD_Y];

 public:
  bool valid(coords p);
  Maze();
};

#endif
