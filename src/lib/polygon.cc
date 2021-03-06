#include "polygon.h"

#include "color.h"
#include "object.h"
#include "vector.h"

namespace sren {

Vertex Polygon::vertex(int i) const {
  return {
      object_->trans_vertexs()[face_indexs_[i].vertex],
      object_->world_vertexs()[face_indexs_[i].vertex],
      object_->model().colors()[face_indexs_[i].vertex],
      object_->model().uvs()[face_indexs_[i].uv],
      object_->trans_normals()[face_indexs_[i].normal],
  };
}

Material const &Polygon::material() const { return object_->material(); }

unsigned int Polygon::render_style() const { return object_->render_style(); }

bool Polygon::is_alpha() const { return object_->is_alpha(); }

}  // namespace sren
