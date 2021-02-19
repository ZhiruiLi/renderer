#include "polygon.h"

#include "color.h"
#include "object.h"
#include "vector.h"

namespace sren {

Vertex Polygon::vertex(int i) const {
  return {
      object_->trans_vertexs()[face_indexs_[i].vertex],
      object_->model().colors()[face_indexs_[i].vertex],
      object_->model().uvs()[face_indexs_[i].uv],
      object_->trans_normals()[face_indexs_[i].normal],
      lights_[i],
  };
}

Material const &Polygon::material() const { return object_->material(); }
void Polygon::set_light(int i, Color const &c) { lights_[i] = c; }
Color const &Polygon::light(int i) const { return lights_[i]; }

}  // namespace sren
