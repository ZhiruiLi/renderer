#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <limits>

#include "camera.h"
#include "color.h"
#include "draw2d.h"
#include "frame_buffer.h"
#include "key.h"
#include "matrix.h"
#include "model.h"
#include "object.h"
#include "vector.h"
#include "window.h"

using namespace sren;

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

std::array<Color, 6> simple_colors{
    colors::Red(),    colors::Blue(), colors::Green(),
    colors::Yellow(), colors::Cyan(), colors::Purple(),
};

void RenderPipeline(Object *obj, FrameBuffer *fb) {
  Vector3 const camera_world_coords(1, 5, 0);
  Vector3 const camera_target(0, 0, 5);

  auto const fov_radian = 0.5f * kPI;
  auto const aspect = float(fb->width()) / float(fb->height());
  obj->trans_vertexs() = obj->vertexs();
  auto const world_transform = matrixs::WorldTransform(obj->world_pos());
  ApplyToAll(world_transform, &obj->trans_vertexs());
  auto const view_transform =
      matrixs::ViewTransform(camera_world_coords, camera_target);
  ApplyToAll(view_transform, &obj->trans_vertexs());
  auto const project_transform =
      matrixs::ProjectionTransform(aspect, fov_radian, 0.1f, 100.0f);
  ApplyToAll(project_transform, &obj->trans_vertexs());

  for (auto &trans_v : obj->trans_vertexs()) {
    Homogenize(*fb, &trans_v);
  }

  int i = 0;
  for (auto const &poly : obj->polygons()) {
    // draw2d::Line(poly.Vertex(0), poly.Vertex(1), colors::White(), fb);
    // draw2d::Line(poly.Vertex(1), poly.Vertex(2), colors::White(), fb);
    // draw2d::Line(poly.Vertex(0), poly.Vertex(2), colors::White(), fb);
    auto const color = simple_colors[i % 6];
    draw2d::Triangle(poly.Vertex(0), poly.Vertex(1), poly.Vertex(2), color, fb);
    i++;
  }
}

int main(void) {
  Window window("Test", 800, 600);
  Model model("../asserts/cube/cube.obj");
  // Model model("../asserts/african_head/african_head.obj");
  Object obj(101, "MyObj");
  InitObjectData(model, {0, 0, 5}, &obj);
  window.set_main_loop([&](FrameBuffer *fb) {
    fb->Clear();
    auto &world_pos = obj.world_pos();
    if (IsKeyPress(Key::kEscape)) window.Close();
    if (IsKeyPress(Key::kRight) || IsKeyHold(Key::kRight)) {
      world_pos.set_x(world_pos.x() + 0.1);
    }
    if (IsKeyPress(Key::kLeft) || IsKeyHold(Key::kLeft)) {
      world_pos.set_x(world_pos.x() - 0.1);
    }
    if (IsKeyPress(Key::kUp) || IsKeyHold(Key::kUp)) {
      world_pos.set_y(world_pos.y() + 0.1);
    }
    if (IsKeyPress(Key::kDown) || IsKeyHold(Key::kDown)) {
      world_pos.set_y(world_pos.y() - 0.1);
    }
    if (IsKeyPress(Key::kI) || IsKeyHold(Key::kI)) {
      world_pos.set_z(world_pos.z() + 0.1);
    }
    if (IsKeyPress(Key::kO) || IsKeyHold(Key::kO)) {
      world_pos.set_z(world_pos.z() - 0.1);
    }
    RenderPipeline(&obj, fb);
    if (IsKeyPress(Key::kP)) {
      int i = 0;
      for (auto const &poly : obj.polygons()) {
        i++;
        std::cout << "poly " << i << ":" << poly.Vertex(0) << poly.Vertex(1)
                  << poly.Vertex(2) << std::endl;
      }
    }
  });
  window.Run();
  return 0;
}
