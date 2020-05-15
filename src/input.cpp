#include "input.hpp"

void processInput(Window *window) {
  if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window->getWindow(), true);
}

bool processExit(Window *window) {
  return glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         !glfwWindowShouldClose(window->getWindow());
}
