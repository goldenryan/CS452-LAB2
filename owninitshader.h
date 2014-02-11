#ifndef OWNINITSHADER_H_
#define OWNINITSHADER_H_

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"

#include <cstdio>
#include <iostream>
using namespace std;

GLuint initshader(char * file, GLenum type) {
  GLint filesize;
  FILE *shade = fopen(file, "r");

  fseek(shade, 0,SEEK_END);
  filesize = ftell(shade);
  rewind(shade);
  const char *buffer = (char *) malloc(sizeof(char) * filesize);

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &buffer, &filesize);

  glCompileShader(shader);

  GLint size;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
  GLchar *check = new GLchar[size+1];
  glGetShaderInfoLog(shader, size, &size, check);

  if(size) {
    fprintf(stderr, "Shader failed, Error:%s\n", check);
    exit(1);
  }

  fclose(shade);
  //free(buffer);
  
  return shader;
}

#endif
