#include "sprite_sheet_renderer.hpp"

#include <iostream>

SpriteSheetRenderer::SpriteSheetRenderer(Shader &shader) {
  this->shader = shader;
  this->initRenderData();
}

SpriteSheetRenderer::~SpriteSheetRenderer() {
  glDeleteVertexArrays(1, &this->posVAO);
}

void SpriteSheetRenderer::DrawSprite(Texture2D &texture, glm::vec2 position,
                                     glm::vec2 size, float rotate,
                                     glm::vec3 color, int totalSprites,
                                     int spriteNumber) {
  // prepare transformations
  this->shader.Use();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(
      model, glm::vec3(position,
                       0.0f));  // first translate (transformations are: scale
                                // happens first, then rotation, and then final
                                // translation happens; reversed order)

  model = glm::translate(
      model, glm::vec3(0.5f * size.x, 0.5f * size.y,
                       0.0f));  // move origin of rotation to center of quad
  model = glm::rotate(model, glm::radians(rotate),
                      glm::vec3(0.0f, 0.0f, 1.0f));  // then rotate
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y,
                                          0.0f));  // move origin back

  model = glm::scale(model, glm::vec3(size, 1.0f));  // last scale

  this->shader.SetMatrix4("model", model);

  glm::mat4 texModel = glm::mat4(1.0f);

  float spriteHeight = 1 / ((float)totalSprites);

  texModel = glm::translate(
      texModel, glm::vec3(0.0f, (totalSprites - spriteNumber) * spriteHeight,
                          0.0f));  // move origin back

  texModel =
      glm::scale(texModel, glm::vec3(1.0f, spriteHeight, 1.0f));  // last scale

  this->shader.SetMatrix4("texModel", texModel);
  // render textured quad
  this->shader.SetVector3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  texture.Bind();

  glBindVertexArray(this->posVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteSheetRenderer::initRenderData() {
  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = {
      // pos      // tex
      0.0f, 1.0f, 0.0f, 1.0f,  //
      1.0f, 0.0f, 1.0f, 0.0f,  //
      0.0f, 0.0f, 0.0f, 0.0f,  //

      0.0f, 1.0f, 0.0f, 1.0f,  //
      1.0f, 1.0f, 1.0f, 1.0f,  //
      1.0f, 0.0f, 1.0f, 0.0f   //
  };

  glGenVertexArrays(1, &this->posVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->posVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
