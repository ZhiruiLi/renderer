#pragma once

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

  void Render(FrameBuffer *fb);

  Camera &camera() { return camera_; }
  Camera const &camera() const { return camera_; }
  std::vector<DirLight> &dir_lights() { return dir_lights_; }
  std::vector<DirLight> const &dir_lights() const { return dir_lights_; }
  std::vector<PointLight> &point_lights() { return point_lights_; }
  std::vector<PointLight> const &point_lights() const { return point_lights_; }
  Color &foreground() { return foreground_; }
  Color const &foreground() const { return foreground_; }
  Color &background() { return background_; }
  Color const &background() const { return background_; }
  std::vector<Object> &objects() { return objects_; }
  std::vector<Object> const &objects() const { return objects_; }
  LightCoefficient &light_coefficient() { return light_coefficient_; }
  LightCoefficient const &light_coefficient() const {
    return light_coefficient_;
  }

 private:
  void RenderOneObject(Object *obj, FrameBuffer *fb);

  Camera camera_{};
  std::vector<DirLight> dir_lights_{};
  std::vector<PointLight> point_lights_{};
  Color foreground_{colors::White()};
  Color background_{colors::Black()};
  std::vector<Object> objects_{};
  LightCoefficient light_coefficient_{};
};

}  // namespace sren
