#pragma once

#include "color.h"
#include "frame_buffer.h"
#include "vector.h"

namespace sren {

namespace draw2d {

// 画点
void Pixel(Vector2 p, Color const &c, FrameBuffer *fb);

// 画线
void Line(Vector2 p0, Vector2 p1, Color const &c, FrameBuffer *fb);

// 画三角形
void Triangle(Vector2 p0, Vector2 p1, Vector2 p2, Color const &c,
              FrameBuffer *fb);

}  // namespace draw2d

}  // namespace sren
