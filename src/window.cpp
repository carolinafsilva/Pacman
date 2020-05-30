#include "window.hpp"

GLFWwindow *Window::getWindow() { return this->window; }

void Window::transferTextures() {
  ResourceManager::LoadTexture("assets/images/maze.png", true, "maze");
  ResourceManager::LoadTexture("assets/images/Pacman_walking.gif", true,
                               "pacman");
  ResourceManager::LoadTexture("assets/images/Blinky_left.gif", true, "blinky");
  ResourceManager::LoadTexture("assets/images/Pinky_left.gif", true, "pinky");
  ResourceManager::LoadTexture("assets/images/Inky_left.gif", true, "inky");
  ResourceManager::LoadTexture("assets/images/Clyde_left.gif", true, "clyde");
  ResourceManager::LoadTexture("assets/images/frightened.gif", true,
                               "frightened");
  ResourceManager::LoadTexture("assets/images/eyes_left.png", true, "eyes");
  ResourceManager::LoadTexture("assets/images/foody_food.png", true, "food");
  ResourceManager::LoadTexture("assets/images/energyzer.png", true,
                               "energyzer");
}

void Window::draw(std::string textureName, glm::vec3 position) {
  Texture2D myTexture = ResourceManager::GetTexture(textureName);
  glm::vec2 topLeft(position.x, position.y);
  float size = position.z;
  SheetRenderer->DrawSprite(myTexture, topLeft, glm::vec2(size, size), 0.0f,
                            glm::vec3(1.0f, 1.0f, 1.0f), 1, 0);
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
  if (this->pacman->isDead()) {
    // reset pacman position
    this->pacman->reset();
    // reset ghosts position
    for (Ghost *ghost : ghosts) {
      ghost->reset();
    }
  } else {
    draw("pacman", this->pacman->getPosition());
    // Draw Ghosts
    for (int i = 0; i < 4; i++) {
      if (this->ghosts[i]->isDead()) {
        draw("eyes", this->ghosts[i]->getPosition());
      } else {
        if (Ghost::getMode() != frightened) {
          draw(Ghost::getPersonality()[i], this->ghosts[i]->getPosition());
        } else {
          draw("frightened", this->ghosts[i]->getPosition());
        }
      }
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

Window::Window(Maze *maze, Pacman *pacman, std::vector<Ghost *> &ghosts) {
  this->maze = maze;
  this->pacman = pacman;
  this->ghosts = ghosts;
}
