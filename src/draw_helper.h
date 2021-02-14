#pragma once

#include "vector.h"
#include "vertex.h"

namespace sren {
namespace details {

// 计算插值：t 为 [0, 1] 之间的数值
inline float Interp(float x1, float x2, float t) { return x1 + (x2 - x1) * t; }

template <class T, std::size_t N>
inline Vector<T, N> InterpVector(Vector<T, N> const &v1, Vector<T, N> const &v2,
                                 T t) {
  Vector<T, N> ret{};
  for (int i = 0; i < N; i++) {
    ret[i] = Interp(v1[i], v2[i], t);
  }
  return ret;
}

inline Vector4 InterpColor(Color const &pos1, Color const &pos2, float t) {
  return {
      Interp(pos1.r(), pos2.r(), t),
      Interp(pos1.g(), pos2.g(), t),
      Interp(pos1.b(), pos2.b(), t),
      Interp(pos1.a(), pos2.a(), t),
  };
}

inline Vertex InterpVertex(Vertex const &v1, Vertex const &v2, float t) {
  return {
      InterpVector(v1.pos(), v2.pos(), t),
      InterpColor(v1.color(), v2.color(), t),
      InterpVector(v1.uv(), v2.uv(), t),
      InterpVector(v1.normal(), v2.normal(), t),
  };
}

inline Vertex CalcRenderPoint(Vertex const &top, Vertex const &bot, float y) {
  auto const y_diff_total = top.pos().y() - bot.pos().y();
  auto const y_diff_curr = y - bot.pos().y();
  return InterpVertex(bot, top, y_diff_curr / y_diff_total);
}

}  // namespace details
}  // namespace sren
