#include "disk.h"

#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

DiskPtr Disk::Make (int segments)
{
  return DiskPtr(new Disk(segments));
}

Disk::Disk (int segments)
: nSegments(segments)
{

  std::vector<float> coord;
  std::vector<unsigned char>color;
  for(int i = 0; i <= segments; i++)
  {
    float t = (i / (float)segments) * (M_PI * 2.0f);
    float x = std::cos(t);
    float y = std::sin(t);  

    coord.push_back(x * 1);
    coord.push_back(y * 1);

    //preto
    for (int i = 0; i < 6; i++) color.push_back(0);
  }
  coord.push_back(0);
  coord.push_back(0);
    
  // create VAO
  glGenVertexArrays(1,&m_vao);
  glBindVertexArray(m_vao);
  // create coord buffer
  GLuint id[2];
  glGenBuffers(2,id);
  glBindBuffer(GL_ARRAY_BUFFER,id[0]);
  glBufferData(GL_ARRAY_BUFFER, coord.size() * sizeof(float),coord.data(),GL_STATIC_DRAW);
  glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);  // coord
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,id[1]);
  glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(unsigned char),color.data(),GL_STATIC_DRAW);
  glVertexAttribPointer(1,3,GL_UNSIGNED_BYTE,GL_TRUE,0,0);  // color
  glEnableVertexAttribArray(1);
}

Disk::~Disk () 
{
}

void Disk::Draw (StatePtr st)  
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLE_FAN,0,(nSegments+1));
}