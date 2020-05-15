#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "shader.hpp"

class Window {
 private:
  GLFWwindow *window;
  GLuint shaderProgram;
  unsigned int VBO, Maze_VAO, Pacman_VAO, EBO;

  const unsigned int SCR_WIDTH = 800;
  const unsigned int SCR_HEIGHT = 600;

  void transferPacman();
  void transferMaze();

  void drawPacman();
  void drawMaze();

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  static void processInput(GLFWwindow *window);

 public:
  void initialize();
  void transferDataToGPUMemory();
  void render();
  void deleteDataFromGPUMemory();
  void terminate();

  Window();
};

#endif
