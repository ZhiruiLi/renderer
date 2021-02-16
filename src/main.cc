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
#include "src/math.h"
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

int main1(void) {
  Window window("Test", kWidth, kHeight);
  Scene scene{};
  auto &camera = scene.camera();
  camera.SetLookAt({0, 0, 0}, {0, 0, 5});
  camera.SetPerspective(Radian(90.0f), kAspect);

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
