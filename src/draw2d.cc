#include "draw2d.h"

#include "vector.h"

namespace sren {

namespace draw2d {

namespace {
void SwapXY(Vector2 *p) {
  float tmp = p->x();
  p->set_x(p->y());
  p->set_y(tmp);
}
}  // namespace

// 画点
void Pixel(Vector2 const &p, Color const &c, FrameBuffer *fb) {
  fb->Set(int(p.x()), int(p.y()), c);
}

// 画线
void Line(Vector2 p0, Vector2 p1, Color const &c, FrameBuffer *fb) {
  bool steep = false;
  auto const diff = (p0 - p1).Abs();
  if (diff.x() < diff.y()) {
    SwapXY(&p0);
    SwapXY(&p1);
    steep = true;
  }
  if (p0.x() > p1.x()) {
    std::swap(p0, p1);
  }
  auto const delta = p1 - p0;
  auto const derror2 = std::abs(delta.y()) * 2;
  auto error2 = decltype(derror2)(0);
  auto y = p0.y();
  for (auto x = p0.x(); x <= p1.x(); x++) {
    if (steep) {
      fb->Set(int(y), int(x), c);
    } else {
      fb->Set(int(x), int(y), c);
    }
    error2 += derror2;
    if (error2 > delta.x()) {
      y += (y1 > y0 ? 1 : -1);
      error2 -= delta.x() * 2;
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
