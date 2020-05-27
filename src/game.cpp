#include "game.hpp"

#include "input.hpp"

void Game::setup() {
  window->initialize();
  window->transferDataToGPUMemory();
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

void Game::debugMatrix() { this->maze->debugMatrix(); }

Game::Game() {
  this->window = new Window();

  this->maze = new Maze();

  this->pacman = new Pacman(maze);

  this->blinky = new Blinky(this->pacman);
  this->pinky = new Pinky(this->pacman);
  this->inky = new Inky(this->pacman, this->blinky);
  this->clide = new Clyde(this->pacman);
}
