
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "state.h"
#include "camera2d.h"
#include "color.h"
#include "transform.h"
#include "error.h"
#include "shader.h"
#include "quad.h"
#include "triangle.h"
#include "disk.h"

#include <iostream>

static ScenePtr scene;
static CameraPtr camera;

class MovePointer;
using MovePointerPtr = std::shared_ptr<MovePointer>;
class MovePointer : public Engine 
{
  TransformPtr m_trf;
protected:
  MovePointer (TransformPtr trf) 
  : m_trf(trf) 
  {
  }
public:
  static MovePointerPtr Make (TransformPtr trf)
  {
    return MovePointerPtr(new MovePointer(trf));
  }
  virtual void Update (float dt)
  {
    m_trf->Rotate(-dt/30.0f*180.0f,0,0,1);
  }
};

class MoveDisk;
using MoveDiskPtr = std::shared_ptr<MoveDisk>;
class MoveDisk : public Engine 
{
  TransformPtr m_trf;
  float m_speed;
  float m_translation_scale;
  float m_angle = 0.0f;
protected:
  MoveDisk (TransformPtr trf, float speed, float translation_scale) 
  : m_trf(trf), m_speed(speed), m_translation_scale(translation_scale)
  {
  }
public:
  static MoveDiskPtr Make (TransformPtr trf, float speed, float translation_scale)
  {
    return MoveDiskPtr(new MoveDisk(trf, speed, translation_scale));
  }
  virtual void Update (float dt)
  {
    m_angle += -dt/m_speed*180.0f;
    m_trf->LoadIdentity();
    m_trf->Rotate(m_angle,0,0,1);
    m_trf->Translate(m_translation_scale, 0.0f, 0.0f);
  }
};

static void initialize (void)
{
  // set background color: white 
  glClearColor(0.0f,0.0f,0.1f,1.0f);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);

  // create objects
  camera = Camera2D::Make(0,10,0,10);

  auto trf5 = Transform::Make();
  trf5->Scale(0.5f, 0.5f, 1.0f);
  auto lua = Node::Make(trf5, {Color::Make(0.8, 0.8, 1)}, {Disk::Make()});

  auto trf4 = Transform::Make();
  auto centroGravTerra = Node::Make(trf4, {}, {}, {lua});

  auto trf3 = Transform::Make();
  trf3->Scale(0.4f, 0.4f, 1.0f);
  auto terra = Node::Make(trf3, {Color::Make(0, 0, 1)}, {Disk::Make()}, {centroGravTerra});

  auto trf2 = Transform::Make();
  auto centroGravSol = Node::Make(trf2, {}, {}, {terra});

  auto trf1 = Transform::Make();
  trf1->Scale(1.0f,1.0f,1.0f);
  trf1->Translate(5.0f,5.0f,0.0f);
  auto sol = Node::Make(trf1,{Color::Make(1,1,0)},{Disk::Make()}, {centroGravSol});

  auto shader = Shader::Make();
  shader->AttachVertexShader("./shaders/2d/vertex.glsl");
  shader->AttachFragmentShader("./shaders/2d/fragment.glsl");
  shader->Link();

  // build scene
  
  auto root = Node::Make(shader, {sol});
  scene = Scene::Make(root);
  scene->AddEngine(MoveDisk::Make(trf2, 10.0f, 3.5f));
  scene->AddEngine(MoveDisk::Make(trf4, 20.0f, 2.5f));
}

static void display (GLFWwindow* win)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
  Error::Check("before render");
  scene->Render(camera);
  Error::Check("after render");
}

static void error (int code, const char* msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(0);
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

static void update (float dt)
{
  scene->Update(dt);
}

int main ()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);


    glfwSetErrorCallback(error);

    GLFWwindow* win = glfwCreateWindow(600, 400, "Window title", nullptr, nullptr);
    assert(win);
    glfwSetFramebufferSizeCallback(win, resize);  // resize callback
    glfwSetKeyCallback(win, keyboard);            // keyboard callback

    glfwMakeContextCurrent(win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return -1;
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
  initialize();

  float t0 = float(glfwGetTime());
  while(!glfwWindowShouldClose(win)) {
    float t = float(glfwGetTime());
    update(t-t0);
    t0 = t;
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

