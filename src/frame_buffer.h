#pragma once

#include <array>
#include <memory>

#include "color.h"

namespace sren {

class FrameBuffer {
 public:
  FrameBuffer() = default;
  FrameBuffer(int width, int height)
      : width_{width},
        height_{height},
        data_{std::make_unique<unsigned char[]>(size())} {}
  ~FrameBuffer() = default;

  void Set(int x, int y, Color const &color);
  void Clear();

  int width() { return width_; }
  int height() { return height_; }
  void *data() { return data_ ? data_.get() : nullptr; }
  int size() { return width_ * height_ * 3; }

  void Resize(int width, int height);

 private:
  int width_{};
  int height_{};
  std::unique_ptr<unsigned char[]> data_{};
};

}  // namespace sren
