#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL

#include "error.h"
#include "triangle.h"
#include "shader.h"
#include "polygon.h"
#include "circle.h"

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <time.h>

static CirclePtr circ;
static TrianglePtr tri;
static ShaderPtr shd;
static PolygonPtr poly;
static GLint uModelLoc = -1;

static void error (int code, const char* msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(1);
}

static void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize (GLFWwindow* win, int width, int height)
{
  glViewport(0,0,width,height);
}

static void initialize ()
{
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  tri = Triangle::Make();
  shd = Shader::Make();
  poly = Polygon::Make();
  circ = Circle::Make();
  shd->AttachVertexShader("shaders/vertex.glsl");
  shd->AttachFragmentShader("shaders/fragment.glsl");
  shd->Link();
  Error::Check("initialize");
}

static void display (GLFWwindow* win)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shd->UseProgram();  
  // desenhar o relógio

  glm::mat4 circRelogio(1.0f);
  circRelogio = glm::scale(circRelogio, glm::vec3(0.55f, 0.9f, 1.0f));
  shd->SetUniform("M", circRelogio);
  circ->Draw();

  Error::Check("display");
}

void update(float dt)
{

}

int main ()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);       // required for mac os
  //glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER,GLFW_TRUE);  // option for mac os

  glfwSetErrorCallback(error);

  GLFWwindow* win = glfwCreateWindow(600,400,"Relogio teste",nullptr,nullptr);
  glfwSetFramebufferSizeCallback(win, resize);  // resize callback
  glfwSetKeyCallback(win, keyboard);            // keyboard callback
  
  glfwMakeContextCurrent(win);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
  {
    printf("Failed to initialize GLAD OpenGL context\n");
    exit(1);
  }

  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  initialize();

  double t0 = glfwGetTime();
  double t;
  while(!glfwWindowShouldClose(win)) {
    t = glfwGetTime();
    update(t-t0);
    t0 = t;
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
