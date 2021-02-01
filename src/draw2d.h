#pragma once

#include "color.h"
#include "frame_buffer.h"
#include "vector.h"

namespace sren {

void DrawPixel(Vector2f const &p, Color const &c, FrameBuffer *fb);
void DrawLine(Vector2f p0, Vector2f p1, Color const &c, FrameBuffer *fb);

}  // namespace sren
