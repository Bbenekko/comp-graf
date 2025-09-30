#include "circle.h"

#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

CirclePtr Circle::Make (float thickness, float radius, int segments)
{
  return CirclePtr(new Circle(thickness, radius, segments));
}

Circle::Circle (float thickness, float radius, int segments)
: nSegments(segments)
{

  std::vector<float> coord;
  std::vector<unsigned char>color;
  for(int i = 0; i <= segments; i++)
  {
    float t = (i / (float)segments) * (M_PI * 2.0f);
    float x = std::cos(t);
    float y = std::sin(t);  

    coord.push_back(x * radius);
    coord.push_back(y * radius);
    // espessura
    coord.push_back((radius - thickness) * x);
    coord.push_back((radius - thickness) * y);

    //preto
    for (int i = 0; i < 6; i++) color.push_back(0);
  }
    
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

Circle::~Circle () 
{
}

void Circle::Draw (StatePtr st)  
{
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLE_STRIP,0,(nSegments+1)*2);
}