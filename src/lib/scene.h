#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "color.h"
#include "frame_buffer.h"
#include "light.h"
#include "object.h"

namespace sren {

class Scene {
 public:
  Scene() = default;

  Scene(Scene const &) = delete;
  void operator=(Scene const &) = delete;

  void Render(FrameBuffer *fb);

  Camera &camera() { return camera_; }
  Camera const &camera() const { return camera_; }
  Color &foreground() { return foreground_; }
  Color const &foreground() const { return foreground_; }
  Color &background() { return background_; }
  Color const &background() const { return background_; }

  int nobjects() const { return objects_.size(); }
  Object *object(int i) { return objects_[i].get(); }
  Object const *object(int i) const { return objects_[i].get(); }
  Object *add_object(std::string name) {
    auto obj = std::make_unique<Object>(id_++, std::move(name), false);
    objects_.push_back(std::move(obj));
    return objects_.back().get();
  }

  int nalpha_objects() const { return alpha_objects_.size(); }
  Object *alpha_object(int i) { return alpha_objects_[i].get(); }
  Object const *alpha_object(int i) const { return alpha_objects_[i].get(); }
  Object *add_alpha_object(std::string name) {
    auto obj = std::make_unique<Object>(id_++, std::move(name), true);
    alpha_objects_.push_back(std::move(obj));
    return alpha_objects_.back().get();
  }

  Lights &lights() { return lights_; }
  Lights const &lights() const { return lights_; }

 private:
  void RenderOneObject(Object *obj, FrameBuffer *fb);

  int id_{100};
  Camera camera_{};
  Color foreground_{colors::White()};
  Color background_{colors::Black()};
  std::vector<std::unique_ptr<Object>> objects_{};
  std::vector<std::unique_ptr<Object>> alpha_objects_{};
  Lights lights_{};
};

}  // namespace sren
