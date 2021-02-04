#include "key.h"

#include <array>
#include <cstddef>
#include <utility>

#include "GLFW/glfw3.h"

namespace sren {

namespace {

std::array<std::pair<uint8_t, uint8_t>, std::size_t(Key::kCount)> gKeyState{};

void SetKeyState(Key k, int action, int mode) {
  gKeyState[int(k)] = std::make_pair(uint8_t(action + 1), uint8_t(mode));
}

}  // namespace

namespace details {

bool HasModifierKey(uint8_t state, KeyMod mod) {
  switch (mod) {
    case KeyMod::kShift:
      return state & GLFW_MOD_SHIFT;
    case KeyMod::kControl:
      return state & GLFW_MOD_CONTROL;
    case KeyMod::kAlt:
      return state & GLFW_MOD_ALT;
    case KeyMod::kSuper:
      return state & GLFW_MOD_SUPER;
    case KeyMod::kCapsLock:
      return state & GLFW_MOD_CAPS_LOCK;
    case KeyMod::kNumLock:
      return state & GLFW_MOD_NUM_LOCK;
  }
  return false;
}

std::pair<uint8_t, uint8_t> const& GetKeyState(Key k) {
  return gKeyState[int(k)];
}

void HandleKey(GLFWwindow* w, int key, int scancode, int action, int mode) {
  switch (key) {
    case GLFW_KEY_SPACE:
      return SetKeyState(Key::kSpace, action, mode);
    case GLFW_KEY_APOSTROPHE:
      return SetKeyState(Key::kApostrophe, action, mode);
    case GLFW_KEY_COMMA:
      return SetKeyState(Key::kComma, action, mode);
    case GLFW_KEY_MINUS:
      return SetKeyState(Key::kMinus, action, mode);
    case GLFW_KEY_PERIOD:
      return SetKeyState(Key::kPeriod, action, mode);
    case GLFW_KEY_SLASH:
      return SetKeyState(Key::kSlash, action, mode);
    case GLFW_KEY_0:
      return SetKeyState(Key::k0, action, mode);
    case GLFW_KEY_1:
      return SetKeyState(Key::k1, action, mode);
    case GLFW_KEY_2:
      return SetKeyState(Key::k2, action, mode);
    case GLFW_KEY_3:
      return SetKeyState(Key::k3, action, mode);
    case GLFW_KEY_4:
      return SetKeyState(Key::k4, action, mode);
    case GLFW_KEY_5:
      return SetKeyState(Key::k5, action, mode);
    case GLFW_KEY_6:
      return SetKeyState(Key::k6, action, mode);
    case GLFW_KEY_7:
      return SetKeyState(Key::k7, action, mode);
    case GLFW_KEY_8:
      return SetKeyState(Key::k8, action, mode);
    case GLFW_KEY_9:
      return SetKeyState(Key::k9, action, mode);
    case GLFW_KEY_SEMICOLON:
      return SetKeyState(Key::kSemicolon, action, mode);
    case GLFW_KEY_EQUAL:
      return SetKeyState(Key::kEqual, action, mode);
    case GLFW_KEY_A:
      return SetKeyState(Key::kA, action, mode);
    case GLFW_KEY_B:
      return SetKeyState(Key::kB, action, mode);
    case GLFW_KEY_C:
      return SetKeyState(Key::kC, action, mode);
    case GLFW_KEY_D:
      return SetKeyState(Key::kD, action, mode);
    case GLFW_KEY_E:
      return SetKeyState(Key::kE, action, mode);
    case GLFW_KEY_F:
      return SetKeyState(Key::kF, action, mode);
    case GLFW_KEY_G:
      return SetKeyState(Key::kG, action, mode);
    case GLFW_KEY_H:
      return SetKeyState(Key::kH, action, mode);
    case GLFW_KEY_I:
      return SetKeyState(Key::kI, action, mode);
    case GLFW_KEY_J:
      return SetKeyState(Key::kJ, action, mode);
    case GLFW_KEY_K:
      return SetKeyState(Key::kK, action, mode);
    case GLFW_KEY_L:
      return SetKeyState(Key::kL, action, mode);
    case GLFW_KEY_M:
      return SetKeyState(Key::kM, action, mode);
    case GLFW_KEY_N:
      return SetKeyState(Key::kN, action, mode);
    case GLFW_KEY_O:
      return SetKeyState(Key::kO, action, mode);
    case GLFW_KEY_P:
      return SetKeyState(Key::kP, action, mode);
    case GLFW_KEY_Q:
      return SetKeyState(Key::kQ, action, mode);
    case GLFW_KEY_R:
      return SetKeyState(Key::kR, action, mode);
    case GLFW_KEY_S:
      return SetKeyState(Key::kS, action, mode);
    case GLFW_KEY_T:
      return SetKeyState(Key::kT, action, mode);
    case GLFW_KEY_U:
      return SetKeyState(Key::kU, action, mode);
    case GLFW_KEY_V:
      return SetKeyState(Key::kV, action, mode);
    case GLFW_KEY_W:
      return SetKeyState(Key::kW, action, mode);
    case GLFW_KEY_X:
      return SetKeyState(Key::kX, action, mode);
    case GLFW_KEY_Y:
      return SetKeyState(Key::kY, action, mode);
    case GLFW_KEY_Z:
      return SetKeyState(Key::kZ, action, mode);
    case GLFW_KEY_LEFT_BRACKET:
      return SetKeyState(Key::kLeftBracket, action, mode);
    case GLFW_KEY_BACKSLASH:
      return SetKeyState(Key::kBackslash, action, mode);
    case GLFW_KEY_RIGHT_BRACKET:
      return SetKeyState(Key::kRightBracket, action, mode);
    case GLFW_KEY_GRAVE_ACCENT:
      return SetKeyState(Key::kGraveAccent, action, mode);
    case GLFW_KEY_WORLD_1:
      return SetKeyState(Key::kWorld1, action, mode);
    case GLFW_KEY_WORLD_2:
      return SetKeyState(Key::kWorld2, action, mode);
    case GLFW_KEY_ESCAPE:
      return SetKeyState(Key::kEscape, action, mode);
    case GLFW_KEY_ENTER:
      return SetKeyState(Key::kEnter, action, mode);
    case GLFW_KEY_TAB:
      return SetKeyState(Key::kTab, action, mode);
    case GLFW_KEY_BACKSPACE:
      return SetKeyState(Key::kBackspace, action, mode);
    case GLFW_KEY_INSERT:
      return SetKeyState(Key::kInsert, action, mode);
    case GLFW_KEY_DELETE:
      return SetKeyState(Key::kDelete, action, mode);
    case GLFW_KEY_RIGHT:
      return SetKeyState(Key::kRight, action, mode);
    case GLFW_KEY_LEFT:
      return SetKeyState(Key::kLeft, action, mode);
    case GLFW_KEY_DOWN:
      return SetKeyState(Key::kDown, action, mode);
    case GLFW_KEY_UP:
      return SetKeyState(Key::kUp, action, mode);
    case GLFW_KEY_PAGE_UP:
      return SetKeyState(Key::kPageUp, action, mode);
    case GLFW_KEY_PAGE_DOWN:
      return SetKeyState(Key::kPageDown, action, mode);
    case GLFW_KEY_HOME:
      return SetKeyState(Key::kHome, action, mode);
    case GLFW_KEY_END:
      return SetKeyState(Key::kEnd, action, mode);
    case GLFW_KEY_CAPS_LOCK:
      return SetKeyState(Key::kCapsLock, action, mode);
    case GLFW_KEY_SCROLL_LOCK:
      return SetKeyState(Key::kScrollLock, action, mode);
    case GLFW_KEY_NUM_LOCK:
      return SetKeyState(Key::kNumLock, action, mode);
    case GLFW_KEY_PRINT_SCREEN:
      return SetKeyState(Key::kPrintScreen, action, mode);
    case GLFW_KEY_PAUSE:
      return SetKeyState(Key::kPause, action, mode);
    case GLFW_KEY_F1:
      return SetKeyState(Key::kF1, action, mode);
    case GLFW_KEY_F2:
      return SetKeyState(Key::kF2, action, mode);
    case GLFW_KEY_F3:
      return SetKeyState(Key::kF3, action, mode);
    case GLFW_KEY_F4:
      return SetKeyState(Key::kF4, action, mode);
    case GLFW_KEY_F5:
      return SetKeyState(Key::kF5, action, mode);
    case GLFW_KEY_F6:
      return SetKeyState(Key::kF6, action, mode);
    case GLFW_KEY_F7:
      return SetKeyState(Key::kF7, action, mode);
    case GLFW_KEY_F8:
      return SetKeyState(Key::kF8, action, mode);
    case GLFW_KEY_F9:
      return SetKeyState(Key::kF9, action, mode);
    case GLFW_KEY_F10:
      return SetKeyState(Key::kF10, action, mode);
    case GLFW_KEY_F11:
      return SetKeyState(Key::kF11, action, mode);
    case GLFW_KEY_F12:
      return SetKeyState(Key::kF12, action, mode);
    case GLFW_KEY_F13:
      return SetKeyState(Key::kF13, action, mode);
    case GLFW_KEY_F14:
      return SetKeyState(Key::kF14, action, mode);
    case GLFW_KEY_F15:
      return SetKeyState(Key::kF15, action, mode);
    case GLFW_KEY_F16:
      return SetKeyState(Key::kF16, action, mode);
    case GLFW_KEY_F17:
      return SetKeyState(Key::kF17, action, mode);
    case GLFW_KEY_F18:
      return SetKeyState(Key::kF18, action, mode);
    case GLFW_KEY_F19:
      return SetKeyState(Key::kF19, action, mode);
    case GLFW_KEY_F20:
      return SetKeyState(Key::kF20, action, mode);
    case GLFW_KEY_F21:
      return SetKeyState(Key::kF21, action, mode);
    case GLFW_KEY_F22:
      return SetKeyState(Key::kF22, action, mode);
    case GLFW_KEY_F23:
      return SetKeyState(Key::kF23, action, mode);
    case GLFW_KEY_F24:
      return SetKeyState(Key::kF24, action, mode);
    case GLFW_KEY_F25:
      return SetKeyState(Key::kF25, action, mode);
    case GLFW_KEY_KP_0:
      return SetKeyState(Key::kKp0, action, mode);
    case GLFW_KEY_KP_1:
      return SetKeyState(Key::kKp1, action, mode);
    case GLFW_KEY_KP_2:
      return SetKeyState(Key::kKp2, action, mode);
    case GLFW_KEY_KP_3:
      return SetKeyState(Key::kKp3, action, mode);
    case GLFW_KEY_KP_4:
      return SetKeyState(Key::kKp4, action, mode);
    case GLFW_KEY_KP_5:
      return SetKeyState(Key::kKp5, action, mode);
    case GLFW_KEY_KP_6:
      return SetKeyState(Key::kKp6, action, mode);
    case GLFW_KEY_KP_7:
      return SetKeyState(Key::kKp7, action, mode);
    case GLFW_KEY_KP_8:
      return SetKeyState(Key::kKp8, action, mode);
    case GLFW_KEY_KP_9:
      return SetKeyState(Key::kKp9, action, mode);
    case GLFW_KEY_KP_DECIMAL:
      return SetKeyState(Key::kKpDecimal, action, mode);
    case GLFW_KEY_KP_DIVIDE:
      return SetKeyState(Key::kKpDivide, action, mode);
    case GLFW_KEY_KP_MULTIPLY:
      return SetKeyState(Key::kKpMultiply, action, mode);
    case GLFW_KEY_KP_SUBTRACT:
      return SetKeyState(Key::kKpSubtract, action, mode);
    case GLFW_KEY_KP_ADD:
      return SetKeyState(Key::kKpAdd, action, mode);
    case GLFW_KEY_KP_ENTER:
      return SetKeyState(Key::kKpEnter, action, mode);
    case GLFW_KEY_KP_EQUAL:
      return SetKeyState(Key::kKpEqual, action, mode);
    case GLFW_KEY_LEFT_SHIFT:
      return SetKeyState(Key::kLeftShift, action, mode);
    case GLFW_KEY_LEFT_CONTROL:
      return SetKeyState(Key::kLeftControl, action, mode);
    case GLFW_KEY_LEFT_ALT:
      return SetKeyState(Key::kLeftAlt, action, mode);
    case GLFW_KEY_LEFT_SUPER:
      return SetKeyState(Key::kLeftSuper, action, mode);
    case GLFW_KEY_RIGHT_SHIFT:
      return SetKeyState(Key::kRightShift, action, mode);
    case GLFW_KEY_RIGHT_CONTROL:
      return SetKeyState(Key::kRightControl, action, mode);
    case GLFW_KEY_RIGHT_ALT:
      return SetKeyState(Key::kRightAlt, action, mode);
    case GLFW_KEY_RIGHT_SUPER:
      return SetKeyState(Key::kRightSuper, action, mode);
    case GLFW_KEY_MENU:
      return SetKeyState(Key::kMenu, action, mode);
  }
}

void ClearKeyState() { gKeyState = {}; }

}  // namespace details

}  // namespace sren
