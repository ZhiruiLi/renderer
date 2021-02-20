#pragma once

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <stdint.h>

#include <cstddef>
#include <utility>

namespace sren {

// 修饰键
enum class KeyMod {
  kShift,
  kControl,
  kAlt,
  kSuper,
  kCapsLock,
  kNumLock,
};

// 一般按键
enum class Key {
  kSpace,
  kApostrophe,
  kComma,
  kMinus,
  kPeriod,
  kSlash,
  k0,
  k1,
  k2,
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  k9,
  kSemicolon,
  kEqual,
  kA,
  kB,
  kC,
  kD,
  kE,
  kF,
  kG,
  kH,
  kI,
  kJ,
  kK,
  kL,
  kM,
  kN,
  kO,
  kP,
  kQ,
  kR,
  kS,
  kT,
  kU,
  kV,
  kW,
  kX,
  kY,
  kZ,
  kLeftBracket,
  kBackslash,
  kRightBracket,
  kGraveAccent,
  kWorld1,
  kWorld2,
  kEscape,
  kEnter,
  kTab,
  kBackspace,
  kInsert,
  kDelete,
  kRight,
  kLeft,
  kDown,
  kUp,
  kPageUp,
  kPageDown,
  kHome,
  kEnd,
  kCapsLock,
  kScrollLock,
  kNumLock,
  kPrintScreen,
  kPause,
  kF1,
  kF2,
  kF3,
  kF4,
  kF5,
  kF6,
  kF7,
  kF8,
  kF9,
  kF10,
  kF11,
  kF12,
  kF13,
  kF14,
  kF15,
  kF16,
  kF17,
  kF18,
  kF19,
  kF20,
  kF21,
  kF22,
  kF23,
  kF24,
  kF25,
  kKp0,
  kKp1,
  kKp2,
  kKp3,
  kKp4,
  kKp5,
  kKp6,
  kKp7,
  kKp8,
  kKp9,
  kKpDecimal,
  kKpDivide,
  kKpMultiply,
  kKpSubtract,
  kKpAdd,
  kKpEnter,
  kKpEqual,
  kLeftShift,
  kLeftControl,
  kLeftAlt,
  kLeftSuper,
  kRightShift,
  kRightControl,
  kRightAlt,
  kRightSuper,
  kMenu,
  // --------
  kCount,
};

namespace details {

void HandleKey(GLFWwindow *w, int key, int scancode, int action, int mode);

std::pair<uint8_t, uint8_t> const &GetKeyState(Key k);

void ClearKeyState();

bool HasModifier(uint8_t state, KeyMod mod);

template <std::size_t N>
bool HasAllModifiers(uint8_t state, std::array<KeyMod, N> const &mods) {
  for (auto m : mods) {
    if (!HasModifier(state, m)) {
      return false;
    }
  }
  return true;
}

}  // namespace details

inline bool IsKeyPress(Key k) {
  return details::GetKeyState(k).first == GLFW_PRESS + 1;
}

template <std::size_t N>
inline bool IsKeyPress(Key k, std::array<KeyMod, N> const &mods) {
  auto const state = details::GetKeyState(k);
  return state.first == GLFW_PRESS + 1 &&
         details::HasAllModifiers(state.second, mods);
}

inline bool IsKeyRelease(Key k) {
  return details::GetKeyState(k).first == GLFW_RELEASE + 1;
}

template <std::size_t N>
inline bool IsKeyRelease(Key k, std::array<KeyMod, N> const &mods) {
  auto const state = details::GetKeyState(k);
  return state.first == GLFW_RELEASE + 1 &&
         details::HasAllModifiers(state.second, mods);
}

inline bool IsKeyHold(Key k) {
  return details::GetKeyState(k).first == GLFW_REPEAT + 1;
}

template <std::size_t N>
inline bool IsKeyHold(Key k, std::array<KeyMod, N> const &mods) {
  auto const state = details::GetKeyState(k);
  return state.first == GLFW_REPEAT + 1 &&
         details::HasAllModifiers(state.second, mods);
}

inline bool HasModifier(Key k, KeyMod mod) {
  return details::HasModifier(details::GetKeyState(k).second, mod);
}

template <std::size_t N>
inline bool HasModifiers(Key k, std::array<KeyMod, N> const &mods) {
  return details::HasAllModifiers(details::GetKeyState(k).second, mods);
}

}  // namespace sren
