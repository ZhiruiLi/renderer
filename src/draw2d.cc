#include "draw2d.h"

#include "vector.h"

namespace sren {

namespace draw2d {

namespace {
void SwapXY(Vector2 *p) {
  float const x = p->x();
  p->set_x(p->y());
  p->set_y(x);
}
}  // namespace

// 画点
void Pixel(Vector2 const &p, Color const &c, FrameBuffer *fb) {
  fb->Set(int(p.x()), int(p.y()), c);
}

// 画线
void Line(Vector2 p0, Vector2 p1, Color const &c, FrameBuffer *fb) {
  if (p0.x() == p1.x() && p0.y() == p1.y()) {
    fb->Set(p0.x(), p0.y(), c);
  } else if (p0.x() == p1.x()) {
    int const inc = (p0.y() <= p1.y()) ? 1 : -1;
    int const y0 = p0.y();
    int const y1 = p1.y();
    for (int y = y0; y != y1; y += inc) {
      fb->Set(p0.x(), y, c);
    }
    fb->Set(p1.x(), p1.y(), c);
  } else if (p0.y() == p1.y()) {
    int const inc = (p0.x() <= p1.x()) ? 1 : -1;
    int const x0 = std::floor(p0.x());
    int const x1 = std::floor(p1.x());
    for (int x = x0; x != x1; x += inc) {
      fb->Set(x, p0.y(), c);
    }
    fb->Set(p1.x(), p1.y(), c);
  } else {
    int const dx = std::abs(p1.x() - p0.x());
    int const dy = std::abs(p1.y() - p0.y());
    if (dx >= dy) {
      if (p1.x() < p0.x()) {
        std::swap(p0, p1);
      }
      int rem = 0;
      int const x0 = p0.x();
      int const x1 = p1.x();
      int const y0 = p0.y();
      for (int x = x0, y = y0; x <= x1; x++) {
        fb->Set(x, y, c);
        rem += dy;
        if (rem >= dx) {
          rem -= dx;
          y += (p1.y() >= p0.y()) ? 1 : -1;
          fb->Set(x, y, c);
        }
      }
      fb->Set(p1.x(), p1.y(), c);
    } else {
      if (p1.y() < p0.y()) {
        std::swap(p0, p1);
      }
      int rem = 0;
      int const x0 = p0.x();
      int const y0 = p0.y();
      int const y1 = p1.y();
      for (int x = x0, y = y0; y <= y1; y++) {
        fb->Set(x, y, c);
        rem += dx;
        if (rem >= dy) {
          rem -= dy;
          x += (p1.x() >= p0.x()) ? 1 : -1;
          fb->Set(x, y, c);
        }
      }
      fb->Set(p1.x(), p1.y(), c);
    }
  }
}

// 画三角形
void Triangle(Vector2 t0, Vector2 t1, Vector2 t2, Color const &c,
              FrameBuffer *fb) {
  if (AlmostEqual(t0.y(), t1.y()) && AlmostEqual(t0.y(), t2.y())) {
    return;
  }
  if (t0.y() > t1.y()) {
    std::swap(t0, t1);
  }
  if (t0.y() > t2.y()) {
    std::swap(t0, t2);
  }
  if (t1.y() > t2.y()) {
    std::swap(t1, t2);
  }
  auto const total_height = int(t2.y() - t0.y());
  for (int i = 0; i < total_height; i++) {
    bool const second_half = i > t1.y() - t0.y() || t1.y() == t0.y();
    int const segment_height = second_half ? t2.y() - t1.y() : t1.y() - t0.y();
    float const alpha = (float)i / total_height;
    float const beta =
        (float)(i - (second_half ? t1.y() - t0.y() : 0)) / segment_height;
    auto pa = t0 + (t2 - t0) * alpha;
    auto pb = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
    if (pa.x() > pb.x()) {
      std::swap(pa, pb);
    }
    for (int j = pa.x(); j <= pb.x(); j++) {
      fb->Set(j, t0.y() + i, c);
    }
  }
}

}  // namespace draw2d

}  // namespace sren
