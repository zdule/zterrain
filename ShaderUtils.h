#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <cstdarg>

//shaders
bool loadShaderFile(const char* ShaderPath, GLuint shader);
GLuint loadShaderProgram(const char* vertexShaderPath,const char* fragmentShaderPath, ...);


#endif // SHADER_UTILS_H

