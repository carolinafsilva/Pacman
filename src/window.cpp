#include "window.hpp"

GLFWwindow *Window::getWindow() { return this->window; }

void Window::transferPacman() {
  // Variable definition
  float step = 0.045f;
  float cx = 13.5f, cy = 8.5f;
  float radius = 1.0f;
  float theta_s = 0.0f;
  float theta_e = 360.0f;
  int size = (int)((theta_e - theta_s) / step) * 2;

  float vertices[size];
  for (int i = 0; i < size; i++) {
    vertices[i++] = cx + radius * cosf(theta_s);
    vertices[i] = cy + radius * sinf(theta_s);
    // g_vertex_buffer_data[i] = 0.0f;
    theta_s += step;
  }

  glGenVertexArrays(1, &Pacman_VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(Pacman_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void Window::transferMaze() {
  ResourceManager::LoadTexture("assets/images/maze.png", true, "maze");
  // float vertices[] = {
  //     0.0f, 0.0f, 0.0f,    // outer bottom left
  //     28.0f, 0.0f, 0.0f,   // outer bottom right
  //     1.0f, 1.0f, 0.0f,    // inner bottom left
  //     27.0f, 1.0f, 0.0f,   // inner bottom right
  //     1.0f, 5.0f, 0.0f,    // 4
  //     3.0f, 5.0f, 0.0f,    // 5
  //     3.0f, 7.0f, 0.0f,    // 6
  //     1.0f, 7.0f, 0.0f,    // 7
  //     1.0f, 11.0f, 0.0f,   // 8
  //     6.0f, 11.0f, 0.0f,   // 9
  //     6.0f, 16.0f, 0.0f,   // 10
  //     0.0f, 16.0f, 0.0f,   // 11
  //     0.0f, 15.0f, 0.0f,   // 12
  //     5.0f, 15.0f, 0.0f,   // 13
  //     5.0f, 12.0f, 0.0f,   // 14
  //     0.0f, 12.0f, 0.0f,   // 15
  //     27.0f, 5.0f, 0.0f,   // 16
  //     25.0f, 5.0f, 0.0f,   // 17
  //     25.0f, 7.0f, 0.0f,   // 18
  //     27.0f, 7.0f, 0.0f,   // 19
  //     27.0f, 11.0f, 0.0f,  // 20
  //     22.0f, 11.0f, 0.0f,  // 21
  //     22.0f, 16.0f, 0.0f,  // 22
  //     28.0f, 16.0f, 0.0f,  // 23
  //     28.0f, 15.0f, 0.0f,  // 24
  //     23.0f, 15.0f, 0.0f,  // 25
  //     23.0f, 12.0f, 0.0f,  // 26
  //     28.0f, 12.0f, 0.0f,  // 27

  //     2.0f, 2.0f, 0.0f,   // 28
  //     2.0f, 4.0f, 0.0f,   // 29
  //     12.0f, 2.0f, 0.0f,  // 30
  //     12.0f, 4.0f, 0.0f,  // 31
  //     7.0f, 4.0f, 0.0f,   // 32
  //     9.0f, 4.0f, 0.0f,   // 33
  //     7.0f, 7.0f, 0.0f,   // 34
  //     9.0f, 7.0f, 0.0f,   // 35

  //     26.0f, 2.0f, 0.0f,  // 36
  //     26.0f, 4.0f, 0.0f,  // 37
  //     16.0f, 2.0f, 0.0f,  // 38
  //     16.0f, 4.0f, 0.0f,  // 39
  //     21.0f, 4.0f, 0.0f,  // 40
  //     19.0f, 4.0f, 0.0f,  // 41
  //     21.0f, 7.0f, 0.0f,  // 42
  //     19.0f, 7.0f, 0.0f,  // 43

  //     4.0f, 5.0f, 0.0f,   // 44
  //     6.0f, 5.0f, 0.0f,   // 45
  //     4.0f, 8.0f, 0.0f,   // 46
  //     6.0f, 10.0f, 0.0f,  // 47
  //     2.0f, 8.0f, 0.0f,   // 48
  //     2.0f, 10.0f, 0.0f,  // 49

  //     24.0f, 5.0f, 0.0f,   // 50
  //     22.0f, 5.0f, 0.0f,   // 51
  //     24.0f, 8.0f, 0.0f,   // 52
  //     22.0f, 10.0f, 0.0f,  // 53
  //     26.0f, 8.0f, 0.0f,   // 54
  //     26.0f, 10.0f, 0.0f,  // 55

  //     13.0f, 2.0f, 0.0f,  // 56
  //     15.0f, 2.0f, 0.0f,  // 57
  //     13.0f, 5.0f, 0.0f,  // 58
  //     15.0f, 5.0f, 0.0f,  // 59
  //     10.0f, 5.0f, 0.0f,  // 60
  //     10.0f, 7.0f, 0.0f,  // 61
  //     18.0f, 5.0f, 0.0f,  // 62
  //     18.0f, 7.0f, 0.0f,  // 63

  //     13.0f, 8.0f, 0.0f,   // 64
  //     15.0f, 8.0f, 0.0f,   // 65
  //     13.0f, 11.0f, 0.0f,  // 66
  //     15.0f, 11.0f, 0.0f,  // 67
  //     10.0f, 11.0f, 0.0f,  // 68
  //     10.0f, 13.0f, 0.0f,  // 69
  //     18.0f, 11.0f, 0.0f,  // 70
  //     18.0f, 13.0f, 0.0f,  // 71

  //     13.0f, 20.0f, 0.0f,  // 72
  //     15.0f, 20.0f, 0.0f,  // 73
  //     13.0f, 23.0f, 0.0f,  // 74
  //     15.0f, 23.0f, 0.0f,  // 75
  //     10.0f, 23.0f, 0.0f,  // 76
  //     10.0f, 25.0f, 0.0f,  // 77
  //     18.0f, 23.0f, 0.0f,  // 78
  //     18.0f, 25.0f, 0.0f,  // 79

  //     7.0f, 8.0f, 0.0f,    // 80
  //     7.0f, 10.0f, 0.0f,   // 81
  //     12.0f, 8.0f, 0.0f,   // 82
  //     12.0f, 10.0f, 0.0f,  // 83

  //     21.0f, 8.0f, 0.0f,   // 84
  //     21.0f, 10.0f, 0.0f,  // 85
  //     16.0f, 8.0f, 0.0f,   // 86
  //     16.0f, 10.0f, 0.0f,  // 87

  //     7.0f, 11.0f, 0.0f,  // 88
  //     9.0f, 11.0f, 0.0f,  // 89
  //     7.0f, 16.0f, 0.0f,  // 90
  //     9.0f, 16.0f, 0.0f,  // 91

  //     21.0f, 11.0f, 0.0f,  // 92
  //     19.0f, 11.0f, 0.0f,  // 93
  //     21.0f, 16.0f, 0.0f,  // 94
  //     19.0f, 16.0f, 0.0f,  // 95

  //     7.0f, 17.0f, 0.0f,   // 96
  //     9.0f, 17.0f, 0.0f,   // 97
  //     7.0f, 25.0f, 0.0f,   // 98
  //     9.0f, 25.0f, 0.0f,   // 99
  //     9.0f, 20.0f, 0.0f,   // 100
  //     12.0f, 20.0f, 0.0f,  // 101
  //     9.0f, 22.0f, 0.0f,   // 102
  //     12.0f, 22.0f, 0.0f,  // 103

  //     21.0f, 17.0f, 0.0f,  // 104
  //     19.0f, 17.0f, 0.0f,  // 105
  //     21.0f, 25.0f, 0.0f,  // 106
  //     19.0f, 25.0f, 0.0f,  // 107
  //     19.0f, 20.0f, 0.0f,  // 108
  //     16.0f, 20.0f, 0.0f,  // 109
  //     19.0f, 22.0f, 0.0f,  // 110
  //     16.0f, 22.0f, 0.0f,  // 111

  //     2.0f, 23.0f, 0.0f,  // 112
  //     2.0f, 25.0f, 0.0f,  // 113
  //     6.0f, 23.0f, 0.0f,  // 114
  //     6.0f, 25.0f, 0.0f,  // 115

  //     26.0f, 23.0f, 0.0f,  // 116
  //     26.0f, 25.0f, 0.0f,  // 117
  //     22.0f, 23.0f, 0.0f,  // 118
  //     22.0f, 25.0f, 0.0f,  // 119

  //     2.0f, 26.0f, 0.0f,  // 120
  //     2.0f, 29.0f, 0.0f,  // 121
  //     6.0f, 26.0f, 0.0f,  // 122
  //     6.0f, 29.0f, 0.0f,  // 123

  //     26.0f, 26.0f, 0.0f,  // 124
  //     26.0f, 29.0f, 0.0f,  // 125
  //     22.0f, 26.0f, 0.0f,  // 126
  //     22.0f, 29.0f, 0.0f,  // 127

  //     7.0f, 26.0f, 0.0f,   // 128
  //     7.0f, 29.0f, 0.0f,   // 129
  //     12.0f, 26.0f, 0.0f,  // 130
  //     12.0f, 29.0f, 0.0f,  // 131

  //     21.0f, 26.0f, 0.0f,  // 132
  //     21.0f, 29.0f, 0.0f,  // 133
  //     16.0f, 26.0f, 0.0f,  // 134
  //     16.0f, 29.0f, 0.0f,  // 135

  //     0.0f, 31.0f, 0.0f,   // 136
  //     28.0f, 31.0f, 0.0f,  // 137
  //     28.0f, 21.0f, 0.0f,  // 138
  //     23.0f, 21.0f, 0.0f,  // 139
  //     23.0f, 18.0f, 0.0f,  // 140
  //     28.0f, 18.0f, 0.0f,  // 141
  //     28.0f, 17.0f, 0.0f,  // 142
  //     22.0f, 17.0f, 0.0f,  // 143
  //     22.0f, 22.0f, 0.0f,  // 144
  //     27.0f, 22.0f, 0.0f,  // 145
  //     27.0f, 30.0f, 0.0f,  // 146
  //     15.0f, 30.0f, 0.0f,  // 147
  //     15.0f, 26.0f, 0.0f,  // 148
  //     13.0f, 26.0f, 0.0f,  // 149
  //     13.0f, 30.0f, 0.0f,  // 150
  //     1.0f, 30.0f, 0.0f,   // 151
  //     1.0f, 22.0f, 0.0f,   // 152
  //     6.0f, 22.0f, 0.0f,   // 153
  //     6.0f, 17.0f, 0.0f,   // 154
  //     0.0f, 17.0f, 0.0f,   // 155
  //     0.0f, 18.0f, 0.0f,   // 156
  //     5.0f, 18.0f, 0.0f,   // 157
  //     5.0f, 21.0f, 0.0f,   // 158
  //     0.0f, 21.0f, 0.0f,   // 159

  //     // Quadrado central
  //     10.0f, 14.0f, 0.0f,  // 160
  //     18.0f, 14.0f, 0.0f,  // 161
  //     11.0f, 15.0f, 0.0f,  // 162
  //     17.0f, 15.0f, 0.0f,  // 163
  //     11.0f, 18.0f, 0.0f,  // 164
  //     17.0f, 18.0f, 0.0f,  // 165
  //     10.0f, 19.0f, 0.0f,  // 166
  //     18.0f, 19.0f, 0.0f,  // 167
  //     13.0f, 19.0f, 0.0f,  // 168
  //     15.0f, 19.0f, 0.0f,  // 169
  //     13.0f, 18.0f, 0.0f,  // 170
  //     15.0f, 18.0f, 0.0f,  // 171

  // };

  // unsigned int indices[] = {
  //     0,   1,   2,    //
  //     1,   2,   3,    //
  //     0,   2,   8,    //
  //     0,   8,   15,   //
  //     4,   5,   6,    //
  //     4,   6,   7,    //
  //     8,   9,   15,   //
  //     9,   15,  14,   //
  //     9,   10,  14,   //
  //     14,  10,  13,   //
  //     13,  10,  11,   //
  //     13,  11,  12,   //
  //     1,   3,   27,   //
  //     3,   27,  20,   //
  //     16,  17,  18,   //
  //     16,  18,  19,   //
  //     21,  26,  27,   //
  //     20,  27,  21,   //
  //     21,  22,  26,   //
  //     26,  22,  25,   //
  //     22,  25,  23,   //
  //     25,  23,  24,   //
  //     28,  29,  30,   //
  //     29,  30,  31,   //
  //     32,  33,  34,   //
  //     33,  34,  35,   //
  //     36,  37,  38,   //
  //     37,  38,  39,   //
  //     40,  41,  42,   //
  //     41,  42,  43,   //
  //     44,  45,  46,   //
  //     45,  46,  47,   //
  //     46,  47,  48,   //
  //     47,  48,  49,   //
  //     50,  51,  52,   //
  //     51,  52,  53,   //
  //     52,  53,  54,   //
  //     53,  54,  55,   //
  //     56,  57,  58,   //
  //     57,  58,  59,   //
  //     60,  61,  62,   //
  //     61,  62,  63,   //
  //     64,  65,  66,   //
  //     65,  66,  67,   //
  //     68,  69,  70,   //
  //     69,  70,  71,   //
  //     72,  73,  74,   //
  //     73,  74,  75,   //
  //     76,  77,  78,   //
  //     77,  78,  79,   //
  //     80,  81,  82,   //
  //     81,  82,  83,   //
  //     84,  85,  86,   //
  //     85,  86,  87,   //
  //     88,  89,  90,   //
  //     89,  90,  91,   //
  //     92,  93,  94,   //
  //     93,  94,  95,   //
  //     96,  97,  98,   //
  //     97,  98,  99,   //
  //     100, 101, 102,  //
  //     101, 102, 103,  //
  //     104, 105, 106,  //
  //     105, 106, 107,  //
  //     108, 109, 110,  //
  //     109, 110, 111,  //
  //     112, 113, 114,  //
  //     113, 114, 115,  //
  //     116, 117, 118,  //
  //     117, 118, 119,  //
  //     120, 121, 122,  //
  //     121, 122, 123,  //
  //     124, 125, 126,  //
  //     125, 126, 127,  //
  //     128, 129, 130,  //
  //     129, 130, 131,  //
  //     132, 133, 134,  //
  //     133, 134, 135,  //
  //     136, 137, 151,  //
  //     137, 151, 146,  //
  //     147, 148, 149,  //
  //     147, 149, 150,  //
  //     137, 146, 145,  //
  //     137, 138, 145,  //
  //     138, 145, 144,  //
  //     138, 144, 139,  //
  //     144, 139, 143,  //
  //     139, 143, 140,  //
  //     143, 140, 142,  //
  //     140, 142, 141,  //
  //     151, 136, 152,  //
  //     136, 152, 159,  //
  //     152, 159, 153,  //
  //     159, 153, 158,  //
  //     153, 158, 154,  //
  //     158, 154, 157,  //
  //     154, 157, 155,  //
  //     157, 155, 156,  //
  //     160, 161, 162,  //
  //     161, 162, 163,  //
  //     160, 162, 166,  //
  //     162, 166, 164,  //
  //     166, 164, 168,  //
  //     164, 168, 170,  //
  //     161, 163, 167,  //
  //     163, 167, 165,  //
  //     167, 165, 169,  //
  //     165, 169, 171,  //
  // };

  // glGenVertexArrays(1, &Maze_VAO);
  // glGenBuffers(1, &VBO);
  // glGenBuffers(1, &EBO);

  // glBindVertexArray(Maze_VAO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
  //              GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
  // *)0); glEnableVertexAttribArray(0);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glBindVertexArray(0);
}

void Window::drawPacman() {
  glUseProgram(shaderProgram);

  glm::mat4 mvp = glm::ortho(0.0f, 28.0f, 0.0f, 31.0f);

  unsigned int matrix = glGetUniformLocation(shaderProgram, "mvp");
  glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

  glBindVertexArray(Pacman_VAO);

  glDrawElements(GL_TRIANGLES, 420, GL_UNSIGNED_INT, 0);
  // glBindVertexArray(0); // no need to unbind it every time
}

void Window::drawMaze() {
  Texture2D myTexture;
  myTexture = ResourceManager::GetTexture("maze");
  SheetRenderer->DrawSprite(myTexture, glm::vec2(88, 0), glm::vec2(224, 248),
                            0.0f, glm::vec3(1.0f, 1.0f, 1.0f), 1, 0);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
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

  glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
}

void Window::transferDataToGPUMemory() {
  // load shaders
  ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag",
                              nullptr, "sprite");

  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, (float)SCREEN_WIDTH,
                                    (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

  // set render-specific controls
  Shader myShader;
  myShader = ResourceManager::GetShader("sprite");
  SheetRenderer = new SpriteSheetRenderer(myShader);
  // load textures

  // ------------------------------------------------------------------
  transferMaze();
  transferPacman();
}

void Window::render() {
  // MacOS retina screen fix
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  // Clean window
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw Maze
  glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
  drawMaze();

  // Draw Sidebar
  // glViewport(SCREEN_WIDTH * 2 / 3, 0, SCREEN_WIDTH * 1 / 3, SCREEN_HEIGHT);
  drawPacman();
  // drawSidebar();

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

Window::Window() {}
