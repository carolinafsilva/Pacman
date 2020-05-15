#include "ghost.hpp"

Ghost::Ghost(Pacman *pacman) { this->pacman = pacman; }

Blinky::Blinky(Pacman *pacman) : Ghost(pacman) {
  this->ignoreScatterLimit = 20;
}

Pinky::Pinky(Pacman *pacman) : Ghost(pacman) {}

Inky::Inky(Pacman *pacman, Blinky *blinky) : Ghost(pacman) {
  this->blinky = blinky;
}

Clyde::Clyde(Pacman *pacman) : Ghost(pacman) { this->distanceToPacman = 0; }
