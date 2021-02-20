#define STB_IMAGE_IMPLEMENTATION
#include "image.h"

#include <cassert>

#include "color.h"
#include "data2d.h"
#include "stb_image.h"

namespace sren {

bool LoadImage(std::string const &path, Data2D *data2d) {
  stbi_set_flip_vertically_on_load(1);
  int width, height, channels;
  auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (!data) {
    return false;
  }
  assert(channels == Color::kGrayScale || channels == Color::kGrayAlpha ||
         channels == Color::kRGB || channels == Color::kRGBA);
  *data2d = Data2D(width, height, channels, data);
  stbi_image_free(data);
  return true;
}

}  // namespace sren
