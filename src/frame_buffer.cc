#include "frame_buffer.h"

#include <algorithm>
#include <cassert>
#include <memory>

namespace sren {

void FrameBuffer::Set(int x, int y, Color const &color) {
  std::clamp(x, 0, width_ - 1);
  std::clamp(y, 0, height_ - 1);
  int n = y * width_ * 3 + x * 3;
  data_[n] = color.r();
  data_[n + 1] = color.g();
  data_[n + 2] = color.b();
}

void FrameBuffer::Resize(int width, int height) {
  width_ = width;
  height_ = height;
  data_ = std::make_unique<unsigned char[]>(size());
}

void FrameBuffer::Clear() { bzero(data(), size()); }

}  // namespace sren
