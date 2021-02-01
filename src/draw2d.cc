#include "draw2d.h"
namespace sren {

void DrawPixel(Vector2f const &p, Color const &c, FrameBuffer *fb) {
  fb->Set(int(p.x), int(p.y), c);
}

void DrawLine(Vector2f p0, Vector2f p1, Color const &c, FrameBuffer *fb) {
  bool steep = false;
  auto const diff = Abs(p0 - p1);
  if (diff.x < diff.y) {
    std::swap(p0.x, p0.y);
    std::swap(p1.x, p1.y);
    steep = true;
  }
  if (p0.x > p1.x) {
    std::swap(p0, p1);
  }
  auto const dx = p1.x - p0.x;
  auto const dy = p1.y - p0.y;
  auto const derror2 = std::abs(dy) * 2;
  auto error2 = decltype(derror2)(0);
  auto y = p0.y;
  for (auto x = p0.x; x <= p1.x; x++) {
    if (steep) {
      fb->Set(y, x, c);
    } else {
      fb->Set(x, y, c);
    }
    error2 += derror2;
    if (error2 > dx) {
      y += (y1 > y0 ? 1 : -1);
      error2 -= dx * 2;
    }
  }
}

}  // namespace sren
