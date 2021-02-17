#include "scene.h"

#include "draw.h"
#include "matrix.h"

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

void FixZ(Matrix4x4 const &proj, Vector4 *v) {
  auto const a = proj[3][2];
  auto const b = proj[2][2];
  v->set_z((v->z() - b) / a);
}

}  // namespace

void Scene::RenderOneObject(Object *obj, FrameBuffer *fb) {
  obj->trans_vertexs() = obj->vertexs();
  obj->trans_normals() = obj->normals();
  auto const rot_matrix = matrixs::RotateTransform(obj->rotation());
  ApplyToAll(rot_matrix, &obj->trans_vertexs());
  ApplyToAll(rot_matrix, &obj->trans_normals());
  ApplyToAll(matrixs::ModelTransform(obj->world_pos()), &obj->trans_vertexs());
  for (auto const &light : dir_lights_) {
    for (auto &poly : obj->polygons()) {
      light.Illuminate(camera_.pos(), light_coefficient_, &poly);
    }
  }
  ApplyToAll(camera_.transform_matrix(), &obj->trans_vertexs());
  for (auto &trans_v : obj->trans_vertexs()) {
    Homogenize(*fb, &trans_v);
    FixZ(camera_.projection_matrix(), &trans_v);
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
