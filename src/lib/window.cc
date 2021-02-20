#define GL_SILENCE_DEPRECATION 1
#include "window.h"

#include <chrono>
#include <iostream>

#include "frame_buffer.h"
#include "key.h"

namespace sren {

void Window::Close() { glfwSetWindowShouldClose(glfw_window_, GL_TRUE); }

Window::Window(std::string const& title, int width, int height) {
  // 初始化 GLFW
  if (!glfwInit()) {
    throw std::runtime_error("GLFW init fail");
  }

  glfw_window_ =
      glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

  if (glfw_window_ == nullptr) {
    glfwTerminate();
    throw std::runtime_error("failed to create GLFW window");
  }

  glfwMakeContextCurrent(glfw_window_);
  glfwSetKeyCallback(glfw_window_, details::HandleKey);
}

Window::~Window() { glfwTerminate(); }

std::chrono::time_point<std::chrono::system_clock> Window::now() {
  return std::chrono::system_clock::now();
}

void Window::Run() {
  last_update_time_ = now();
  while (!glfwWindowShouldClose(glfw_window_)) {
    current_time_ = now();
    auto const delta_dura = current_time_ - last_update_time_;
    delta_time_ = std::chrono::duration_cast<FloatSeconds>(delta_dura).count();

    // 检查事件
    glfwPollEvents();

    // 在每个新的渲染迭代开始的时候清屏，否则仍会看见上一迭代的渲染结果。
    // glClear 接受一个 Buffer Bit 来指定要清空的缓冲，
    // 包括：GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT 和 GL_STENCIL_BUFFER_BIT
    // 这个操作还能防止屏幕闪烁，参考
    // https://stackoverflow.com/questions/27678819/crazy-flashing-window-opengl-glfw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 注意在 retina 屏幕下，由于存在缩放，所以像素和 window 大小并不是一对一的
    // 例如 200% 缩放的情况下，对于一个屏幕上的一个单位点，需要渲染四个像素
    // https://stackoverflow.com/questions/36672935/why-retina-screen-coordinate-value-is-twice-the-value-of-pixel-value
    int bwidth{};
    int bheight{};
    glfwGetFramebufferSize(glfw_window_, &bwidth, &bheight);
    glViewport(0, 0, bwidth, bheight);
    frame_buffer_.Resize(bwidth, bheight);

    if (main_loop_) {
      main_loop_(this);
    }

    glDrawPixels(frame_buffer_.width(), frame_buffer_.height(), GL_RGBA,
                 GL_UNSIGNED_BYTE, frame_buffer_.data());

    // 交换缓冲，修改的缓冲和展示的缓冲是两个数据，交换才能正常展示
    glfwSwapBuffers(glfw_window_);

    // 清理按键记录
    details::ClearKeyState();
  }
}

}  // namespace sren
