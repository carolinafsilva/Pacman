#include "window.hpp"

GLFWwindow *Window::getWindow() { return this->window; }

void Window::transferTextures() {
  ResourceManager::LoadTexture("assets/images/menu.png", true, "menu");
  ResourceManager::LoadTexture("assets/images/maze.png", true, "maze");
  ResourceManager::LoadTexture("assets/images/maze_flash.png", true,
                               "maze_flash");
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
  ResourceManager::LoadTexture("assets/images/Pacman.png", true, "life");
  ResourceManager::LoadTexture("assets/images/Pacman_start.png", true,
                               "pacman_start");
  ResourceManager::LoadTexture("assets/images/maze_win.png", true, "maze_win");
}

void Window::draw(std::string textureName, glm::vec2 position, glm::vec2 size,
                  float rotation, int totalSprites, int spriteNumber) {
  Texture2D myTexture = ResourceManager::GetTexture(textureName);
  SheetRenderer->DrawSprite(myTexture, position, size, rotation,
                            glm::vec3(1.0f, 1.0f, 1.0f), totalSprites,
                            spriteNumber);
}

void Window::drawLives() {
  glViewport((this->width - this->new_width) / 2, 0, this->new_width,
             this->lives_height);

  // Draw lives
  for (int i = 0; i < this->pacman->getLives() - 1; i++) {
    draw("life", glm::vec2(16 * i, 0.0), glm::vec2(16, MAZE_HEIGHT - 4));
  }
}

void Window::drawHeader() {
  glViewport((this->width - this->new_width) / 2,
             this->lives_height + this->maze_height, this->new_width,
             this->header_height);
  Text->RenderText("HIGH SCORE", 72.0f, 0.0f, glm::vec2(1.0 / 3, 3.0f));
  prettyPrintScore();
}

void Window::drawPoints() {
  for (int i = 0; i < BLOCK_L; i++) {
    for (int j = 0; j < BLOCK_C; j++) {
      glm::ivec2 block = glm::ivec2(i, j);
      if (this->maze->value(block) == 10) {
        glm::vec2 center = this->maze->blockToPixel(block);
        glm::vec2 position = glm::vec2(center.x - 4, center.y - 4);
        glm::vec2 size = glm::vec2(8, 8);
        draw("food", position, size);
      }
      if (this->maze->value(block) == 50) {
        glm::vec2 center = this->maze->blockToPixel(block);
        glm::vec2 position = glm::vec2(center.x - 4, center.y - 4);
        glm::vec2 size = glm::vec2(8, 8);
        draw("energyzer", position, size);
      }
    }
  }
}

void Window::drawMaze() {
  glViewport((this->width - this->new_width) / 2, this->lives_height,
             this->new_width, this->maze_height);
  Texture2D myTexture;
  myTexture = ResourceManager::GetTexture("maze");
  SheetRenderer->DrawSprite(myTexture, glm::vec2(0, 0),
                            glm::vec2((float)MAZE_WIDTH, (float)MAZE_HEIGHT),
                            0.0f, glm::vec3(1.0f, 1.0f, 1.0f), 1, 0);
}

void Window::drawMazeWin() {
  glViewport((this->width - this->new_width) / 2, this->lives_height,
             this->new_width, this->maze_height);
  Texture2D myTexture;
  myTexture = ResourceManager::GetTexture("maze_flash");
  SheetRenderer->DrawSprite(myTexture, glm::vec2(0, 0),
                            glm::vec2((float)MAZE_WIDTH, (float)MAZE_HEIGHT),
                            0.0f, glm::vec3(1.0f, 1.0f, 1.0f), 2, ghostSprite);
}

void Window::drawMenu() {
  glViewport(32.0 / MAZE_WIDTH * new_width + (this->width - new_width) / 2,
             this->lives_height + (32.0 / MAZE_HEIGHT * this->height),
             new_width - 32.0 / MAZE_WIDTH * new_width * 2,
             this->height - this->lives_height - header_height -
                 (32.0 / MAZE_HEIGHT * this->height * 2));
  Texture2D myTexture = ResourceManager::GetTexture("menu");
  SheetRenderer->DrawSprite(myTexture, glm::vec2(0.0f, 0.0f),
                            glm::vec2(MAZE_WIDTH, MAZE_HEIGHT));
  // Text->Load("assets/fonts/title.ttf", 24);
  Text->RenderText("PACMAN", 50.0f, 30.0f, glm::vec2(1.0f, 1.0f),
                   this->highlightColor);
  // Text->Load("assets/fonts/regular_text.ttf", 24);
  Text->RenderText("Resume", 50.0f, 110.0f, glm::vec2(0.625f, 0.8f));
  Text->RenderText("New Game", 50.0f, 150.0f, glm::vec2(0.625f, 0.8f));
  Text->RenderText("Exit", 50.0f, 190.0f, glm::vec2(0.625f, 0.8f));
  switch (*(this->menuItem)) {
    case 0:
      Text->RenderText("Resume", 50.0f, 110.0f, glm::vec2(0.625f, 0.8f),
                       this->highlightColor);
      break;
    case 1:
      Text->RenderText("New Game", 50.0f, 150.0f, glm::vec2(0.625f, 0.8f),
                       this->highlightColor);
      break;
    case 2:
      Text->RenderText("Exit", 50.0f, 190.0f, glm::vec2(0.625f, 0.8f),
                       this->highlightColor);
      break;
  }
}

