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
  Color &foreground() { return foreground_; }
  Color const &foreground() const { return foreground_; }
  Color &background() { return background_; }
  Color const &background() const { return background_; }
  std::vector<Object> &objects() { return objects_; }
  std::vector<Object> const &objects() const { return objects_; }
  Lights &lights() { return lights_; }
  Lights const &lights() const { return lights_; }

 private:
  void RenderOneObject(Object *obj, FrameBuffer *fb);

  Camera camera_{};
  Color foreground_{colors::White()};
  Color background_{colors::Black()};
  std::vector<Object> objects_{};
  Lights lights_{};
};

}  // namespace sren
