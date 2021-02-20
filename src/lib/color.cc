#include "color.h"

#include <algorithm>

#include "math.h"

namespace sren {

float Color::Normalize(uint32_t c) {
  return float(Clamp<uint32_t>(0, 255, c)) / 255.0f;
}

uint32_t Color::Unnormalize(float c) {
  return Clamp<uint32_t>(0, 255, c * 255);
}

}  // namespace sren
