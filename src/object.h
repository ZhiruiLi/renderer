#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "color.h"
#include "model.h"
#include "polygon.h"
#include "vector.h"

namespace sren {

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
  Vector3 &rotation() { return rotation_; }
  Vector3 const &rotation() const { return rotation_; }

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
  Vector3 rotation_{0.0f, 0.0f, 0.0f};
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
