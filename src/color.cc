#include "color.h"

#include <algorithm>

namespace sren {

float Color::Normalize(uint32_t c) {
  return std::clamp(float(c) / 255, 0.0f, 1.0f);
}

uint32_t Color::Unnormalize(float c) {
  return std::clamp(uint32_t(c * 255), uint32_t(0), uint32_t(255));
}

}  // namespace sren
