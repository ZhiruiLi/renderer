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

namespace {

Vector3 const kObjectPos = {0, 0, 0};
Vector3 const kObjectPos1 = {0, 0, 0.5};
Vector3 const kCameraPos = {0, 0, 2};
Vector3 const kLightDir = {-3, -3, -3};
LightCoefficient const kCoefficient = {
    0.1f,  // ambient
    1.0f,  // diffuse
    1.0f,  // specular
};

bool gRenderSolid = true;
bool gRenderTranslucency = false;

struct ModelInfo {
  std::string name;
  std::string file_path;
  std::string file_ext;
};

std::vector<ModelInfo> const kModelInfos{
    {"cube", "cube/cube", "png"},
    {"african", "african_head/african_head", "tga"},
    {"diablo", "diablo3/diablo3_pose", "tga"},
};

int gModelIndex = 0;

}  // namespace

bool IsKeyActive(Key k) { return IsKeyPress(k) || IsKeyHold(k); }

void HandleKey(Window *window, Scene *scene) {
  if (IsKeyPress(Key::kEscape)) {
    window->Close();
  }

  for (int i = 0; i < scene->nobjects(); i++) {
    auto &obj = *scene->object(i);
    if (gRenderSolid && i == gModelIndex) {
      obj.set_state(sren::ObjectState::kActive);
    } else {
      obj.set_state(sren::ObjectState::kDisable);
    }

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

  for (int i = 0; i < scene->nalpha_objects(); i++) {
    auto &obj = *scene->alpha_object(i);
    if (gRenderTranslucency) {
      obj.set_state(sren::ObjectState::kActive);
    } else {
      obj.set_state(sren::ObjectState::kDisable);
    }
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
  ImGui::Begin("Info", nullptr);
  ImGui::Checkbox("Render Solid", &gRenderSolid);
  ImGui::SameLine();
  ImGui::Checkbox("Render Translucency", &gRenderTranslucency);
  ImGui::Text("Solid Model");
  for (int i = 0; i < kModelInfos.size(); i++) {
    ImGui::SameLine();
    ImGui::RadioButton(kModelInfos[i].name.c_str(), &gModelIndex, i);
  }
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

  for (auto const &m : kModelInfos) {
    auto const obj = scene.add_object(m.name);
    LoadData(m.file_path, m.file_ext, obj);
    obj->transform().set_world_pos(kObjectPos);
  }

  auto const alpha_obj = scene.add_alpha_object("alpha");
  LoadColorModel(kModelInfos[0].file_path,
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
