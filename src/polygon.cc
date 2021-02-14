#include "polygon.h"

#include "object.h"

namespace sren {

Vector4 const &Polygon::Vertex(int i) const {
  return object_->trans_vertexs()[vertex_indexs_[i]];
}

Vector2 const &Polygon::UV(int i) const {
  return object_->uvs()[uv_indexs_[i]];
}

Vector4 const &Polygon::Norm(int i) const {
  return object_->norms()[norm_indexs_[i]];
}

}  // namespace sren
