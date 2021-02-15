#include "draw.h"

#include <array>

#include "color.h"
#include "draw_helper.h"
#include "frame_buffer.h"
#include "trapezoid.h"
#include "vector.h"

namespace sren {

using namespace details;

namespace draw {

namespace {

void SwapXY(Vector2 *p) {
  float const x = p->x();
  p->set_x(p->y());
  p->set_y(x);
}

inline Vertex InterpVertex(Vertex v1, Vertex v2, float t) {
  auto const z1 = v1.pos().z();
  auto const z2 = v2.pos().z();
  v1.pos().set_z(1 / z1);
  v2.pos().set_z(1 / z2);
  v1.uv() /= z1;
  v2.uv() /= z2;
  auto const interp_pos = InterpVector(v1.pos(), v2.pos(), t);
  return {
      interp_pos,
      InterpColor(v1.color(), v2.color(), t),
      InterpVector(v1.uv(), v2.uv(), t) / interp_pos.z(),
      InterpVector(v1.normal(), v2.normal(), t),
  };
}

inline Vertex CalcRenderPoint(Vertex const &top, Vertex const &bot, float y) {
  auto const y_diff_total = top.pos().y() - bot.pos().y();
  auto const y_diff_curr = y - bot.pos().y();
  return InterpVertex(bot, top, y_diff_curr / y_diff_total);
}
void RenderOneLine(Trapezoid trap, float y, Polygon const &poly,
                   RenderStyle style, FrameBuffer *fb) {
  auto left = CalcRenderPoint(trap.left.top, trap.left.bottom, y);
  auto right = CalcRenderPoint(trap.right.top, trap.right.bottom, y);
  auto const width = right.pos().x() - left.pos().x();
  auto step = (right - left) / width;
  for (float x = left.pos().x(); x < right.pos().x(); x++) {
    left += step;
    auto const &pos = left.pos();
    if (style & kRenderTexture) {
      fb->Set(pos.x(), pos.y(), pos.z(), poly.Diffuse(left.uv()));
    }
    if (style & kRenderColor) {
      fb->Set(pos.x(), pos.y(), pos.z(), left.color());
    }
  }
}

void RenderTrapezoid(Trapezoid const &trap, Polygon const &poly,
                     RenderStyle style, FrameBuffer *fb) {
  for (float y = trap.bottom; y < trap.top; y++) {
    if (y >= 0 && y < fb->height()) {
      RenderOneLine(trap, y, poly, style, fb);
    }
    if (y >= fb->height()) {
      break;
    }
  }
}

}  // namespace

// 画点
void Pixel(Vector4 p, Color const &c, FrameBuffer *fb) {
  fb->Set(int(p.x()), int(p.y()), int(p.z()), c);
}

// 画线
void Line(Vector4 p0, Vector4 p1, Color const &c, FrameBuffer *fb) {
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
    pa.set_z(1 / pa.z());
    pb.set_z(1 / pb.z());
    auto const delta_z = (pb.z() - pa.z()) / (pb.x() - pa.x());
    auto z = pa.z();
    for (int j = pa.x(); j <= pb.x(); j++) {
      fb->Set(j, p0.y() + i, z, c);
      z += delta_z;
    }
  }
}

// 画三角形
void Triangle(Polygon const &poly, RenderStyle style, FrameBuffer *fb) {
  if (style & (kRenderWireframe | kRenderTexture)) {
    std::array<Trapezoid, 2> traps{};
    int const count = trapezoids::CutTriangle(
        {poly.Vertex(0), poly.Vertex(1), poly.Vertex(2)}, &traps);
    if (count >= 1) {
      RenderTrapezoid(traps[0], poly, style, fb);
    }
    if (count >= 2) {
      RenderTrapezoid(traps[1], poly, style, fb);
    }
  }
  if (style & kRenderWireframe) {
    Line(poly.Vertex(0).pos(), poly.Vertex(1).pos(), fb->foreground(), fb);
    Line(poly.Vertex(1).pos(), poly.Vertex(2).pos(), fb->foreground(), fb);
    Line(poly.Vertex(0).pos(), poly.Vertex(2).pos(), fb->foreground(), fb);
  }
}

}  // namespace draw

}  // namespace sren
