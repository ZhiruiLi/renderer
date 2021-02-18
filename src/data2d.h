#pragma once

#include <cstdint>
#include <vector>

namespace sren {

class Data2D {
 public:
  Data2D() = default;
  Data2D(int width, int height, int bytespp, std::vector<std::uint8_t> data)
      : width_(width),
        height_(height),
        bytespp_(bytespp),
        data_(std::move(data)) {}

  std::uint8_t const *Get(int x, int y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
      return data_.data();
    }
    return data() + (x + y * width_) * bytespp_;
  }

  int width() const { return width_; }
  int height() const { return height_; }
  int bytespp() const { return bytespp_; }
  std::uint8_t *data() { return data_.data(); }
  std::uint8_t const *data() const { return data_.data(); }

 private:
  int width_{};
  int height_{};
  int bytespp_{};
  std::vector<std::uint8_t> data_{};
};

}  // namespace sren
