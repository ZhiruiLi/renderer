#pragma once

// GLFW
#include <GLFW/glfw3.h>

#include <chrono>
#include <functional>
#include <string_view>

#include "frame_buffer.h"

namespace sren {

class Window {
 public:
  using LoopFunc = std::function<void(FrameBuffer*)>;
  using FloatSeconds = std::chrono::duration<float>;
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

  Window(std::string_view title, int width, int height);
  ~Window();

  void Run();
  void Close();

  void set_main_loop(LoopFunc func) { main_loop_ = std::move(func); }
  int frame_width() const { return frame_buffer_.width(); }
  int frame_height() const { return frame_buffer_.height(); }
  float delta_time() const { return delta_time_; }
  TimePoint last_update_time() { return last_update_time_; };
  TimePoint current_time() { return current_time_; };

 private:
  static std::chrono::time_point<std::chrono::system_clock> now();

  GLFWwindow* glfw_window_{};
  LoopFunc main_loop_{};
  FrameBuffer frame_buffer_{};
  float delta_time_{};
  std::chrono::time_point<std::chrono::system_clock> current_time_{};
  std::chrono::time_point<std::chrono::system_clock> last_update_time_{};
};

}  // namespace sren