void Window::drawPacmanAnimation() {
  float rotation;
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

  glm::vec2 position =
      glm::vec2(this->pacman->getPosition().x, this->pacman->getPosition().y);
  glm::vec2 size =
      glm::vec2(this->pacman->getPosition().z, this->pacman->getPosition().z);
  draw("pacman", position, size, rotation, PACMAN_SHEET, pacmanSprite);
}

void Window::drawPacmanStart() {
  Texture2D myTexture;
  myTexture = ResourceManager::GetTexture("pacman_start");
  glm::vec2 position =
      glm::vec2(this->pacman->getPosition().x, this->pacman->getPosition().y);
  glm::vec2 size =
      glm::vec2(this->pacman->getPosition().z, this->pacman->getPosition().z);

  SheetRenderer->DrawSprite(myTexture, position, size, 0.0f,
                            glm::vec3(1.0f, 1.0f, 1.0f));
}

void Window::drawGhosts() {
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
    glm::vec2 position = glm::vec2(this->ghosts[i]->getPosition().x,
                                   this->ghosts[i]->getPosition().y);
    glm::vec2 size = glm::vec2(this->ghosts[i]->getPosition().z,
                               this->ghosts[i]->getPosition().z);
    if (this->ghosts[i]->isDead()) {
      sprite = "eyes";
      draw(sprite.append(dir), position, size);
    } else {
      if (Ghost::getMode() != frightened) {
        sprite = Ghost::getPersonality()[i];
        draw(sprite.append(dir), position, size);
      } else {
        long long frightened_time =
            std::chrono::duration_cast<std::chrono::seconds>(
                this->now - *(this->lastEnergyzerTime))
                .count();
        if (frightened_time >= TIME_UNTIL_FLASH) {
          draw("frightened_flash", position, size, 0.0f, GHOST_SHEET,
               this->ghostSprite);
        } else {
          draw("frightened", position, size);
        }
      }
    }
  }
}
// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// -----------------------------------------------------------------------------
void Window::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina
  // displays.
  Window::width = width;
  Window::height = height;
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
  glm::mat4 projection = glm::ortho(0.0f, (float)(MAZE_WIDTH),
                                    (float)(MAZE_HEIGHT), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

  // set render-specific controls
  Shader myShader = ResourceManager::GetShader("sprite");
  SheetRenderer = new SpriteSheetRenderer(myShader);
  // load textures

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  transferTextures();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Text = new TextRenderer((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
  Text->Load("assets/fonts/regular_text.ttf", 24);
}

void Window::render(gameState state) {
  // MacOS retina screen fix
  glfwGetFramebufferSize(window, &(this->width), &(this->height));

  this->now = std::chrono::steady_clock::now();

  long long milliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(this->now -
                                                            this->lastTime)
          .count();

  // Clean window
  glClear(GL_COLOR_BUFFER_BIT);

  // update sizes
  maze_height = this->height * this->mazeProportion.y;
  header_height = this->height * this->headerProportion;
  lives_height = this->height - this->maze_height - this->header_height;
  new_width = this->height * this->proportion;

  if (state != win) {
    // Draw lies remaining
    drawLives();
    // Draw header
    drawHeader();
    // Draw Maze
    drawMaze();
    // Draw Points
    drawPoints();
  }

  switch (state) {
    case start:
      Text->RenderText("Ready!", 84.0f, 158.0f, glm::vec2(0.4f, 0.50f),
                       this->highlightColor);
      drawPacmanStart();
      drawGhosts();
      break;
    case active:
      if (!this->pacman->isDead()) {
        // Draw Pacman animation
        drawPacmanAnimation();
        // Draw Ghosts
        drawGhosts();
        if (milliseconds >= SPRITE_DURATION) {
          this->pacmanSprite = (this->pacmanSprite + 1) % PACMAN_SHEET;
          this->ghostSprite = (this->ghostSprite + 1) % GHOST_SHEET;
          this->lastTime = now;
        }
      }
      break;
    case pause:
      // Draw Pacman animation
      drawPacmanAnimation();
      // Draw Ghosts
      drawGhosts();
      drawMenu();
      break;
    case over:
      Text->RenderText("Game Over!", 76.0f, 158.0f, glm::vec2(0.3f, 0.50f),
                       this->highlightColor);
      break;
    case win:
      drawMazeWin();
      if (milliseconds >= MAZE_DURATION) {
        this->ghostSprite = (this->ghostSprite + 1) % 4;
        this->lastTime = now;
      }
      break;
  }

  // swap the color buffer
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Window::prettyPrintScore() {
  std::string score = std::to_string(*(this->score));
  Text->RenderText(score, 0.0f, 82.0f, glm::vec2(1.0 / 3, 3.0f));
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

glm::vec2 Window::mazeProportion = glm::vec2(
    (float)MAZE_WIDTH / SCREEN_WIDTH, (float)MAZE_HEIGHT / SCREEN_HEIGHT);
float Window::headerProportion = (float)HEADER_HEIGHT / SCREEN_HEIGHT;
float Window::proportion = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
int Window::width = SCREEN_WIDTH;
int Window::height = SCREEN_HEIGHT;
Window::Window(Maze *maze, Pacman *pacman, std::vector<Ghost *> &ghosts,
               std::chrono::steady_clock::time_point startTime,
               std::chrono::steady_clock::time_point *lastEnergyzerTime,
               int *score, int *menuItem) {
  this->maze = maze;
  this->pacman = pacman;
  this->ghosts = ghosts;
  this->lastTime = startTime;
  this->lastEnergyzerTime = lastEnergyzerTime;
  this->score = score;
  this->menuItem = menuItem;
  this->highlightColor = glm::vec3(1.0f, 1.0f, 0.0f);
  this->pacmanSprite = 0;
  this->ghostSprite = 0;
}
