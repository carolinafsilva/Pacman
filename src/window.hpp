#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "shader.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Window {
 private:
  GLFWwindow *window;
  GLuint shaderProgram;
  unsigned int VBO, Maze_VAO, Pacman_VAO, EBO;

  void transferPacman();
  void transferMaze();

  void drawPacman();
  void drawMaze();

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  static void processInput(GLFWwindow *window);

 public:
  GLFWwindow *getWindow();

  void initialize();
  void transferDataToGPUMemory();
  void render();
  void deleteDataFromGPUMemory();
  void terminate();

  Window();
};

#endif
