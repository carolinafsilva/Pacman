#include "input.hpp"

void processInput(Window *window, Pacman *pacman) {
  if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window->getWindow(), true);
  }
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

bool processExit(Window *window) {
  return glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         !glfwWindowShouldClose(window->getWindow());
}
