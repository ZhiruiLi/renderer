#include "draw2d.h"

#include "src/color.h"
#include "src/frame_buffer.h"
#include "vector.h"

namespace sren {

namespace draw2d {

namespace {
void SwapXY(Vector2 *p) {
  float const x = p->x();
  p->set_x(p->y());
  p->set_y(x);
}

template <class Vec>
void CenterPos(Vec *p, FrameBuffer *fb) {
  p->set_x(p->x() + fb->width() / 2.0f);
  p->set_y(p->y() + fb->height() / 2.0f);
}

}  // namespace

// 画点
void Pixel(Vector4 p, Color const &c, FrameBuffer *fb) {
  CenterPos(&p, fb);
  fb->Set(int(p.x()), int(p.y()), int(p.z()), c);
}

// 画线
void Line(Vector4 p0, Vector4 p1, Color const &c, FrameBuffer *fb) {
  CenterPos(&p0, fb);
  CenterPos(&p1, fb);
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
void Triangle(Vector4 p0, Vector4 p1, Vector4 p2, Color const &c,
              FrameBuffer *fb) {
  CenterPos(&p0, fb);
  CenterPos(&p1, fb);
  CenterPos(&p2, fb);
  if (AlmostEqual(p0.y(), p1.y()) && AlmostEqual(p0.y(), p2.y())) {
    return;
  }
  if (p0.y() > p1.y()) {
    std::swap(p0, p1);
  }
  if (p0.y() > p2.y()) {
    std::swap(p0, p2);
  }
  if (p1.y() > p2.y()) {
    std::swap(p1, p2);
  }
  auto const total_height = int(p2.y() - p0.y());
  for (int i = 0; i < total_height; i++) {
    bool const second_half = i > p1.y() - p0.y() || p1.y() == p0.y();
    int const segment_height = second_half ? p2.y() - p1.y() : p1.y() - p0.y();
    float const alpha = (float)i / total_height;
    float const beta =
        (float)(i - (second_half ? p1.y() - p0.y() : 0)) / segment_height;
    auto pa = p0 + (p2 - p0) * alpha;
    auto pb = second_half ? p1 + (p2 - p1) * beta : p0 + (p1 - p0) * beta;
    if (pa.x() > pb.x()) {
      std::swap(pa, pb);
    }
    auto const delta_z = (pb.z() - pa.z()) / (pb.x() - pa.x());
    auto z = pa.z() + 1;
    for (int j = pa.x(); j <= pb.x(); j++) {
      fb->Set(j, p0.y() + i, 1 / z, c);
      z += delta_z;
    }
  }
}

}  // namespace draw2d

}  // namespace sren
