#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "color.h"
#include "model.h"
#include "vector.h"
#include "vertex.h"

namespace sren {

enum class PolygonState {
  kUnknown = 0x0,
  kActive = 0x1,
  kClipped = 0x2,
  kBackface = 0x4,
};

class Object;

class Polygon {
 public:
  Polygon() = default;
  Polygon(Object *object, std::array<int, 3> vertex_indexs,
          std::array<int, 3> uv_indexs, std::array<int, 3> norm_indexs)
      : object_(object),
        vertex_indexs_(vertex_indexs),
        uv_indexs_(uv_indexs),
        norm_indexs_(norm_indexs) {}

  PolygonState state() const { return state_; };
  void set_state(PolygonState state) { state_ = state; };

  Vector4 const &Vertex(int i) const;
  Vector2 const &UV(int i) const;
  Vector4 const &Norm(int i) const;

 private:
  PolygonState state_{};
  std::array<int, 3> vertex_indexs_{};
  std::array<int, 3> uv_indexs_{};
  std::array<int, 3> norm_indexs_{};
  Object *object_{};
};

class Object {
 public:
  Object() = default;
  Object(int id, std::string name) : id_{id}, name_{std::move(name)} {}

  int id() const { return id_; }
  void set_id(int id) { id_ = id; }

  std::string const &name() const { return name_; }
  void set_name(std::string name) { name_ = std::move(name); }
  int state() const { return state_; };
  void set_state(int state) { state_ = state; }
  int attribute() const { return attribute_; }
  void set_attribute(int attribute) { attribute_ = attribute; }
  float avg_radius() const { return avg_radius_; }
  void set_avg_radius(float avg_radius) { avg_radius_ = avg_radius; }
  float max_radius() const { return max_radius_; }
  void set_max_radius(float max_radius) { max_radius_ = max_radius; }

  Vector3 &world_pos() { return world_pos_; }
  Vector3 const &world_pos() const { return world_pos_; }
  Vector3 &local_dir() { return local_dir_; }
  Vector3 const &local_dir() const { return local_dir_; }

  std::vector<Vector4> &vertexs() { return vertexs_; }
  std::vector<Vector4> const &vertexs() const { return vertexs_; }
  std::vector<Vector4> &trans_vertexs() { return trans_vertexs_; }
  std::vector<Vector4> const &trans_vertexs() const { return trans_vertexs_; }
  std::vector<Vector2> &uvs() { return uvs_; }
  std::vector<Vector2> const &uvs() const { return uvs_; }
  std::vector<Vector4> &norms() { return norms_; }
  std::vector<Vector4> const &norms() const { return norms_; }
  std::vector<Polygon> &polygons() { return polygons_; };
  std::vector<Polygon> const &polygons() const { return polygons_; };

 private:
  int id_{};
  std::string name_{};
  int state_{};
  int attribute_{};
  // 平均半径
  float avg_radius_{};
  // 最大半径
  float max_radius_{};
  // 物体在世界坐标系中的位置
  Vector3 world_pos_{0.0f, 0.0f, 0.0f};
  // 物体在局部坐标系下的旋转角度
  Vector3 local_dir_{0.0f, 0.0f, -1.0f};
  // 原始物体的顶点
  std::vector<Vector4> vertexs_{};
  // 变换后物体的顶点
  std::vector<Vector4> trans_vertexs_{};
  // 物体相关的 UV 坐标
  std::vector<Vector2> uvs_{};
  // 物体相关的法线
  std::vector<Vector4> norms_{};
  // 物体的面
  std::vector<Polygon> polygons_{};
};

void InitObjectData(Model const &m, Vector3 world_pos, Object *obj);

}  // namespace sren
