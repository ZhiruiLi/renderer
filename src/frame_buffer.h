#pragma once

#include <array>

#include "color.h"

namespace sren {

class FrameBuffer {
 public:
  FrameBuffer() = default;
  ~FrameBuffer() = default;

  void Set(int x, int y, Color const &color);
  void Clear();
  void Resize(int width, int height);

  int width() { return width_; }
  int height() { return height_; }
  void *data() { return data_ ? data_.get() : nullptr; }

 private:
  int DataSize() { return width_ * height_ * 3; }

  int width_{};
  int height_{};
  std::unique_ptr<unsigned char[]> data_{};
};

}  // namespace sren
