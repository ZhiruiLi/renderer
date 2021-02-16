#include "polygon.h"

#include "color.h"
#include "object.h"
#include "vector.h"

namespace sren {

Vertex Polygon::Vertex(int i) const {
  return {
      object_->trans_vertexs()[vertex_indexs_[i]],
      object_->colors()[vertex_indexs_[i]],
      object_->uvs()[uv_indexs_[i]],
      object_->normals()[norm_indexs_[i]],
  };
}

Color Polygon::TextureDiffuse(Vector2 const &uv) const {
  return object_->TextureDiffuse(uv);
}

Vector3 Polygon::TextureNormal(Vector2 const &uv) const {
  return object_->TextureNormal(uv);
}

}  // namespace sren
