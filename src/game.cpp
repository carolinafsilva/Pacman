#include "game.hpp"

#include "input.hpp"

void Game::setup() {
  window->initialize();
  window->transferDataToGPUMemory();
  srand(time(NULL));
}

void Game::run() {
  do {
    // process input
    processInput(this->window, pacman);

    // TODO: update positions (pacman + ghosts)
    pacman->updatePosition(1.0f);
    // for (Ghost *ghost : ghosts) {
    //   ghost->updatePosition(1.0f);
    // }
    ghosts[0]->updatePosition(1.0f);
    // TODO: update game state

    // render
    window->render();

  } while (processExit(this->window));
}

void Game::clean() {
  window->deleteDataFromGPUMemory();
  window->terminate();
}

Game::Game() {
  this->maze = new Maze();

  this->pacman = new Pacman(this->maze);

  ghosts.push_back(new Blinky(this->pacman, this->maze));
  ghosts.push_back(new Pinky(this->pacman, this->maze));
  ghosts.push_back(new Inky(this->pacman, this->maze, this->ghosts[0]));
  ghosts.push_back(new Clyde(this->pacman, this->maze));

  this->window = new Window(this->pacman, this->ghosts);

  this->score = 0;
}
