#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>

#include "maze.hpp"
#include "pacman.hpp"

#include "ghost.hpp"

#include "blinky.hpp"
#include "pinky.hpp"
#include "inky.hpp"
#include "clyde.hpp"

#include "window.hpp"

#define ENERGYZER_TIME 5

class Game {
 private:
  // ---------------------------------------------------------------------------
  // Attributes
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

  // ---------------------------------------------------------------------------
  // Methods
  void setMode(long long seconds, long long timer);
  void checkDuration(long long seconds);
  void checkEnergyzer(long long timer);
  void checkColision();

 public:
  // ---------------------------------------------------------------------------
  // Methods
  void setup();
  void run();
  void clean();

  // ---------------------------------------------------------------------------
  // Constructor

  Game();
  ~Game();
};

#endif
