#pragma once

#include "color.h"
#include "frame_buffer.h"
#include "polygon.h"
#include "vector.h"

namespace sren {

class Scene;

namespace details {

// 计算插值：t 为 [0, 1] 之间的数值
inline float Interp(float x1, float x2, float t) { return x1 + (x2 - x1) * t; }

// 计算类容器对象的插值
template <class C>
inline C Interp(C const &c1, C const &c2, typename C::value_type t) {
  assert(c1.size() == c2.size());
  C ret{};
  for (int i = 0; i < c1.size(); i++) {
    ret[i] = Interp(c1[i], c2[i], t);
  }
  return ret;
}

}  // namespace details

namespace draw {

// 画点
void Pixel(Vector4 p, Color const &c, FrameBuffer *fb);

// 画线
void Line(Vector4 p0, Vector4 p1, Color const &c, FrameBuffer *fb);

// 画三角形
void Triangle(Polygon const &poly, Scene const &scene, FrameBuffer *fb);

}  // namespace draw

}  // namespace sren
