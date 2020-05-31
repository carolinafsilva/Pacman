#ifndef WINDOW_H
#define WINDOW_H

#include "opengl.hpp"
#include "shader.hpp"
#include "maze.hpp"
#include "pacman.hpp"
#include "ghost.hpp"
#include "resource_manager.hpp"
#include "text_renderer.hpp"
#include "sprite_sheet_renderer.hpp"

#include <vector>
#include <iostream>

#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 288

#define MAZE_WIDTH 224
#define MAZE_HEIGHT 248

#define PACMAN_SHEET 4
#define GHOST_SHEET 4
#define SPRITE_DURATION 50
#define TIME_UNTIL_FLASH 3

class Window {
 private:
  GLFWwindow *window;
  GLuint shaderProgram;
  Pacman *pacman;
  Maze *maze;
  std::vector<Ghost *> ghosts;
  TextRenderer *Text;
  SpriteSheetRenderer *SheetRenderer;
  unsigned int VBO, Maze_VAO, Pacman_VAO, EBO;
  int pacmanSprite, ghostSprite;
  int *score;

  std::chrono::steady_clock::time_point lastTime;
  std::chrono::steady_clock::time_point *lastEnergyzerTime;

  void transferTextures();

  void draw(std::string textureName, glm::vec2 position, glm::vec2 size,
            float rotation = 0.0f, int totalSprites = 1, int spriteNumber = 0);
  void drawMaze();

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  void prettyPrintScore();

 public:
  GLFWwindow *getWindow();

  void initialize();
  void transferDataToGPUMemory();
  void render();
  void deleteDataFromGPUMemory();
  void terminate();

  Window(Maze *maze, Pacman *pacman, std::vector<Ghost *> &ghosts,
         std::chrono::steady_clock::time_point startTime,
         std::chrono::steady_clock::time_point *lastEnergyzerTime, int *score);
};

#endif
