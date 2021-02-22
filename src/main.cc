#include <imgui.h>
#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

#include "lib/camera.h"
#include "lib/color.h"
#include "lib/data2d.h"
#include "lib/draw.h"
#include "lib/frame_buffer.h"
#include "lib/image.h"
#include "lib/key.h"
#include "lib/light.h"
#include "lib/math.h"
#include "lib/matrix.h"
#include "lib/model.h"
#include "lib/objdata.h"
#include "lib/object.h"
#include "lib/quaternion.h"
#include "lib/render_style.h"
#include "lib/scene.h"
#include "lib/vector.h"
#include "lib/window.h"

using namespace sren;

Vector3 const kObjectPos = {0, 0, 0};
Vector3 const kObjectPos1 = {0, 0, 0.5};
Vector3 const kCameraPos = {0, 0, 2};
Vector3 const kLightDir = {-3, -3, -3};
LightCoefficient const kCoefficient = {
    0.1f,  // ambient
    1.0f,  // diffuse
    1.0f,  // specular
};

bool IsKeyActive(Key k) { return IsKeyPress(k) || IsKeyHold(k); }

void HandleKey(Window *window, Scene *scene) {
  if (IsKeyPress(Key::kEscape)) {
    window->Close();
  }

  if (scene->nobjects() > 0) {
    auto &obj = *scene->object(0);
    auto world_pos = obj.transform().world_pos();
    auto rotation = obj.transform().rotation();

    if (IsKeyActive(Key::kRight)) {
      world_pos.set_x(world_pos.x() - 0.1);
    }
    if (IsKeyActive(Key::kLeft)) {
      world_pos.set_x(world_pos.x() + 0.1);
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

    obj.transform().set_world_pos(world_pos);
    obj.transform().set_rotation(rotation);
  }

  if (scene->nalpha_objects() > 0) {
    auto &obj = *scene->alpha_object(0);
    auto rotation = obj.transform().rotation();
    if (IsKeyActive(Key::kJ)) {
      rotation.set_y(rotation.y() - 0.1);
    }
    if (IsKeyActive(Key::kL)) {
      rotation.set_y(rotation.y() + 0.1);
    }
    if (IsKeyActive(Key::kI)) {
      rotation.set_x(rotation.x() - 0.1);
    }
    if (IsKeyActive(Key::kK)) {
      rotation.set_x(rotation.x() + 0.1);
    }
    obj.transform().set_rotation(rotation);
  }
}

void RenderGUI() {
  static int counter = 0;
  ImGui::Begin("Info", nullptr);
  if (ImGui::Button("Button")) counter++;
  ImGui::SameLine();
  ImGui::Text("counter = %d", counter);
  ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
              ImGui::GetIO().Framerate);
  ImGui::End();
}

constexpr int kWidth = 800;
constexpr int kHeight = 600;
constexpr float kAspect = float(kWidth) / float(kHeight);

void LoadData(std::string const &name, std::string const &suffix, Object *obj) {
  auto const prefix = "../../asserts/" + name;
  auto const obj_filename = prefix + ".obj";
  auto const tex_filename = prefix + "_diffuse." + suffix;
  auto const spec_filename = prefix + "_spec." + suffix;
  auto const norm_filename = prefix + "_nm_tangent." + suffix;

  Model model{};
  auto const model_ok = LoadObjFile(obj_filename, &model);
  obj->set_model(model);
  auto &material = obj->material();
  auto const tex_ok = LoadImage(tex_filename, &material.diffuse_map());
  auto const spec_ok = LoadImage(spec_filename, &material.specular_map());
  auto const norm_ok = LoadImage(norm_filename, &material.normal_map());
  std::cout << "load result: model-" << model_ok << ", tex-" << tex_ok
            << ", spec-" << spec_ok << ", norm-" << norm_ok << std::endl;
}

void LoadColorModel(std::string const &name, std::vector<Color> const &cs,
                    Object *obj) {
  auto const prefix = "../../asserts/" + name;
  auto const obj_filename = prefix + ".obj";

  Model model{};
  auto const model_ok = LoadObjFile(obj_filename, &model);
  auto cit = cs.begin();
  for (auto &c : model.colors()) {
    c = *cit;
    cit++;
    if (cit == cs.end()) {
      cit = cs.begin();
    }
  }
  obj->set_model(model);
  std::cout << "load result: model-" << model_ok << std::endl;
}

int main(void) {
  Window window("Test", kWidth, kHeight);
  Scene scene{};
  auto &camera = scene.camera();
  camera.SetLookAt(kCameraPos, kObjectPos);
  camera.SetPerspective(Radian(90.0f), kAspect);
  auto &dir_lights = scene.lights().dir_lights();
  dir_lights.emplace_back(kLightDir, colors::White(), kCoefficient);

  auto const obj = scene.add_object("MyObj");
  LoadData("cube/cube", "png", obj);
  // LoadData("african_head/african_head", "tga", obj);
  // LoadData("diablo3/diablo3_pose", "tga", obj);
  obj->transform().set_world_pos(kObjectPos);

  auto const alpha_obj = scene.add_alpha_object("MyObj1");
  LoadColorModel("cube/cube",
                 {
                     {1.0f, 0.0f, 0.0f, 0.5f},
                     {0.0f, 1.0f, 0.0f, 0.5f},
                     {0.0f, 0.0f, 1.0f, 0.5f},
                 },
                 alpha_obj);
  alpha_obj->transform().set_world_pos(kObjectPos1);
  alpha_obj->set_render_style(kRenderColor);

  window.set_main_loop([&](Window *window) {
    RenderGUI();
    HandleKey(window, &scene);
    scene.Render(&window->frame_buffer());
  });
  window.Run();
  return 0;
}
