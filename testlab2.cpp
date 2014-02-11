#include "owninitshader.h"
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

using namespace std;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLuint vao, vbo;
GLuint positionID, colorID;
GLuint program;

GLfloat verticies[] = {-0.5f, -0.5f, 0.0f,
                       0.5f, -0.5f, 0.0f,
                       0.75f, 0.25f, 0.0f,
                       0.0f, 0.85f, 0.0f,
                       -0.75f, 0.25f, 0.0f};
GLfloat colors[] = {1.0f, 1.0f, 0.0f, 1.0f,
                    0.0f, 1.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 0.0f, 1.0f,
                    0.0f, 1.0f, 0.0f, 1.0f};

void init(void) {
  GLuint frags, verts;
  
  program = glCreateProgram();
  verts = initshader("vertexshader.glsl", GL_VERTEX_SHADER);
  frags = initshader("fragmentshader.glsl", GL_FRAGMENT_SHADER);

  glAttachShader(program, verts);
  glAttachShader(program, frags);
  glLinkProgram(program);
  glUseProgram(program);
}

void drawshape() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
 // glBufferSubData(GL_ARRAY_BUFFER, 5*3*sizeof(GLfloat), sizeof(colors), colors);

 // positionID = glGetAttribLocation(program, "s_vPosition");
 // colorID = glGetAttribLocation(program, "s_vColor");

 glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
 // glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3*5*sizeof(GLfloat)));
  glEnableVertexAttribArray(0); //has positionID
 // glEnableVertexAttribArray(colorID);

  glDrawArrays(GL_POLYGON, 0, 3*5);
  glFlush(); 

}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Pentagon");

  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "unable to initialize GLEW");
    exit(EXIT_FAILURE);
  }

  //init();  

  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);

  glutDisplayFunc(drawshape);
  //glutMouseFunc(mousepress);
  glutMainLoop();
  return 0;
}
