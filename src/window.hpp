#ifndef WINDOW_H
#define WINDOW_H

#include "opengl.hpp"
#include "shader.hpp"
#include "pacman.hpp"
#include "ghost.hpp"
#include "resource_manager.hpp"
#include "sprite_sheet_renderer.hpp"

#include <vector>
#include <iostream>

#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 248

class Window {
 private:
  GLFWwindow *window;
  GLuint shaderProgram;
  Pacman *pacman;
  std::vector<Ghost *> ghosts;
  SpriteSheetRenderer *SheetRenderer;
  unsigned int VBO, Maze_VAO, Pacman_VAO, EBO;

  void transferTextures();

  void draw(std::string textureName, glm::vec3 position);
  void drawMaze();

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);

 public:
  GLFWwindow *getWindow();

  void initialize();
  void transferDataToGPUMemory();
  void render();
  void deleteDataFromGPUMemory();
  void terminate();

  Window(Pacman *pacman, std::vector<Ghost *> &ghosts);
};

#endif
