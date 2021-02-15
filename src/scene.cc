#include "scene.h"

#include "draw.h"

namespace sren {

namespace {

void ApplyToAll(Matrix4x4 const &m, std::vector<Vector4> *vertexs) {
  auto &vs = *vertexs;
  for (int i = 0; i < vs.size(); i++) {
    vs[i] = vs[i] * m;
  }
}

void Homogenize(FrameBuffer const &fb, Vector4 *v) {
  float const rhw = 1.0f / v->w();
  v->set_x((v->x() * rhw + 1.0f) * fb.width() * 0.5f);
  v->set_y((v->y() * rhw + 1.0f) * fb.height() * 0.5f);
  v->set_z(v->z() * rhw);
  v->set_w(1.0f);
}

}  // namespace

void Scene::RenderOneObject(Object *obj, FrameBuffer *fb) {
  obj->trans_vertexs() = obj->vertexs();
  ApplyToAll(matrixs::RotateTransform(obj->rotation()), &obj->trans_vertexs());
  ApplyToAll(matrixs::ModelTransform(obj->world_pos()), &obj->trans_vertexs());
  ApplyToAll(camera_.transform_matrix(), &obj->trans_vertexs());
  for (auto &trans_v : obj->trans_vertexs()) {
    Homogenize(*fb, &trans_v);
  }
  for (auto const &poly : obj->polygons()) {
    draw::Triangle(poly, *this, fb);
  }
}

void Scene::Render(FrameBuffer *fb) {
  fb->Clear();
  for (auto &obj : objects_) {
    RenderOneObject(&obj, fb);
  }
}

}  // namespace sren
