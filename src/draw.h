#pragma once

#include <array>

#include "color.h"
#include "frame_buffer.h"
#include "polygon.h"
#include "trapezoid.h"
#include "vector.h"

namespace sren {

namespace draw {

enum RenderStyle {
  kRenderWireframe = 0x1,
  kRenderColor = 0x2,
  kRenderTexture = 0x4,
};

// 画点
void Pixel(Vector4 p, Color const &c, FrameBuffer *fb);

// 画线
void Line(Vector4 p0, Vector4 p1, Color const &c, FrameBuffer *fb);

// 画三角形
void Triangle(Vector4 p0, Vector4 p1, Vector4 p2, Color const &c,
              FrameBuffer *fb);

void Triangle(Polygon const &poly, unsigned int render_style, FrameBuffer *fb);

}  // namespace draw

}  // namespace sren
