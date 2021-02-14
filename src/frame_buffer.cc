#include "frame_buffer.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <memory>

#include "math.h"

namespace sren {

void FrameBuffer::Set(float fx, float fy, Color const &color) {
  int x = int(fx);
  int y = int(fy);
  if (x < 0 || x >= width_ || y < 0 || y > height_) {
    return;
  }
  auto const idx = x + y * width_;
  int n = y * width_ * 4 + x * 4;
  data_[n] = color.r_hex();
  data_[n + 1] = color.g_hex();
  data_[n + 2] = color.b_hex();
  data_[n + 3] = color.a_hex();
}

void FrameBuffer::Set(float fx, float fy, float z, Color const &color) {
  int x = int(fx);
  int y = int(fy);
  if (x < 0 || x >= width_ || y < 0 || y > height_) {
    return;
  }
  auto const idx = x + y * width_;
  auto &bufz = (z_buffer_.get())[idx];
  if (bufz > z) {
    return;
  }
  bufz = z;
  int n = y * width_ * 4 + x * 4;
  data_[n] = color.r_hex();
  data_[n + 1] = color.g_hex();
  data_[n + 2] = color.b_hex();
  data_[n + 3] = color.a_hex();
}

void FrameBuffer::Resize(int width, int height) {
  width_ = width;
  height_ = height;
  data_ = std::make_unique<unsigned char[]>(size());
  z_buffer_ = std::make_unique<float[]>(width * height);
  Clear();
}

void FrameBuffer::Clear() {
  auto const count = width_ * height_ * 4;
  for (int i = 0; i < count; i += 4) {
    for (int j = 0; j < 4; j++) {
      data_[i + j] = background_[j];
    }
  }
  std::fill(z_buffer_.get(), z_buffer_.get() + width_ * height_,
            std::numeric_limits<float>::min());
}

}  // namespace sren
