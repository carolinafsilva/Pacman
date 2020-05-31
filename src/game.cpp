#include "game.hpp"

// -----------------------------------------------------------------------------
// Private methods

void Game::processInput(Window *window, Pacman *pacman) {
  if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    if (Game::state != pause) {
      Game::state = pause;
    } else {
      Game::state = active;
    }
  }

  if (Game::state == active) {
    if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS ||
        glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
      pacman->setOrientation(up);
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS ||
        glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
      pacman->setOrientation(left);
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS ||
        glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
      pacman->setOrientation(down);
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS ||
        glfwGetKey(window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
      pacman->setOrientation(right);
    }
  }

  if (Game::state == pause) {
    if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS ||
        glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
      // Select menu item up
    }
    if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS ||
        glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
      // Select menu item down
    }
  }
}

bool Game::processExit(Window *window) {
  return !glfwWindowShouldClose(window->getWindow());
}

void Game::setMode(long long seconds, long long timer) {
  this->checkDuration(seconds);
  this->checkEnergyzer(timer);
}

void Game::checkDuration(long long seconds) {
  // wave 1
  if (seconds == 0 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 0) {
    Ghost::setMode(scatter);
    this->modeTracker += 1;
  }
  if (seconds == 7 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 1) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
    }
    Ghost::setMode(chase);
    this->modeTracker += 1;
  }
  // wave 2
  if (seconds == 27 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 2) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
    }
    Ghost::setMode(scatter);
    this->modeTracker += 1;
  }
  if (seconds == 34 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 3) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
    }
    Ghost::setMode(chase);
    this->modeTracker += 1;
  }
  // wave 3
  if (seconds == 54 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 4) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
    }
    Ghost::setMode(scatter);
    this->modeTracker += 1;
  }
  if (seconds == 59 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 5) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
    }
    Ghost::setMode(chase);
    this->modeTracker += 1;
  }
  // wave 4
  if (seconds == 79 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 6) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
    }
    Ghost::setMode(scatter);
    this->modeTracker += 1;
  }
  if (seconds == 84 + START_STATE + ENERGYZER_TIME * this->energyzerEaten &&
      this->modeTracker == 7) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
    }
    Ghost::setMode(chase);
    this->modeTracker += 1;
  }
}

void Game::checkEnergyzer(long long timer) {
  if (timer <= ENERGYZER_TIME && this->energyzerEaten > 0) {
    if (this->lastModeTracker == false) {
      this->lastMode = Ghost::getMode();
    }
    this->lastModeTracker = true;
    Ghost::setMode(frightened);
  } else if (this->lastModeTracker) {
    this->lastModeTracker = false;
    Ghost::setMode(this->lastMode);
  }
}

void Game::checkColision() {
  glm::vec2 pacmanCenter = this->maze->getCenter(this->pacman->getPosition());
  glm::vec2 ghostCenter;

  for (Ghost *ghost : ghosts) {
    ghostCenter = this->maze->getCenter(ghost->getPosition());

    if (ghostCenter.x == pacmanCenter.x &&
            fabs(ghostCenter.y - pacmanCenter.y) <= 8.0f ||
        ghostCenter.y == pacmanCenter.y &&
            fabs(ghostCenter.x - pacmanCenter.x) <= 8.0f) {
      if (Ghost::getMode() != frightened && !ghost->isDead()) {
        this->startTime = std::chrono::steady_clock::now();
        this->energyzerEaten = 0;
        this->modeTracker = 0;

        this->pacman->setIsDead(true);
      } else {
        ghost->setDead(true);
      }
    }
  }
}

// -----------------------------------------------------------------------------
// Public methods

void Game::setup() {
  // set random seed
  srand(time(NULL));
  // initialize window
  this->window->initialize();
  this->window->transferDataToGPUMemory();
}

void Game::run() {
  do {
    // process input
    processInput(this->window, pacman);

    if (Game::state != pause) {
      // get seconds since start
      long long seconds = std::chrono::duration_cast<std::chrono::seconds>(
                              std::chrono::steady_clock::now() - startTime)
                              .count();
      // Start
      while (seconds <= START_STATE) {
        // set state
        Game::state = start;

        // get seconds since start
        seconds = std::chrono::duration_cast<std::chrono::seconds>(
                      std::chrono::steady_clock::now() - startTime)
                      .count();

        // render window
        this->window->render(Game::state);
      }

      // set state
      Game::state = active;

      // update positions
      this->pacman->updatePosition(1.0f);
      for (Ghost *ghost : ghosts) {
        ghost->updatePosition(1.0f);
      }

      // handle colisions
      this->checkColision();

      // consume points
      glm::vec2 center = this->maze->getCenter(this->pacman->getPosition());
      glm::ivec2 block = this->maze->pixelToBlock(center);

      int points = this->maze->eat(block);

      if (points > 0) {
        this->score += points;
        this->maze->decrementDotsRemaining();
        if (points == 50) {
          this->lastEnergyzerTime = std::chrono::steady_clock::now();
          for (Ghost *ghost : this->ghosts) {
            ghost->turnAround();
          }
          this->energyzerEaten += 1;
        }
      }

      // get seconds since enegizer eaten
      long long timer =
          std::chrono::duration_cast<std::chrono::seconds>(
              std::chrono::steady_clock::now() - lastEnergyzerTime)
              .count();

      // set mode
      this->setMode(seconds, timer);

      // render window
      this->window->render(Game::state);

      // handle pacman death
      if (this->pacman->isDead()) {
        // reset pacman
        this->pacman->reset();
        this->pacman->setIsDead(false);
        this->pacman->decrementLives();
        // reset ghosts
        for (Ghost *ghost : ghosts) {
          ghost->reset();
        }
      }

    } else {
      // render window
      this->window->render(Game::state);
    }

  } while (processExit(this->window) && !(this->maze->getDotsRemaining() == 0 ||
                                          this->pacman->getLives() == 0));

  do {
    // set state
    Game::state = over;

    // render window
    this->window->render(Game::state);

  } while (processExit(this->window));
}

void Game::clean() {
  this->window->deleteDataFromGPUMemory();
  this->window->terminate();
}

// -----------------------------------------------------------------------------
// Initialization

gameState Game::state = active;

// -----------------------------------------------------------------------------
// Constructors

Game::Game() {
  this->maze = new Maze();

  this->pacman = new Pacman(this->maze);

  this->ghosts.push_back(new Blinky(this->pacman, this->maze));
  this->ghosts.push_back(new Pinky(this->pacman, this->maze));
  this->ghosts.push_back(new Inky(this->pacman, this->maze, this->ghosts[0]));
  this->ghosts.push_back(new Clyde(this->pacman, this->maze));

  this->window =
      new Window(this->maze, this->pacman, this->ghosts, this->startTime,
                 &(this->lastEnergyzerTime), &(this->score));

  this->startTime = std::chrono::steady_clock::now();
  this->lastEnergyzerTime = std::chrono::steady_clock::now();

  this->modeTracker = 0;
  this->lastModeTracker = false;

  this->energyzerEaten = 0;

  this->score = 0;
}

Game::~Game() {}
