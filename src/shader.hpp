#ifndef SHADER_H
#define SHADER_H

#include "opengl.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path);

#endif
