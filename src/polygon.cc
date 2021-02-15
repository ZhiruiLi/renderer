#include "polygon.h"

#include "object.h"

namespace sren {

Vertex Polygon::Vertex(int i) const {
  return {
      object_->trans_vertexs()[vertex_indexs_[i]],
      object_->colors()[vertex_indexs_[i]],
      object_->uvs()[uv_indexs_[i]],
      object_->normals()[norm_indexs_[i]],
  };
}

Color Polygon::Diffuse(Vector2 const &uv) const { return object_->Diffuse(uv); }

}  // namespace sren
