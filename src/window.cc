// GLFW
#include "window.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "key.h"

namespace sren {

namespace {

uint8_t keyState[int(Key::kCount)] = {};

void SetKey(Key k, int action) { keyState[int(k)] = uint8_t(action) + 1; }

void HandleKey(GLFWwindow* w, int key, int scancode, int action, int mode) {
  switch (key) {
    case GLFW_KEY_SPACE:
      return SetKey(Key::kSpace, action);
    case GLFW_KEY_APOSTROPHE:
      return SetKey(Key::kApostrophe, action);
    case GLFW_KEY_COMMA:
      return SetKey(Key::kComma, action);
    case GLFW_KEY_MINUS:
      return SetKey(Key::kMinus, action);
    case GLFW_KEY_PERIOD:
      return SetKey(Key::kPeriod, action);
    case GLFW_KEY_SLASH:
      return SetKey(Key::kSlash, action);
    case GLFW_KEY_0:
      return SetKey(Key::k0, action);
    case GLFW_KEY_1:
      return SetKey(Key::k1, action);
    case GLFW_KEY_2:
      return SetKey(Key::k2, action);
    case GLFW_KEY_3:
      return SetKey(Key::k3, action);
    case GLFW_KEY_4:
      return SetKey(Key::k4, action);
    case GLFW_KEY_5:
      return SetKey(Key::k5, action);
    case GLFW_KEY_6:
      return SetKey(Key::k6, action);
    case GLFW_KEY_7:
      return SetKey(Key::k7, action);
    case GLFW_KEY_8:
      return SetKey(Key::k8, action);
    case GLFW_KEY_9:
      return SetKey(Key::k9, action);
    case GLFW_KEY_SEMICOLON:
      return SetKey(Key::kSemicolon, action);
    case GLFW_KEY_EQUAL:
      return SetKey(Key::kEqual, action);
    case GLFW_KEY_A:
      return SetKey(Key::kA, action);
    case GLFW_KEY_B:
      return SetKey(Key::kB, action);
    case GLFW_KEY_C:
      return SetKey(Key::kC, action);
    case GLFW_KEY_D:
      return SetKey(Key::kD, action);
    case GLFW_KEY_E:
      return SetKey(Key::kE, action);
    case GLFW_KEY_F:
      return SetKey(Key::kF, action);
    case GLFW_KEY_G:
      return SetKey(Key::kG, action);
    case GLFW_KEY_H:
      return SetKey(Key::kH, action);
    case GLFW_KEY_I:
      return SetKey(Key::kI, action);
    case GLFW_KEY_J:
      return SetKey(Key::kJ, action);
    case GLFW_KEY_K:
      return SetKey(Key::kK, action);
    case GLFW_KEY_L:
      return SetKey(Key::kL, action);
    case GLFW_KEY_M:
      return SetKey(Key::kM, action);
    case GLFW_KEY_N:
      return SetKey(Key::kN, action);
    case GLFW_KEY_O:
      return SetKey(Key::kO, action);
    case GLFW_KEY_P:
      return SetKey(Key::kP, action);
    case GLFW_KEY_Q:
      return SetKey(Key::kQ, action);
    case GLFW_KEY_R:
      return SetKey(Key::kR, action);
    case GLFW_KEY_S:
      return SetKey(Key::kS, action);
    case GLFW_KEY_T:
      return SetKey(Key::kT, action);
    case GLFW_KEY_U:
      return SetKey(Key::kU, action);
    case GLFW_KEY_V:
      return SetKey(Key::kV, action);
    case GLFW_KEY_W:
      return SetKey(Key::kW, action);
    case GLFW_KEY_X:
      return SetKey(Key::kX, action);
    case GLFW_KEY_Y:
      return SetKey(Key::kY, action);
    case GLFW_KEY_Z:
      return SetKey(Key::kZ, action);
    case GLFW_KEY_LEFT_BRACKET:
      return SetKey(Key::kLeftBracket, action);
    case GLFW_KEY_BACKSLASH:
      return SetKey(Key::kBackslash, action);
    case GLFW_KEY_RIGHT_BRACKET:
      return SetKey(Key::kRightBracket, action);
    case GLFW_KEY_GRAVE_ACCENT:
      return SetKey(Key::kGraveAccent, action);
    case GLFW_KEY_WORLD_1:
      return SetKey(Key::kWorld1, action);
    case GLFW_KEY_WORLD_2:
      return SetKey(Key::kWorld2, action);
    case GLFW_KEY_ESCAPE:
      return SetKey(Key::kEscape, action);
    case GLFW_KEY_ENTER:
      return SetKey(Key::kEnter, action);
    case GLFW_KEY_TAB:
      return SetKey(Key::kTab, action);
    case GLFW_KEY_BACKSPACE:
      return SetKey(Key::kBackspace, action);
    case GLFW_KEY_INSERT:
      return SetKey(Key::kInsert, action);
    case GLFW_KEY_DELETE:
      return SetKey(Key::kDelete, action);
    case GLFW_KEY_RIGHT:
      return SetKey(Key::kRight, action);
    case GLFW_KEY_LEFT:
      return SetKey(Key::kLeft, action);
    case GLFW_KEY_DOWN:
      return SetKey(Key::kDown, action);
    case GLFW_KEY_UP:
      return SetKey(Key::kUp, action);
    case GLFW_KEY_PAGE_UP:
      return SetKey(Key::kPageUp, action);
    case GLFW_KEY_PAGE_DOWN:
      return SetKey(Key::kPageDown, action);
    case GLFW_KEY_HOME:
      return SetKey(Key::kHome, action);
    case GLFW_KEY_END:
      return SetKey(Key::kEnd, action);
    case GLFW_KEY_CAPS_LOCK:
      return SetKey(Key::kCapsLock, action);
    case GLFW_KEY_SCROLL_LOCK:
      return SetKey(Key::kScrollLock, action);
    case GLFW_KEY_NUM_LOCK:
      return SetKey(Key::kNumLock, action);
    case GLFW_KEY_PRINT_SCREEN:
      return SetKey(Key::kPrintScreen, action);
    case GLFW_KEY_PAUSE:
      return SetKey(Key::kPause, action);
    case GLFW_KEY_F1:
      return SetKey(Key::kF1, action);
    case GLFW_KEY_F2:
      return SetKey(Key::kF2, action);
    case GLFW_KEY_F3:
      return SetKey(Key::kF3, action);
    case GLFW_KEY_F4:
      return SetKey(Key::kF4, action);
    case GLFW_KEY_F5:
      return SetKey(Key::kF5, action);
    case GLFW_KEY_F6:
      return SetKey(Key::kF6, action);
    case GLFW_KEY_F7:
      return SetKey(Key::kF7, action);
    case GLFW_KEY_F8:
      return SetKey(Key::kF8, action);
    case GLFW_KEY_F9:
      return SetKey(Key::kF9, action);
    case GLFW_KEY_F10:
      return SetKey(Key::kF10, action);
    case GLFW_KEY_F11:
      return SetKey(Key::kF11, action);
    case GLFW_KEY_F12:
      return SetKey(Key::kF12, action);
    case GLFW_KEY_F13:
      return SetKey(Key::kF13, action);
    case GLFW_KEY_F14:
      return SetKey(Key::kF14, action);
    case GLFW_KEY_F15:
      return SetKey(Key::kF15, action);
    case GLFW_KEY_F16:
      return SetKey(Key::kF16, action);
    case GLFW_KEY_F17:
      return SetKey(Key::kF17, action);
    case GLFW_KEY_F18:
      return SetKey(Key::kF18, action);
    case GLFW_KEY_F19:
      return SetKey(Key::kF19, action);
    case GLFW_KEY_F20:
      return SetKey(Key::kF20, action);
    case GLFW_KEY_F21:
      return SetKey(Key::kF21, action);
    case GLFW_KEY_F22:
      return SetKey(Key::kF22, action);
    case GLFW_KEY_F23:
      return SetKey(Key::kF23, action);
    case GLFW_KEY_F24:
      return SetKey(Key::kF24, action);
    case GLFW_KEY_F25:
      return SetKey(Key::kF25, action);
    case GLFW_KEY_KP_0:
      return SetKey(Key::kKp0, action);
    case GLFW_KEY_KP_1:
      return SetKey(Key::kKp1, action);
    case GLFW_KEY_KP_2:
      return SetKey(Key::kKp2, action);
    case GLFW_KEY_KP_3:
      return SetKey(Key::kKp3, action);
    case GLFW_KEY_KP_4:
      return SetKey(Key::kKp4, action);
    case GLFW_KEY_KP_5:
      return SetKey(Key::kKp5, action);
    case GLFW_KEY_KP_6:
      return SetKey(Key::kKp6, action);
    case GLFW_KEY_KP_7:
      return SetKey(Key::kKp7, action);
    case GLFW_KEY_KP_8:
      return SetKey(Key::kKp8, action);
    case GLFW_KEY_KP_9:
      return SetKey(Key::kKp9, action);
    case GLFW_KEY_KP_DECIMAL:
      return SetKey(Key::kKpDecimal, action);
    case GLFW_KEY_KP_DIVIDE:
      return SetKey(Key::kKpDivide, action);
    case GLFW_KEY_KP_MULTIPLY:
      return SetKey(Key::kKpMultiply, action);
    case GLFW_KEY_KP_SUBTRACT:
      return SetKey(Key::kKpSubtract, action);
    case GLFW_KEY_KP_ADD:
      return SetKey(Key::kKpAdd, action);
    case GLFW_KEY_KP_ENTER:
      return SetKey(Key::kKpEnter, action);
    case GLFW_KEY_KP_EQUAL:
      return SetKey(Key::kKpEqual, action);
    case GLFW_KEY_LEFT_SHIFT:
      return SetKey(Key::kLeftShift, action);
    case GLFW_KEY_LEFT_CONTROL:
      return SetKey(Key::kLeftControl, action);
    case GLFW_KEY_LEFT_ALT:
      return SetKey(Key::kLeftAlt, action);
    case GLFW_KEY_LEFT_SUPER:
      return SetKey(Key::kLeftSuper, action);
    case GLFW_KEY_RIGHT_SHIFT:
      return SetKey(Key::kRightShift, action);
    case GLFW_KEY_RIGHT_CONTROL:
      return SetKey(Key::kRightControl, action);
    case GLFW_KEY_RIGHT_ALT:
      return SetKey(Key::kRightAlt, action);
    case GLFW_KEY_RIGHT_SUPER:
      return SetKey(Key::kRightSuper, action);
    case GLFW_KEY_MENU:
      return SetKey(Key::kMenu, action);
  }
}

}  // namespace

bool IsKeyPress(Key k) { return keyState[int(k)] == GLFW_PRESS + 1; }
bool IsKeyRelease(Key k) { return keyState[int(k)] == GLFW_RELEASE + 1; }
bool IsKeyHold(Key k) { return keyState[int(k)] == GLFW_REPEAT + 1; }

void Window::Close() { glfwSetWindowShouldClose(glfw_window_, GL_TRUE); }

Window::Window(std::string_view title, int width, int height) {
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
  glfwSetKeyCallback(glfw_window_, HandleKey);

  // 注意在 retina 屏幕下，由于存在缩放，所以像素和 window 大小并不是一对一的
  // 例如 200% 缩放的情况下，对于一个屏幕上的一个单位点，需要渲染四个像素
  // https://stackoverflow.com/questions/36672935/why-retina-screen-coordinate-value-is-twice-the-value-of-pixel-value
  int bwidth{};
  int bheight{};
  glfwGetFramebufferSize(glfw_window_, &bwidth, &bheight);
  glViewport(0, 0, bwidth, bheight);
  frame_buffer_.Resize(bwidth, bheight);
}

Window::~Window() { glfwTerminate(); }

void Window::Run() {
  while (!glfwWindowShouldClose(glfw_window_)) {
    // 检查事件
    glfwPollEvents();

    if (main_loop_) {
      main_loop_(&frame_buffer_);
    }

    // 在每个新的渲染迭代开始的时候清屏，否则仍会看见上一迭代的渲染结果。
    // glClear 接受一个 Buffer Bit 来指定要清空的缓冲，
    // 包括：GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT 和 GL_STENCIL_BUFFER_BIT
    // 这个操作还能防止屏幕闪烁，参考
    // https://stackoverflow.com/questions/27678819/crazy-flashing-window-opengl-glfw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawPixels(frame_buffer_.width(), frame_buffer_.height(), GL_RGB,
                 GL_UNSIGNED_BYTE, frame_buffer_.data());

    // 交换缓冲，修改的缓冲和展示的缓冲是两个数据，交换才能正常展示
    glfwSwapBuffers(glfw_window_);

    // 清理按键记录
    bzero(keyState, sizeof(keyState));
  }
}

}  // namespace sren
