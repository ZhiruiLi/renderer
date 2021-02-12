#include "draw2d.h"

namespace sren {

namespace draw2d {

namespace {
void SwapXY(Vector2 *p) {
  float tmp = p->x();
  p->set_x(p->y());
  p->set_y(tmp);
}

Vector3 Barycentric(Vector2 pt0, Vector2 pt1, Vector2 pt2, Vector2 p) {
  Vector3 u = Vector3(pt2[0] - pt0[0], pt1[0] - pt0[0], pt0[0] - p[0]) ^
              Vector3(pt2[1] - pt0[1], pt1[1] - pt0[1], pt0[1] - p[1]);
  /* `pts` and `P` has integer value as coordinates
     so `abs(u[2])` < 1 means `u[2]` is 0, that means
     triangle is degenerate, in this case return something with negative
     coordinates */
  if (std::abs(u[2]) < 1) return Vector3(-1, 1, 1);
  return Vector3(1.f - (u.x() + u.y()) / u.z(), u.y() / u.z(), u.x() / u.z());
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
void Triangle(Vector2 pt0, Vector2 pt1, Vector2 pt2, Color const &color,
              FrameBuffer *fb) {
  Vector2 bboxmin(fb->width() - 1, fb->height() - 1);
  Vector2 bboxmax(0, 0);
  Vector2 clamp(fb->width() - 1, fb->height() - 1);
  for (int i = 0; i < 2; i++) {
    bboxmin[i] = std::max(0.0f, std::min(bboxmin[i], pt0[i]));
    bboxmax[i] = std::min(clamp[i], std::max(bboxmax[i], pt0[i]));
    bboxmin[i] = std::max(0.0f, std::min(bboxmin[i], pt1[i]));
    bboxmax[i] = std::min(clamp[i], std::max(bboxmax[i], pt1[i]));
    bboxmin[i] = std::max(0.0f, std::min(bboxmin[i], pt2[i]));
    bboxmax[i] = std::min(clamp[i], std::max(bboxmax[i], pt2[i]));
  }
  Vector2 p{};
  for (p.set_x(bboxmin.x()); p.x() <= bboxmax.x(); p.set_x(p.x() + 1)) {
    for (p.set_y(bboxmin.y()); p.y() <= bboxmax.y(); p.set_y(p.y())) {
      Vector3 bc_screen = Barycentric(pt0, pt1, pt2, p);
      if (bc_screen.x() < 0 || bc_screen.y() < 0 || bc_screen.z() < 0) {
        continue;
      }
      fb->Set(p.x(), p.y(), color);
    }
  }
}

}  // namespace draw2d

}  // namespace sren
