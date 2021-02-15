#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <limits>

#include "camera.h"
#include "color.h"
#include "draw.h"
#include "frame_buffer.h"
#include "key.h"
#include "matrix.h"
#include "model.h"
#include "object.h"
#include "scene.h"
#include "vector.h"
#include "window.h"

using namespace sren;

// void ApplyToAll(Matrix4x4 const &m, std::vector<Vector4> *vertexs) {
//   auto &vs = *vertexs;
//   for (int i = 0; i < vs.size(); i++) {
//     vs[i] = vs[i] * m;
//   }
// }
//
// void Homogenize(FrameBuffer const &fb, Vector4 *v) {
//   float const rhw = 1.0f / v->w();
//   v->set_x((v->x() * rhw + 1.0f) * fb.width() * 0.5f);
//   v->set_y((v->y() * rhw + 1.0f) * fb.height() * 0.5f);
//   v->set_z(v->z() * rhw);
//   v->set_w(1.0f);
// }
//
// std::array<Color, 6> simple_colors{
//     colors::Red(),    colors::Blue(), colors::Green(),
//     colors::Yellow(), colors::Cyan(), colors::Purple(),
// };
//
// void RenderPipeline(Object *obj, FrameBuffer *fb) {
//   Vector3 const camera_world_coords(0, 0, 0);
//   Vector3 const camera_target(0, 0, 5);
//
//   auto const fov_radian = 0.5f * kPI;
//   auto const aspect = float(fb->width()) / float(fb->height());
//   obj->trans_vertexs() = obj->vertexs();
//
//   auto const rot = matrixs::RotateTransform(obj->rotation());
//   ApplyToAll(rot, &obj->trans_vertexs());
//   auto const world_transform = matrixs::ModelTransform(obj->world_pos());
//   ApplyToAll(world_transform, &obj->trans_vertexs());
//   auto const view_transform =
//       matrixs::ViewTransform(camera_world_coords, camera_target);
//   ApplyToAll(view_transform, &obj->trans_vertexs());
//   auto const project_transform =
//       matrixs::ProjectionTransform(aspect, fov_radian, 0.1f, 100.0f);
//   ApplyToAll(project_transform, &obj->trans_vertexs());
//
//   for (auto &trans_v : obj->trans_vertexs()) {
//     Homogenize(*fb, &trans_v);
//   }
//
//   int i = 0;
//   for (auto const &poly : obj->polygons()) {
//     // draw::Line(poly.Vertex(0), poly.Vertex(1), colors::White(), fb);
//     // draw::Line(poly.Vertex(1), poly.Vertex(2), colors::White(), fb);
//     // draw::Line(poly.Vertex(0), poly.Vertex(2), colors::White(), fb);
//     // auto const color = simple_colors[i % 6];
//     // draw::Triangle(poly.Vertex(0).pos(), poly.Vertex(1).pos(),
//     //                poly.Vertex(2).pos(), color, fb);
//     draw::Triangle(
//         poly, draw::RenderStyle(draw::kRenderTexture |
//         draw::kRenderWireframe), fb);
//     i++;
//   }
// }
//
bool IsKeyActive(Key k) { return IsKeyPress(k) || IsKeyHold(k); }

void HandleKey(Window *window, Scene *scene) {
  if (IsKeyPress(Key::kEscape)) {
    window->Close();
  }
  for (auto &obj : scene->objects()) {
    auto &world_pos = obj.world_pos();
    auto &rotation = obj.rotation();
    if (IsKeyActive(Key::kRight)) {
      world_pos.set_x(world_pos.x() + 0.1);
    }
    if (IsKeyActive(Key::kLeft)) {
      world_pos.set_x(world_pos.x() - 0.1);
    }
    if (IsKeyActive(Key::kUp)) {
      world_pos.set_y(world_pos.y() + 0.1);
    }
    if (IsKeyActive(Key::kDown)) {
      world_pos.set_y(world_pos.y() - 0.1);
    }
    if (IsKeyActive(Key::kI)) {
      world_pos.set_z(world_pos.z() + 0.1);
    }
    if (IsKeyActive(Key::kO)) {
      world_pos.set_z(world_pos.z() - 0.1);
    }
    if (IsKeyActive(Key::kA)) {
      rotation.set_y(rotation.y() - 0.1);
    }
    if (IsKeyActive(Key::kD)) {
      rotation.set_y(rotation.y() + 0.1);
    }
    if (IsKeyActive(Key::kW)) {
      rotation.set_x(rotation.x() - 0.1);
    }
    if (IsKeyActive(Key::kS)) {
      rotation.set_x(rotation.x() + 0.1);
    }
  }
}

constexpr int kWidth = 800;
constexpr int kHeight = 600;
constexpr float kAspect = float(kWidth) / float(kHeight);

int main(void) {
  Window window("Test", kWidth, kHeight);
  Scene scene{};
  auto &camera = scene.camera();
  camera.SetLookAt({0, 0, 0}, {0, 0, 5});
  camera.SetPerspective(0.5f * kPI, kAspect);

  Model model("../asserts/cube/cube.obj");
  scene.objects().emplace_back(101, "MyObj");
  auto &obj = scene.objects().back();
  InitObjectData(model, {0, 0, 5}, &obj);
  window.set_main_loop([&](FrameBuffer *fb) {
    HandleKey(&window, &scene);
    scene.Render(fb);
  });
  window.Run();
  return 0;
}
