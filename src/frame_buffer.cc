#include "frame_buffer.h"

#include <algorithm>
#include <cassert>

namespace sren {

void FrameBuffer::Set(int x, int y, Color const &color) {
  std::clamp(x, 0, width_ - 1);
  std::clamp(y, 0, height_ - 1);
  int n = y * width_ * 4 + x * 4;
  data_[n] = color.r;
  data_[n + 1] = color.g;
  data_[n + 2] = color.b;
  data_[n + 3] = color.a;
}

void FrameBuffer::Resize(int width, int height) {
  width_ = width;
  height_ = height;
  data_ = std::make_unique<unsigned char[]>(DataSize());
}

void FrameBuffer::Clear() { bzero(data(), DataSize()); }

}  // namespace sren
