#include "utils/debugout.h"

#include <glfw3.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

#pragma comment (lib, "glfw3.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

#include "opengl/objects/cube.h"
#include "opengl/objects/plane.h"
#include "opengl/camera.h"
#include "opengl/glutils.h"
#include "opengl/DeferredRenderer.h"
#include "motionModel/motionModel.h"



struct WindowSetup {
  static const int REFRESH_RATE = 60;// Hz
  static const int WIDTH = 1024;
  static const int HEIGHT = 768;  
  static const float ASPECT;
};

const float WindowSetup::ASPECT = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);

const size_t numCubes = 500;

int main()
{
  if (!glfwInit()) 
  {
    debugLog(">>> Failed to initialize GLFW!");
    std::cout << "Failed to initialize GLFW!" << std::endl;
    return -1;
  }

  
  glfwWindowHint(GLFW_REFRESH_RATE, WindowSetup::REFRESH_RATE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  
  GLFWwindow* window = glfwCreateWindow(WindowSetup::WIDTH, WindowSetup::HEIGHT, "Deferred Rendering", NULL, NULL);
  
  glfwShowWindow(window);

  /*auto cube = CubeVBO::createUnique();*/
  glfwMakeContextCurrent(window);

  std::vector<std::unique_ptr<CubeVBO>> cubes;
  cubes.resize(numCubes);

  SYSTEMTIME time;
  GetSystemTime(&time);
  LONG timeMS = (time.wSecond * 1000) + time.wMilliseconds;
  srand(timeMS);
  
  auto deferredRenderer = DeferredRenderer::createUnique(WindowSetup::WIDTH, WindowSetup::HEIGHT, 8);

  for (auto& cube : cubes)
  {
    auto r0 = rand() / static_cast<float>(RAND_MAX);
    auto r1 = rand() / static_cast<float>(RAND_MAX);
    auto r2 = rand() / static_cast<float>(RAND_MAX);

    cube = CubeVBO::createUnique(deferredRenderer->pass0());
    cube->color() = { 214.0f * r0, 64.0f * r0, 187.0f * r0 };
    cube->color() = { 255, 200, 0 };
    cube->position() = {-100.0f + (200.0f * r1), 1, -100.0f + (200.0f * r2)};
  }

  auto plane = PlaneVBO::createUnique(deferredRenderer->pass0());
  plane->color() = { 230, 149, 18 };


  Camera camera;  
  camera.mode() = Camera::Mode::PERSPECTIVE;
  camera.perspectiveData() = { 45.0f, WindowSetup::ASPECT, 0.1f, 1000.0f };

  MotionModel motionModel;
  motionModel.eyePosition() = { 0, 4, 20 };
  motionModel.deltaPos() = 0.2f;
  motionModel.deltaAtt() = 1;

  while (!glfwWindowShouldClose(window))
  {
    motionModel.computeMotion();

    camera.position() = motionModel.eyePosition();
    camera.attitude() = motionModel.eyeAttitude();

    //glClearColor(18.f/255.f, 230.f/255.f, 223.f/255.f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);
    deferredRenderer->attach();    
    auto projectionMatrix = camera.projectionMatrix();
    auto viewMatrix = camera.viewMatrix();
    
    plane->draw(projectionMatrix, viewMatrix);

    for (auto& cube : cubes)
    {
      cube->draw(projectionMatrix, viewMatrix);
    }
    deferredRenderer->detach();

    deferredRenderer->render(camera);

    deferredRenderer->debug();

    glfwSwapBuffers(window);
    glfwPollEvents();

    OPENGL_CHECK_ERROR();
  }
}
