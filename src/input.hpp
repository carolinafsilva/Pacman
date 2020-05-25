#ifndef INPUT_H
#define INPUT_H

#include "opengl.hpp"
#include "window.hpp"
#include "pacman.hpp"

void processInput(Window *window, Pacman *pacman);

bool processExit(Window *window);

#endif
