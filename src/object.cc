#include "object.h"

namespace sren {

void InitObjectData(Model const &m, Vector3 world_pos, Object *obj) {
  obj->world_pos() = world_pos;
  obj->colors() = m.colors();
  obj->diffuse_map() = m.diffuse_map();
  obj->specular_map() = m.specular_map();
  obj->normal_map() = m.normal_map();

  obj->vertexs().clear();
  obj->uvs().clear();
  obj->normals().clear();
  obj->polygons().clear();

  for (auto const &v : m.vertexs()) {
    obj->vertexs().emplace_back(v, 1.0f);
  }
  for (auto const &u : m.uvs()) {
    obj->uvs().emplace_back(u);
  }
  for (auto const &n : m.normals()) {
    obj->normals().emplace_back(n, 1.0f);
  }
  for (int i = 0; i < m.nfaces(); i++) {
    obj->polygons().emplace_back(obj, m.VertexIndexs(i), m.VertexUVIndexs(i),
                                 m.VertexNormalIndexs(i));
  }
  obj->trans_vertexs() = obj->vertexs();
}

}  // namespace sren
