#include "game.hpp"

#include "input.hpp"

void Game::setup() {
  // set random seed
  srand(time(NULL));
  this->window->initialize();
  this->window->transferDataToGPUMemory();
}

void Game::run() {
  // save starting time
  this->start_time = std::chrono::steady_clock::now();

  do {
    // get seconds since start
    long long seconds = std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::steady_clock::now() - start_time)
                            .count();

    // process input
    processInput(this->window, pacman);

    this->pacman->updatePosition(1.0f);

    // consume points
    glm::vec2 center = this->maze->getCenter(this->pacman->getPosition());
    glm::ivec2 block = this->maze->pixelToBlock(center);
    this->score += this->maze->eat(block);

    for (Ghost *ghost : ghosts) {
      ghost->updatePosition(1.0f);
    }

    // TODO: update game state
    this->setMode(seconds);
    this->checkColision();

    // render
    this->window->render();

  } while (processExit(this->window));
}

void Game::setMode(long long seconds) {
  // wave 1
  if (seconds == 0 && this->mode_tracker == 0) {
    for (Ghost *ghost : this->ghosts) {
      ghost->setMode(scatter);
    }
    this->mode_tracker += 1;
  }
  if (seconds == 7 && this->mode_tracker == 1) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
      ghost->setMode(chase);
    }
    this->mode_tracker += 1;
  }
  // wave 2
  if (seconds == 27 && this->mode_tracker == 2) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
      ghost->setMode(scatter);
    }
    this->mode_tracker += 1;
  }
  if (seconds == 34 && this->mode_tracker == 3) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
      ghost->setMode(chase);
    }
    this->mode_tracker += 1;
  }
  // wave 3
  if (seconds == 54 && this->mode_tracker == 4) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
      ghost->setMode(scatter);
    }
    this->mode_tracker += 1;
  }
  if (seconds == 59 && this->mode_tracker == 5) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
      ghost->setMode(chase);
    }
    this->mode_tracker += 1;
  }
  // wave 4
  if (seconds == 79 && this->mode_tracker == 6) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
      ghost->setMode(scatter);
    }
    this->mode_tracker += 1;
  }
  if (seconds == 84 && this->mode_tracker == 7) {
    for (Ghost *ghost : this->ghosts) {
      ghost->turnAround();
      ghost->setMode(chase);
    }
    this->mode_tracker += 1;
  }
}

void Game::checkColision() {
  if (Ghost::getMode() != frightened) {
    glm::vec2 pacmanCenter = this->maze->getCenter(this->pacman->getPosition());
    glm::ivec2 pacmanBlock = this->maze->pixelToBlock(pacmanCenter);
    glm::vec2 ghostCenter;
    glm::ivec2 ghostBlock;
    for (Ghost *ghost : ghosts) {
      ghostCenter = this->maze->getCenter(ghost->getPosition());
      ghostBlock = this->maze->pixelToBlock(ghostCenter);
      if (ghostBlock.x == pacmanBlock.x && ghostBlock.y == pacmanBlock.y) {
        this->pacman->setIsDead(true);
      }
    }
  }
}

void Game::clean() {
  this->window->deleteDataFromGPUMemory();
  this->window->terminate();
}

Game::Game() {
  this->maze = new Maze();

  this->pacman = new Pacman(this->maze);

  this->ghosts.push_back(new Blinky(this->pacman, this->maze));
  this->ghosts.push_back(new Pinky(this->pacman, this->maze));
  this->ghosts.push_back(new Inky(this->pacman, this->maze, this->ghosts[0]));
  this->ghosts.push_back(new Clyde(this->pacman, this->maze));

  this->window = new Window(this->maze, this->pacman, this->ghosts);

  this->mode_tracker = 0;
  this->score = 0;
}
