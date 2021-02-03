#pragma once

// GLFW
#include <GLFW/glfw3.h>

#include <functional>
#include <string_view>

#include "frame_buffer.h"
#include "key.h"

namespace sren {

class Window {
 public:
  using LoopFunc = std::function<void(FrameBuffer*)>;

  Window(std::string_view title, int width, int height);
  ~Window();

  void Run();
  void Close();

  void set_main_loop(LoopFunc func) { main_loop_ = std::move(func); }

 private:
  GLFWwindow* glfw_window_{};
  LoopFunc main_loop_{};
  FrameBuffer frame_buffer_{};
};

bool IsKeyPress(Key k);
bool IsKeyRelease(Key k);
bool IsKeyHold(Key k);

}  // namespace sren
