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
        z_buffer_(std::make_unique<float[]>(width * height)) {
    Clear();
  }

  ~FrameBuffer() = default;

  void Set(float x, float y, Color const &color);
  void Set(float x, float y, float z, Color const &color);
  void Clear();
  void Resize(int width, int height);

  int width() const { return width_; }
  int height() const { return height_; }
  int size() const { return width_ * height_ * 4; }
  void *data() { return data_ ? data_.get() : nullptr; }
  void const *data() const { return data_ ? data_.get() : nullptr; }

 private:
  int width_{};
  int height_{};
  std::unique_ptr<unsigned char[]> data_{};
  std::unique_ptr<float[]> z_buffer_{};
};

}  // namespace sren
