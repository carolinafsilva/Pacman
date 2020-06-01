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

enum gameState { start, active, pause, over, win };

#define SCREEN_WIDTH 224
#define SCREEN_HEIGHT 288

#define MAZE_WIDTH 224
#define MAZE_HEIGHT 248
#define HEADER_HEIGHT 24

#define PACMAN_SHEET 4
#define GHOST_SHEET 4

#define MAZE_DURATION 500
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
  static float proportion;
  static glm::vec2 mazeProportion;
  static float headerProportion;
  int *score;
  int *menuItem;
  static int width, height;
  int maze_height;
  int header_height;
  int lives_height;
  int new_width;
  glm::vec3 highlightColor;

  std::chrono::steady_clock::time_point lastTime;
  std::chrono::steady_clock::time_point *lastEnergyzerTime;
  std::chrono::steady_clock::time_point now;

  void transferTextures();

  void draw(std::string textureName, glm::vec2 position, glm::vec2 size,
            float rotation = 0.0f, int totalSprites = 1, int spriteNumber = 0);
  void drawLives();
  void drawHeader();
  void drawPoints();
  void drawMaze();
  void drawMazeWin();
  void drawMenu();
  void drawPacmanStart();
  void drawPacmanAnimation();
  void drawGhosts();

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  void prettyPrintScore();

 public:
  GLFWwindow *getWindow();

  void initialize();
  void transferDataToGPUMemory();
  void render(gameState state);
  void deleteDataFromGPUMemory();
  void terminate();

  Window(Maze *maze, Pacman *pacman, std::vector<Ghost *> &ghosts,
         std::chrono::steady_clock::time_point startTime,
         std::chrono::steady_clock::time_point *lastEnergyzerTime, int *score,
         int *menuItem);
};

#endif
