#include "frame_buffer.h"

#include <GLFW/glfw3.h>

namespace sren {

void FrameBuffer::Draw(Vector2f pos, Color color) {
  int n = pos.y * width_ * 4 + pos.x * 4;
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
