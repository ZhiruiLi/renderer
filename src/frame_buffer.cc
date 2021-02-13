#include "frame_buffer.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <memory>

#include "math.h"

namespace sren {

void FrameBuffer::Set(int x, int y, Color const &color) {
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

void FrameBuffer::Set(int x, int y, int z, Color const &color) {
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
  z_buffer_ = std::make_unique<int[]>(width * height);
  ResetZBuffer();
}

void FrameBuffer::Clear() { bzero(data(), size()); }

void FrameBuffer::ResetZBuffer() {
  std::fill(z_buffer_.get(), z_buffer_.get() + width_ * height_,
            std::numeric_limits<int>::min());
}

}  // namespace sren
