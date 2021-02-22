#include "frame_buffer.h"

#include <algorithm>
#include <limits>

#include "lib/color.h"
#include "math.h"

namespace sren {

int FrameBuffer::data_index(int x, int y) const {
  return y * width_ * 4 + x * 4;
}

int FrameBuffer::z_buffer_index(int x, int y) const { return x + y * width_; }

void FrameBuffer::Set(int x, int y, Color const &color) {
  if (!InBound(x, y)) {
    return;
  }
  int n = data_index(x, y);
  data_[n] = color.r_hex();
  data_[n + 1] = color.g_hex();
  data_[n + 2] = color.b_hex();
  data_[n + 3] = color.a_hex();
}

Color FrameBuffer::Get(int x, int y) {
  if (!InBound(x, y)) {
    return Color{};
  }
  int n = data_index(x, y);
  return Color::RGBA(data_[n], data_[n + 1], data_[n + 2], data_[n + 3]);
}

void FrameBuffer::Set(int x, int y, float z, Color const &color) {
  if (!InBound(x, y)) {
    return;
  }
  z_buffer_[z_buffer_index(x, y)] = z;
  int n = data_index(x, y);
  data_[n] = color.r_hex();
  data_[n + 1] = color.g_hex();
  data_[n + 2] = color.b_hex();
  data_[n + 3] = color.a_hex();
}

void FrameBuffer::Resize(int width, int height) {
  width_ = width;
  height_ = height;
  data_.resize(width * height * 4);
  z_buffer_.resize(width * height);
  Clear();
}

void FrameBuffer::Clear() {
  std::fill(data_.begin(), data_.end(), 0);
  std::fill(z_buffer_.begin(), z_buffer_.end(),
            std::numeric_limits<float>::min());
}

bool FrameBuffer::NeedRender(int x, int y, float z) const {
  return InBound(x, y) && z_buffer_[z_buffer_index(x, y)] < z;
}

bool FrameBuffer::InBound(int x, int y) const {
  if (x < 0 || x >= width_ || y < 0 || y > height_) {
    return false;
  }
  return true;
}

void FrameBuffer::FlipVertically() {
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_ / 2; j++) {
      auto const k = height_ - j - 1;
      SwapAt(i, j, i, k);
    }
  }
}

void FrameBuffer::SwapAt(int x1, int y1, int x2, int y2) {
  auto const idx1 = data_index(x1, y1);
  auto const idx2 = data_index(x2, y2);
  std::swap(data_[idx1], data_[idx2]);
  std::swap(data_[idx1 + 1], data_[idx2 + 1]);
  std::swap(data_[idx1 + 2], data_[idx2 + 2]);
  std::swap(data_[idx1 + 3], data_[idx2 + 3]);
}

}  // namespace sren
