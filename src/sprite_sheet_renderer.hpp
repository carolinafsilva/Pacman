/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SPRITE_SHEET_RENDERER_H
#define SPRITE_SHEET_RENDERER_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "texture.h"

class SpriteSheetRenderer {
 public:
  // Constructor (inits shaders/shapes)
  SpriteSheetRenderer(Shader &shader);
  // Destructor
  ~SpriteSheetRenderer();
  // Renders a defined quad textured with given sprite
  void DrawSprite(Texture2D &texture, glm::vec2 position,
                  glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                  glm::vec3 color = glm::vec3(1.0f), int totalSprites = 1,
                  int spriteNumber = 0);

 private:
  // Render state
  Shader shader;
  unsigned int posVAO;
  // Initializes and configures the quad's buffer and vertex attributes
  void initRenderData();
};

#endif
