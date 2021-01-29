#pragma once

// GLFW
#include <GLFW/glfw3.h>

#include <string_view>

namespace sren {

class Window {
 public:
  Window(std::string_view title, int width, int height);
  ~Window();

  void run();

 private:
  GLFWwindow* glfw_window_;
};

}  // namespace sren
