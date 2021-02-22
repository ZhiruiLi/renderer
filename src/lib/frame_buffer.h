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

  void Set(int x, int y, Color const &color);
  void Set(int x, int y, float z, Color const &color);
  Color Get(int x, int y);
  void Clear();
  void Resize(int width, int height);
  bool NeedRender(int x, int y, float z) const;
  void FlipVertically();

  int width() const { return width_; }
  int height() const { return height_; }
  int size() const { return data_.size(); }
  std::uint8_t *data() { return data_.data(); }
  std::uint8_t const *data() const { return data_.data(); }

 private:
  bool InBound(int x, int y) const;
  void SwapAt(int x1, int y1, int x2, int y2);

  int data_index(int x, int y) const;
  int z_buffer_index(int x, int y) const;

  int width_{};
  int height_{};
  std::vector<std::uint8_t> data_{};
  std::vector<float> z_buffer_{};
};

}  // namespace sren
