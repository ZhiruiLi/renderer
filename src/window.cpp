// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "window.h"
#include <iostream>

static void handleKey(GLFWwindow* window, int key, int scancode, int action,
               int mode) {
  // ESC 关闭应用程序
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

namespace sren {

Window::Window(std::string_view title, int width, int height) {
  // 初始化 GLFW
  glfwInit();
  // GLFW 基本配置
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfw_window_ =
      glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

  if (glfw_window_ == nullptr) {
    glfwTerminate();
    throw std::runtime_error("failed to create GLFW window");
  }

  glfwMakeContextCurrent(glfw_window_);
  glfwSetKeyCallback(glfw_window_, handleKey);

  // 使用实验性功能
  glewExperimental = GL_TRUE;
  // 初始化 GLEW，必须在调用任何 OpenGL 函数之前进行
  if (glewInit() != GLEW_OK) {
    std::cout << "failed to initialize GLEW" << std::endl;
    throw std::runtime_error("failed to initialize GLEW");
  }
}

Window::~Window() { glfwTerminate(); }

void Window::run() {
  while (!glfwWindowShouldClose(glfw_window_)) {
    // 检查事件
    glfwPollEvents();

    // ...
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // 在每个新的渲染迭代开始的时候清屏，否则仍会看见上一迭代的渲染结果。
    // glClear 接受一个 Buffer Bit 来指定要清空的缓冲，
    // 包括：GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT 和 GL_STENCIL_BUFFER_BIT
    // 这个操作还能防止屏幕闪烁，参考
    // https://stackoverflow.com/questions/27678819/crazy-flashing-window-opengl-glfw
    glClear(GL_COLOR_BUFFER_BIT);
    // 交换缓冲
    glfwSwapBuffers(glfw_window_);
  }
}

}  // namespace sren