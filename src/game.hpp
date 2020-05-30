#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>

#include "ghost.hpp"
#include "maze.hpp"
#include "pacman.hpp"
#include "window.hpp"

#define ENERGYZER_TIME 5

class Game {
 private:
  Window *window;

  Maze *maze;

  Pacman *pacman;
  std::vector<Ghost *> ghosts;

  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point lastEnergyzerTime;

  int score;
  int level;

  int modeTracker;

  bool lastModeTracker;
  behaviour lastMode;

  int energyzerEaten;

  void setMode(long long seconds, long long timer);
  void checkColision();

 public:
  void setup();
  void run();
  void clean();

  void debugMatrix();

  Game();
};

#endif
