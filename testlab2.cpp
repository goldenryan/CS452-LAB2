#include "owninitshader2.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

using namespace std;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLuint vao, vbo[2];

GLfloat verticies[] = {-0.175f, -0.25f, 0.0f,
                       0.175f, -0.25f, 0.0f,
                       0.3f, 0.0f, 0.0f,
                       0.0f, 0.3f, 0.0f,
                       -0.3f, 0.0f, 0.0f};
GLfloat colors[] = {0.0f, 0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 0.0f, 1.0f,
                    1.0f, 1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 0.0f, 1.0f};



void init() {  
  ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL}
  };

  initShaders(shaders);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(2, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

  //positionID = glGetAttribLocation(program, "s_vPosition");
  //colorID = glGetAttribLocation(program, "s_vColor");

  //glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  //glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3*3*sizeof(GLfloat)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void drawshape() {
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_POLYGON, 0, 5);
  glFlush(); 

}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Pentigon");

  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "unable to initialize GLEW");
    exit(EXIT_FAILURE);
  }
   

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);
  init();
  glutDisplayFunc(drawshape);
  //glutMouseFunc(mousepress);
  glutMainLoop();
  return 0;
}
