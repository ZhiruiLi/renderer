#pragma once

#include <array>
#include <memory>

#include "color.h"

namespace sren {

class FrameBuffer {
 public:
  FrameBuffer() = default;
  FrameBuffer(int width, int height)
      : width_(width),
        height_(height),
        data_(std::make_unique<unsigned char[]>(size())),
        z_buffer_(std::make_unique<int[]>(width * height)) {
    ResetZBuffer();
  }

  ~FrameBuffer() = default;

  void Set(int x, int y, int z, Color const &color);
  void Clear();

  int width() { return width_; }
  int height() { return height_; }
  void *data() { return data_ ? data_.get() : nullptr; }
  int size() { return width_ * height_ * 4; }

  void Resize(int width, int height);

 private:
  void ResetZBuffer();

  int width_{};
  int height_{};
  std::unique_ptr<unsigned char[]> data_{};
  std::unique_ptr<int[]> z_buffer_{};
};

}  // namespace sren
