#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>

#include "ghost.hpp"
#include "maze.hpp"
#include "pacman.hpp"
#include "window.hpp"

class Game {
 private:
  Window *window;

  Maze *maze;

  Pacman *pacman;
  std::vector<Ghost *> ghosts;

  std::chrono::steady_clock::time_point start_time;

  int score;
  int mode_tracker;

  void setMode(long long seconds);
  void checkColision();

 public:
  void setup();
  void run();
  void clean();

  void debugMatrix();

  Game();
};

#endif
