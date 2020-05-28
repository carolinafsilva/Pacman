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
  this->window = new Window();

  this->maze = new Maze();

  this->pacman = new Pacman(this->maze);

  this->blinky = new Blinky(this->pacman, this->maze);
  this->pinky = new Pinky(this->pacman, this->maze);
  this->inky = new Inky(this->pacman, this->maze, this->blinky);
  this->clide = new Clyde(this->pacman, this->maze);

  this->score = 0;
}
