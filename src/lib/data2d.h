#pragma once

#include <cstdint>
#include <vector>

namespace sren {

class Data2D {
 public:
  Data2D() = default;

  Data2D(int width, int height, int bytestep, std::vector<std::uint8_t> data)
      : width_(width),
        height_(height),
        bytestep_(bytestep),
        data_(std::move(data)) {}

  Data2D(int width, int height, int bytestep, std::uint8_t *data)
      : width_(width),
        height_(height),
        bytestep_(bytestep),
        data_(data, data + width * height * bytestep) {}

  std::uint8_t const *Get(int x, int y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
      return data();
    }
    return data() + (x + y * width_) * bytestep_;
  }

  int width() const { return width_; }
  int height() const { return height_; }
  int bytestep() const { return bytestep_; }
  std::uint8_t *data() { return data_.data(); }
  std::uint8_t const *data() const { return data_.data(); }

 private:
  int width_{};
  int height_{};
  int bytestep_{};
  std::vector<std::uint8_t> data_{};
};

}  // namespace sren
