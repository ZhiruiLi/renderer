#include "draw.h"

#include <array>

#include "color.h"
#include "frame_buffer.h"
#include "render_style.h"
#include "scene.h"
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

void PreInterpFix(Vertex *v) {
  v->color() *= v->pos().z();
  v->uv() *= v->pos().z();
}

inline Vertex InterpVertex(Vertex v1, Vertex v2, float t) {
  PreInterpFix(&v1);
  PreInterpFix(&v2);
  auto const interp_pos = Interp(v1.pos(), v2.pos(), t);
  auto const interp_wpos = Interp(v1.world_pos(), v2.world_pos(), t);
  auto const interp_color = Interp(v1.color(), v2.color(), t) / interp_pos.z();
  auto const interp_uv = Interp(v1.uv(), v2.uv(), t) / interp_pos.z();
  auto const interp_norm = Interp(v1.normal(), v2.normal(), t);
  return {interp_pos, interp_wpos, interp_color, interp_uv, interp_norm};
}

inline Vertex CalcRenderPoint(Vertex const &top, Vertex const &bot, float y) {
  auto const y_diff_total = top.pos().y() - bot.pos().y();
  auto const y_diff_curr = y - bot.pos().y();
  return InterpVertex(bot, top, y_diff_curr / y_diff_total);
}

void RenderOneLine(Trapezoid const &trap, float y, Polygon const &poly,
                   Vector3 const &camera_pos, Lights const &lights,
                   FrameBuffer *fb) {
  auto left = CalcRenderPoint(trap.left.top, trap.left.bottom, y);
  auto right = CalcRenderPoint(trap.right.top, trap.right.bottom, y);
  int const rightx = std::round(right.pos().x());
  PreInterpFix(&left);
  PreInterpFix(&right);
  auto const width = right.pos().x() - left.pos().x();
  auto const step = (right - left) / width;
  for (int leftx = left.pos().x(); leftx < rightx; leftx++) {
    left += step;
    auto vert = left;
    vert.uv() /= left.pos().z();
    int const x = vert.pos().x();
    int const y = vert.pos().y();
    float const z = vert.pos().z();
    if (!fb->NeedRender(x, y, z)) {
      continue;
    }
    if (poly.render_style() & kRenderTexture) {
      auto color = lights.Illuminate(vert, poly.material(), camera_pos);
      fb->Set(x, y, z, color);
    }
    if (poly.render_style() & kRenderColor) {
      auto color = lights.Illuminate(vert, vert.color(), camera_pos);
      fb->Set(x, y, z, color);
    }
  }
}

void RenderTrapezoid(Trapezoid const &trap, Polygon const &poly,
                     Scene const &scene, FrameBuffer *fb) {
  for (float y = trap.bottom; y < trap.top; y++) {
    if (y >= 0 && y < fb->height()) {
      RenderOneLine(trap, y, poly, scene.camera().pos(), scene.lights(), fb);
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
void Triangle(Polygon const &poly, Scene const &scene, FrameBuffer *fb) {
  if (poly.render_style() & (kRenderColor | kRenderTexture)) {
    std::array<Trapezoid, 2> traps{};
    int const count = trapezoids::CutTriangle(
        {poly.vertex(0), poly.vertex(1), poly.vertex(2)}, &traps);
    if (count >= 1) {
      RenderTrapezoid(traps[0], poly, scene, fb);
    }
    if (count >= 2) {
      RenderTrapezoid(traps[1], poly, scene, fb);
    }
  }
  if (poly.render_style() & kRenderWireframe) {
    Line(poly.vertex(0).pos(), poly.vertex(1).pos(), scene.foreground(), fb);
    Line(poly.vertex(1).pos(), poly.vertex(2).pos(), scene.foreground(), fb);
    Line(poly.vertex(0).pos(), poly.vertex(2).pos(), scene.foreground(), fb);
  }
}

}  // namespace draw

}  // namespace sren
