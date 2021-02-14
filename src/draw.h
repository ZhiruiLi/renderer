#pragma once

#include <array>

#include "color.h"
#include "frame_buffer.h"
#include "polygon.h"
#include "trapezoid.h"
#include "vector.h"

namespace sren {

namespace draw {

namespace details {

void SwapXY(Vector2 *p);
// 计算插值：t 为 [0, 1] 之间的数值
float Interp(float x1, float x2, float t);
Vector2 InterpUV(Vector2 const &uv1, Vector2 const &uv2, float t);
Vector4 InterpPos(Vector4 const &pos1, Vector4 const &pos2, float t);
void RenderTrapezoid(Trapezoid const &trap, FrameBuffer *fb);

}  // namespace details

// 画点
void Pixel(Vector4 p, Color const &c, FrameBuffer *fb);

// 画线
void Line(Vector4 p0, Vector4 p1, Color const &c, FrameBuffer *fb);

// 画三角形
void Triangle(Vector4 p0, Vector4 p1, Vector4 p2, Color const &c,
              FrameBuffer *fb);

void Triangle(Polygon const &poly, FrameBuffer *fb);

}  // namespace draw

}  // namespace sren
