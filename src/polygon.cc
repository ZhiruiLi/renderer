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
      object_->trans_normals()[norm_indexs_[i]],
      lights_[i],
  };
}

Color Polygon::TextureDiffuse(Vector2 const &uv) const {
  return object_->TextureDiffuse(uv);
}

Vector3 Polygon::TextureNormal(Vector2 const &uv) const {
  return object_->TextureNormal(uv);
}

Polygon &Polygon::SetLight(int i, Color const &c) {
  lights_[i] = c;
  return *this;
}

Color const &Polygon::Light(int i) const { return lights_[i]; }

}  // namespace sren
