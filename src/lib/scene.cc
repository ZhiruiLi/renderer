#include "scene.h"

#include "camera.h"
#include "draw.h"
#include "matrix.h"
#include "polygon.h"

namespace sren {

namespace {

auto const kNdcCameraVector = Vector3(0, 0, 1);

void BackFaceCuting(Polygon *poly) {
  if (poly->normal() * kNdcCameraVector < 0) {
    poly->set_state(PolygonState::kActive);
  } else {
    poly->set_state(PolygonState::kBackface);
  }
}

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
  obj->ResetWorldVertexs();
  obj->ResetTransNormals();
  obj->ResetTransVertexs();
  auto const &transform = obj->transform();
  ApplyToAll(transform.rotate_matrix(), &obj->trans_normals());
  ApplyToAll(transform.model_matrix(), &obj->trans_vertexs());
  ApplyToAll(transform.model_matrix(), &obj->world_vertexs());
  ApplyToAll(camera_.transform_matrix(), &obj->trans_vertexs());
  for (auto &trans_v : obj->trans_vertexs()) {
    Homogenize(*fb, &trans_v);
    FixZ(camera_.projection_matrix(), &trans_v);
  }
  for (auto &poly : obj->polygons()) {
    BackFaceCuting(&poly);
    if (poly.state() == PolygonState::kActive) {
      draw::Triangle(poly, *this, fb);
    }
  }
}

void Scene::Render(FrameBuffer *fb) {
  fb->Clear();
  for (auto &obj : objects_) {
    RenderOneObject(&obj, fb);
  }
}

}  // namespace sren
