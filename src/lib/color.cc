#include "color.h"

#include <algorithm>

namespace sren {

float Color::Normalize(uint32_t c) {
  return float(std::clamp<uint32_t>(c, 0, 255)) / 255.0f;
}

uint32_t Color::Unnormalize(float c) {
  return std::clamp<uint32_t>(c * 255, 0, 255);
}

}  // namespace sren
