#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include "color.h"

namespace sren {

class FrameBuffer {
 public:
  FrameBuffer() = default;
  FrameBuffer(int width, int height) : width_(width), height_(height) {
    Resize(width, height);
  }

  ~FrameBuffer() = default;

  void Set(float x, float y, Color const &color);
  void Set(float x, float y, float z, Color const &color);
  void Clear();
  void Resize(int width, int height);

  int width() const { return width_; }
  int height() const { return height_; }
  int size() const { return data_.size(); }
  std::uint8_t *data() { return data_.data(); }
  std::uint8_t const *data() const { return data_.data(); }

 private:
  int width_{};
  int height_{};
  std::vector<std::uint8_t> data_{};
  std::vector<float> z_buffer_{};
};

}  // namespace sren
