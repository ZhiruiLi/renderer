#pragma once

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <chrono>
#include <functional>
#include <string>

#include "frame_buffer.h"

namespace sren {

class Window {
 public:
  using LoopFunc = std::function<void(Window *)>;
  using FloatSeconds = std::chrono::duration<float>;
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

  Window(std::string const &title, int width, int height);
  ~Window();

  void Run();
  void Close();

  void set_main_loop(LoopFunc func) { main_loop_ = std::move(func); }
  FrameBuffer &frame_buffer() { return frame_buffer_; }
  FrameBuffer const &frame_buffer() const { return frame_buffer_; }
  float delta_time() const { return delta_time_; }
  TimePoint last_update_time() { return last_update_time_; };
  TimePoint current_time() { return current_time_; };

 private:
  static std::chrono::time_point<std::chrono::system_clock> now();

  int width_{};
  int height_{};
  GLFWwindow *glfw_window_{};
  LoopFunc main_loop_{};
  FrameBuffer frame_buffer_{};
  float delta_time_{};
  GLuint image_texture_{};
  std::chrono::time_point<std::chrono::system_clock> current_time_{};
  std::chrono::time_point<std::chrono::system_clock> last_update_time_{};
};

}  // namespace sren
