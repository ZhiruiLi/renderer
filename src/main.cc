#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <limits>

#include "camera.h"
#include "color.h"
#include "draw.h"
#include "frame_buffer.h"
#include "key.h"
#include "math.h"
#include "matrix.h"
#include "model.h"
#include "object.h"
#include "scene.h"
#include "vector.h"
#include "window.h"

using namespace sren;

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
    if (IsKeyActive(Key::kQ)) {
      world_pos.set_z(world_pos.z() + 0.1);
    }
    if (IsKeyActive(Key::kE)) {
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
  auto &light_dir = scene->dir_lights().back().direction();
  if (IsKeyActive(Key::kJ)) {
    light_dir.set_y(light_dir.y() - 0.1);
  }
  if (IsKeyActive(Key::kL)) {
    light_dir.set_y(light_dir.y() + 0.1);
  }
  if (IsKeyActive(Key::kI)) {
    light_dir.set_x(light_dir.x() - 0.1);
  }
  if (IsKeyActive(Key::kK)) {
    light_dir.set_x(light_dir.x() + 0.1);
  }
}

constexpr int kWidth = 800;
constexpr int kHeight = 600;
constexpr float kAspect = float(kWidth) / float(kHeight);

int main(void) {
  Window window("Test", kWidth, kHeight);
  Scene scene{};
  scene.light_coefficient().ambient = 0.1f;
  scene.light_coefficient().diffuse = 1.0f;
  auto &camera = scene.camera();
  camera.SetLookAt({0, 0, 0}, {0, 0, 5});
  camera.SetPerspective(Radian(90.0f), kAspect);
  scene.dir_lights().emplace_back(DirLight(Vector4(0, 0, 10), colors::White(),
                                           colors::White(), colors::White()));

  // Model model("../../asserts/cube/cube.obj");
  // Model model("../../asserts/diablo3/diablo3_pose.obj");
  Model model("../../asserts/african_head/african_head.obj");
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
