#pragma once

#include <array>

#include "color.h"
#include "vector.h"

namespace sren {

class FrameBuffer {
 public:
  FrameBuffer() = default;
  ~FrameBuffer() = default;

  void Draw(Vector2i pos, Color color);
  void Clear();
  int Resize(int width, int height);

  int width() { return width_; }
  int height() { return height_; }
  void *data() { return data_ ? data_.get() : nullptr; }

 private:
  int DataSize() { return width_ * height_ * 4; }

  int width_{};
  int height_{};
  std::unique_ptr<unsigned char[]> data_{};
};

}  // namespace sren
