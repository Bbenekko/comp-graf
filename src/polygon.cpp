#include "polygon.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

PolygonPtr Polygon::Make ()
{
  return PolygonPtr(new Polygon());
}

Polygon::Polygon ()
{
  float coord[] = {
    0.0f, 0.0f,
    0.5f, 0.25f,
    0.4f, -0.4f,
   -0.20f, -0.5f,
   -0.25f, 0.25f
  };

  unsigned char color[] = {
    255, 100, 100,
    200, 200, 50,
    70, 70, 70,
    70, 255, 70,
    110, 110, 255
  };

  // octógono
  /* float coord[] = {
     0.0f, 0.0f,
    -0.25f,-0.5f, 
     0.25f,-0.5f,
     0.5f,-0.25f,
     0.5f, 0.25f,
     0.25f, 0.5f,
    -0.25f, 0.5f,
    -0.5f, 0.25f,
    -0.5f,-0.25f,
    -0.25f,-0.5f
  };
  unsigned char color[] = {
    100, 100, 100,
    255, 0, 0,
    255, 0, 0,
    0, 255, 0,
    0, 0, 255,
    0, 0, 255,
    0, 0, 255,
    0, 255, 0,
    255, 0, 0,
    255, 0, 0
  }; */

  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  m_vertex = sizeof(coord) / sizeof(coord[0]) / 2;
  // create coord buffer
  GLuint id[2];
  glGenBuffers(2,id);
  glBindBuffer(GL_ARRAY_BUFFER,id[0]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(coord),coord,GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,id[1]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(color),color,GL_STATIC_DRAW);
  glVertexAttribPointer(1,3,GL_UNSIGNED_BYTE,GL_TRUE,0,0);  // color
  glEnableVertexAttribArray(1);
}

Polygon::~Polygon () 
{
}

void Polygon::Draw (StatePtr st)
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLE_FAN,0,m_vertex);
}