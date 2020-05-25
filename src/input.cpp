#include "input.hpp"

void processInput(Window *window, Pacman *pacman) {
  if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window->getWindow(), true);
  }
  if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS ||
      glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
    pacman->setOrientation(left);
  }
}

bool processExit(Window *window) {
  return glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         !glfwWindowShouldClose(window->getWindow());
}
