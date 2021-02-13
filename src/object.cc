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

void InitObjectData(Model const &m, Vector3 world_pos, Object *obj) {
  obj->world_pos() = world_pos;
  obj->vertexs().clear();
  obj->uvs().clear();
  obj->norms().clear();
  obj->polygons().clear();

  for (auto const &v : m.vertexs()) {
    obj->vertexs().emplace_back(v, 1.0f);
  }
  for (auto const &u : m.uvs()) {
    obj->uvs().emplace_back(u);
  }
  for (auto const &n : m.norms()) {
    obj->norms().emplace_back(n, 1.0f);
  }
  for (int i = 0; i < m.nfaces(); i++) {
    obj->polygons().emplace_back(obj, m.VertexIndexs(i), m.VertexUVIndexs(i),
                                 m.VertexNormalIndexs(i));
  }
  obj->trans_vertexs() = obj->vertexs();
}
}  // namespace sren
