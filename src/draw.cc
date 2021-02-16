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

// Color CalcDirLight(Polygon const &poly, Vector2 const &uv,
//                    DirLight const &light, Scene const &scene) {
//   auto const diffuse_color = poly.Diffuse(uv);
//   Vector3 light_dir = -light.direction().Normalize();
//   // 漫反射着色
//   float diff = std::max(norm_dir * light_dir, 0.0f);
//
//   // 合并结果
//   Vector3 ambient =
//       light.ambient * scene.ambient_strength() *
//   Vector3 diffuse =
//       light.diffuse * diff * Vector3(texture(material.diffuse, TexCoords));
//   return (ambient + diffuse + specular);
// }
//
// inline void IlluminateDirLight(Scene const &scene, Color *c) {
//   for (auto const &light : scene.dir_lights()) {
//     light.Illuminate(scene.ambient_strength(), c);
//   }
// }

inline Vertex InterpVertex(Vertex v1, Vertex v2, float t) {
  v1.uv() *= v1.pos().z();
  v2.uv() *= v2.pos().z();
  auto const interp_pos = Interp(v1.pos(), v2.pos(), t);
  return {
      interp_pos,
      Interp(v1.color(), v2.color(), t),
      Interp(v1.uv(), v2.uv(), t) / interp_pos.z(),
      Interp(v1.normal(), v2.normal(), t),
  };
}

inline Vertex CalcRenderPoint(Vertex const &top, Vertex const &bot, float y) {
  auto const y_diff_total = top.pos().y() - bot.pos().y();
  auto const y_diff_curr = y - bot.pos().y();
  return InterpVertex(bot, top, y_diff_curr / y_diff_total);
}

void RenderOneLine(Trapezoid const &trap, float y, Polygon const &poly,
                   Scene const &scene, FrameBuffer *fb) {
  auto left = CalcRenderPoint(trap.left.top, trap.left.bottom, y);
  auto right = CalcRenderPoint(trap.right.top, trap.right.bottom, y);
  left.uv() *= left.pos().z();
  right.uv() *= right.pos().z();
  auto const width = right.pos().x() - left.pos().x();
  auto step = (right - left) / width;
  for (float x = left.pos().x(); x < right.pos().x(); x++) {
    left += step;
    auto const &pos = left.pos();
    if (scene.render_style() & kRenderTexture) {
      auto uv = left.uv() / left.pos().z();
      auto color = poly.TextureDiffuse(uv);
      fb->Set(pos.x(), pos.y(), pos.z(), color);
    }
    if (scene.render_style() & kRenderColor) {
      auto color = left.color();
      fb->Set(pos.x(), pos.y(), pos.z(), color);
    }
  }
}

void RenderTrapezoid(Trapezoid const &trap, Polygon const &poly,
                     Scene const &scene, FrameBuffer *fb) {
  for (float y = trap.bottom; y < trap.top; y++) {
    if (y >= 0 && y < fb->height()) {
      RenderOneLine(trap, y, poly, scene, fb);
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
  if (scene.render_style() & (kRenderWireframe | kRenderTexture)) {
    std::array<Trapezoid, 2> traps{};
    int const count = trapezoids::CutTriangle(
        {poly.Vertex(0), poly.Vertex(1), poly.Vertex(2)}, &traps);
    if (count >= 1) {
      RenderTrapezoid(traps[0], poly, scene, fb);
    }
    if (count >= 2) {
      RenderTrapezoid(traps[1], poly, scene, fb);
    }
  }
  if (scene.render_style() & kRenderWireframe) {
    Line(poly.Vertex(0).pos(), poly.Vertex(1).pos(), scene.foreground(), fb);
    Line(poly.Vertex(1).pos(), poly.Vertex(2).pos(), scene.foreground(), fb);
    Line(poly.Vertex(0).pos(), poly.Vertex(2).pos(), scene.foreground(), fb);
  }
}

}  // namespace draw

}  // namespace sren
