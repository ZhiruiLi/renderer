#pragma once

#include "color.h"
#include "frame_buffer.h"
#include "point.h"

namespace sren {

// 画点
void DrawPixel(Point2 const &p, Color const &c, FrameBuffer *fb);

// 画线
void DrawLine(Point2 p0, Point2 p1, Color const &c, FrameBuffer *fb);

// 画三角形
void DrawTriangle(Point2 p0, Point2 p1, Point2 p2, Color const &c,
                  FrameBuffer *fb);

}  // namespace sren
