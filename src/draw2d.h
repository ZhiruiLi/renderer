#pragma once

#include "color.h"
#include "frame_buffer.h"
#include "vector.h"

namespace sren {

// 画点
void DrawPixel(Vector2f const &p, Color const &c, FrameBuffer *fb);

// 画线
void DrawLine(Vector2f p0, Vector2f p1, Color const &c, FrameBuffer *fb);

// 画三角形
void DrawTriangle(Vector2f p0, Vector2f p1, Vector2f p2, Color const &c,
                  FrameBuffer *fb);

}  // namespace sren
