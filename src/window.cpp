#include "window.hpp"

GLFWwindow *Window::getWindow() { return this->window; }

void Window::transferTextures() {
  ResourceManager::LoadTexture("assets/images/maze.png", true, "maze");
  ResourceManager::LoadTexture("assets/images/pacman_walking_sheet.png", true,
                               "pacman");
  ResourceManager::LoadTexture("assets/images/Blinky_left.gif", true,
                               "blinky_left");
  ResourceManager::LoadTexture("assets/images/Pinky_left.gif", true,
                               "pinky_left");
  ResourceManager::LoadTexture("assets/images/Inky_left.gif", true,
                               "inky_left");
  ResourceManager::LoadTexture("assets/images/Clyde_left.gif", true,
                               "clyde_left");
  ResourceManager::LoadTexture("assets/images/Blinky_right.gif", true,
                               "blinky_right");
  ResourceManager::LoadTexture("assets/images/Pinky_right.gif", true,
                               "pinky_right");
  ResourceManager::LoadTexture("assets/images/Inky_right.gif", true,
                               "inky_right");
  ResourceManager::LoadTexture("assets/images/Clyde_right.gif", true,
                               "clyde_right");
  ResourceManager::LoadTexture("assets/images/Blinky_up.gif", true,
                               "blinky_up");
  ResourceManager::LoadTexture("assets/images/Pinky_up.gif", true, "pinky_up");
  ResourceManager::LoadTexture("assets/images/Inky_up.gif", true, "inky_up");
  ResourceManager::LoadTexture("assets/images/Clyde_up.gif", true, "clyde_up");
  ResourceManager::LoadTexture("assets/images/Blinky_down.gif", true,
                               "blinky_down");
  ResourceManager::LoadTexture("assets/images/Pinky_down.gif", true,
                               "pinky_down");
  ResourceManager::LoadTexture("assets/images/Inky_down.gif", true,
                               "inky_down");
  ResourceManager::LoadTexture("assets/images/Clyde_down.gif", true,
                               "clyde_down");
  ResourceManager::LoadTexture("assets/images/frightened.gif", true,
                               "frightened");
  ResourceManager::LoadTexture("assets/images/frightened_flash.png", true,
                               "frightened_flash");
  ResourceManager::LoadTexture("assets/images/eyes_left.png", true,
                               "eyes_left");
  ResourceManager::LoadTexture("assets/images/eyes_up.png", true, "eyes_up");
  ResourceManager::LoadTexture("assets/images/eyes_down.png", true,
                               "eyes_down");
  ResourceManager::LoadTexture("assets/images/eyes_right.png", true,
                               "eyes_right");
  ResourceManager::LoadTexture("assets/images/foody_food.png", true, "food");
  ResourceManager::LoadTexture("assets/images/energyzer.png", true,
                               "energyzer");
}

void Window::draw(std::string textureName, glm::vec3 position, float rotation,
                  int totalSprites, int spriteNumber) {
  Texture2D myTexture = ResourceManager::GetTexture(textureName);
  glm::vec2 topLeft(position.x, position.y);
  float size = position.z;
  SheetRenderer->DrawSprite(myTexture, topLeft, glm::vec2(size, size), rotation,
                            glm::vec3(1.0f, 1.0f, 1.0f), totalSprites,
                            spriteNumber);
}

void Window::drawMaze() {
  Texture2D myTexture;
  myTexture = ResourceManager::GetTexture("maze");
  SheetRenderer->DrawSprite(
      myTexture, glm::vec2(0, 0),
      glm::vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT), 0.0f,
      glm::vec3(1.0f, 1.0f, 1.0f), 1, 0);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// -----------------------------------------------------------------------------
void Window::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina
  // displays.
  glViewport(0, 0, width, height);
}

void Window::initialize() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pacman", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLEW
  glewExperimental = true;  // Needed for core profile
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    glfwTerminate();
    exit(1);
  }

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::transferDataToGPUMemory() {
  // load shaders
  ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag",
                              nullptr, "sprite");

  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, (float)(SCREEN_WIDTH),
                                    (float)(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

  // set render-specific controls
  Shader myShader = ResourceManager::GetShader("sprite");
  SheetRenderer = new SpriteSheetRenderer(myShader);
  // load textures

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  transferTextures();
}

void Window::render() {
  // MacOS retina screen fix
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

  long long milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                            this->lastTime)
          .count();

  // Clean window
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw Maze
  drawMaze();

  // Draw Points
  for (int i = 0; i < BLOCK_L; i++) {
    for (int j = 0; j < BLOCK_C; j++) {
      glm::ivec2 block = glm::ivec2(i, j);
      if (this->maze->value(block) == 10) {
        glm::vec2 center = this->maze->blockToPixel(block);
        glm::vec3 position = glm::vec3(center.x - 4, center.y - 4, 8);
        draw("food", position);
      }
      if (this->maze->value(block) == 50) {
        glm::vec2 center = this->maze->blockToPixel(block);
        glm::vec3 position = glm::vec3(center.x - 4, center.y - 4, 8);
        draw("energyzer", position);
      }
    }
  }

  // Draw Pacman
  float rotation;
  if (!this->pacman->isDead()) {
    switch (this->pacman->getOrientation()) {
      case up:
        rotation = 90.0f;
        break;
      case left:
        rotation = 0.0f;
        break;
      case down:
        rotation = -90.0f;
        break;
      case right:
        rotation = 180.0f;
        break;
    }
    draw("pacman", this->pacman->getPosition(), rotation, PACMAN_SHEET,
         pacmanSprite);
    // Draw Ghosts
    for (int i = 0; i < 4; i++) {
      std::string dir;
      switch (this->ghosts[i]->getOrientation()) {
        case up:
          dir = "_up";
          break;
        case left:
          dir = "_left";
          break;
        case down:
          dir = "_down";
          break;
        case right:
          dir = "_right";
          break;
      }

      std::string sprite;
      if (this->ghosts[i]->isDead()) {
        sprite = "eyes";
        draw(sprite.append(dir), this->ghosts[i]->getPosition());
      } else {
        if (Ghost::getMode() != frightened) {
          sprite = Ghost::getPersonality()[i];
          draw(sprite.append(dir), this->ghosts[i]->getPosition());
        } else {
          long long frightened_time =
              std::chrono::duration_cast<std::chrono::seconds>(
                  now - *(this->lastEnergyzerTime))
                  .count();
          if (frightened_time >= TIME_UNTIL_FLASH) {
            draw("frightened_flash", this->ghosts[i]->getPosition(), 0.0f,
                 GHOST_SHEET, this->ghostSprite);
          } else {
            draw("frightened", this->ghosts[i]->getPosition());
          }
        }
      }
    }
    if (milliseconds >= SPRITE_DURATION) {
      this->pacmanSprite = (this->pacmanSprite + 1) % PACMAN_SHEET;
      this->ghostSprite = (this->ghostSprite + 1) % GHOST_SHEET;
      this->lastTime = now;
    }
  }

  // swap the color buffer
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Window::deleteDataFromGPUMemory() {
  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &Maze_VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);
}

void Window::terminate() { glfwTerminate(); }

Window::Window(Maze *maze, Pacman *pacman, std::vector<Ghost *> &ghosts,
               std::chrono::steady_clock::time_point startTime,
               std::chrono::steady_clock::time_point *lastEnergyzerTime) {
  this->maze = maze;
  this->pacman = pacman;
  this->ghosts = ghosts;
  this->lastTime = startTime;
  this->lastEnergyzerTime = lastEnergyzerTime;
  this->pacmanSprite = 0;
  this->ghostSprite = 0;
}
