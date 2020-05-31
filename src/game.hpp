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

#define START_STATE 1

class Game {
 private:
  // ---------------------------------------------------------------------------
  // Attributes
  static gameState state;

  Window *window;

  Maze *maze;

  Pacman *pacman;
  std::vector<Ghost *> ghosts;

  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point lastEnergyzerTime;

  int ghostMultiplyer;

  int modeTracker;
  bool lastModeTracker;
  behaviour lastMode;

  int energyzerEaten;

  int score;

  static int menuItem;

  // ---------------------------------------------------------------------------
  // Methods
  static void handleKeyboardInput(GLFWwindow *window, int key, int scancode,
                                  int action, int mods);

  void processInput(Window *window, Pacman *pacman);
  bool processExit(Window *window);

  void setMode(long long seconds, long long timer);
  void checkDuration(long long seconds);
  void checkEnergyzer(long long timer);
  void checkColision();
  void resetGame();

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
