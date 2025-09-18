#version 410

layout (location=0) in vec4 vertex;
layout (location=1) in vec4 inColor;

out Data {
  vec4 color;
} v;

uniform mat4 M;

void main (void)
{
  v.color = inColor;
  gl_Position = M * vertex;
}

