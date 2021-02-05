#include "draw2d.h"

#include "point.h"

namespace sren {

// 画点
void DrawPixel(Point2 const &p, Color const &c, FrameBuffer *fb) {
  fb->Set(int(p.x()), int(p.y()), c);
}

// 画线
void DrawLine(Point2 p0, Point2 p1, Color const &c, FrameBuffer *fb) {
  bool steep = false;
  auto diff = p0 - p1;
  diff.SetAbs();
  if (diff.x() < diff.y()) {
    std::swap(p0.x(), p0.y());
    std::swap(p1.x(), p1.y());
    steep = true;
  }
  if (p0.x() > p1.x()) {
    std::swap(p0, p1);
  }
  auto const dx = p1.x() - p0.x();
  auto const dy = p1.y() - p0.y();
  auto const derror2 = std::abs(dy) * 2;
  auto error2 = decltype(derror2)(0);
  auto y = p0.y();
  for (auto x = p0.x(); x <= p1.x(); x++) {
    if (steep) {
      fb->Set(int(y), int(x), c);
    } else {
      fb->Set(int(x), int(y), c);
    }
    error2 += derror2;
    if (error2 > dx) {
      y += (y1 > y0 ? 1 : -1);
      error2 -= dx * 2;
    }
  }
}

// 画三角形
void DrawTriangle(Point2 t0, Point2 t1, Point2 t2, Color const &c,
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

}  // namespace sren
