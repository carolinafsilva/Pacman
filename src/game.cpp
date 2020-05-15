#include "game.hpp"

#include "input.hpp"

void Game::setup() {
  window->initialize();
  window->transferDataToGPUMemory();
}

void Game::run() {
  do {
    // process input

    // game logic

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

  this->pacman = new Pacman();

  this->blinky = new Blinky(this->pacman);
  this->pinky = new Pinky(this->pacman);
  this->inky = new Inky(this->pacman, this->blinky);
  this->clide = new Clyde(this->pacman);
}
