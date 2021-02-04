#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "color.h"
#include "point.h"

namespace sren {

class Polygon {
 public:
  Polygon() = default;

  int state() { return state_; };
  void set_state(int state) { state_ = state; };

  int attribute() { return attribute_; };
  void set_attribute(int attribute) { attribute_ = attribute; };

  Color color() { return color_; };
  void set_color(Color color) { color_ = color; };

  std::array<Point4, 3> vertexs() { return vertexs_; }
  void set_vertexs(std::array<Point4, 3> const &vertexs) { vertexs_ = vertexs; }

  std::array<Point4, 3> trans_vertexs() { return trans_vertexs_; }
  void set_trans_vertexs(std::array<Point4, 3> const &vertexs) {
    trans_vertexs_ = vertexs;
  }

 private:
  int state_{};
  int attribute_{};
  Color color_{};
  std::array<Point4, 3> vertexs_{};
  std::array<Point4, 3> trans_vertexs_{};
};

class Object {
 public:
  Object() = default;
  Object(int id, std::string name) : id_{id}, name_{std::move(name)} {}

  int id() const { return id_; }
  void set_id(int id) { id_ = id; }

  std::string const &name() const { return name_; }
  void name(std::string name) { name_ = std::move(name); }

  int state() const { return state_; };
  void set_state(int state) { state_ = state; }
  int attribute() const { return attribute_; }
  void set_attribute(int attribute) { attribute_ = attribute; }
  float avg_radius() const { return avg_radius_; }
  void set_avg_radius(float avg_radius) { avg_radius_ = avg_radius; }
  float max_radius() const { return max_radius_; }
  void set_max_radius(float max_radius) { max_radius_ = max_radius; }
  Point4 world_pos() const { return world_pos_; }
  void set_world_pos(Point4 const &world_pos) { world_pos_ = world_pos; }
  Vector4 local_dir() const { return local_dir_; }
  void set_local_dir(Vector4 const &dir) { local_dir_ = dir; }
  Vector4 ux() const { return ux_; }
  void set_ux(Vector4 const &ux) { ux_ = ux; }
  Vector4 uy() const { return uy_; }
  void set_uy(Vector4 const &uy) { uy_ = uy; }
  Vector4 uz() const { return uz_; }
  void set_uz(Vector4 const &uz) { uz_ = uz; }

  std::vector<Point4> const &vertexs() const { return vertexs_; }
  void set_vertexs(std::vector<Point4> vertexs) {
    vertexs_ = std::move(vertexs);
  }

  std::vector<Point4> const &trans_vertexs() const { return trans_vertexs_; }
  void set_trans_vertexs(std::vector<Point4> trans_vertexs) {
    trans_vertexs_ = std::move(trans_vertexs);
  }

  std::vector<Polygon> const &polygons() const { return polygons_; };
  void set_polygons(std::vector<Polygon> polygons) {
    polygons_ = std::move(polygons);
  }

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
  Point4 world_pos_{0.0f, 0.0f, 0.0f, 0.0f};
  // 物体在局部坐标系下的旋转角度
  Vector4 local_dir_{0.0f, 0.0f, 1.0f, 0.0f};
  // 记录物体朝向的局部坐标轴
  Vector4 ux_{};
  Vector4 uy_{};
  Vector4 uz_{};
  // 原始物体的顶点
  std::vector<Point4> vertexs_{};
  // 变换后物体的顶点
  std::vector<Point4> trans_vertexs_{};
  std::vector<Polygon> polygons_{};
};

inline Object MakeSimpleCube() {
  Object cube(0, "example_cube");
  cube.set_avg_radius(17.3f);
  cube.set_max_radius(17.3f);
  std::vector<Point3> vertex3s{
      {10, 10, 10},     // p0
      {10, 10, -10},    // p1
      {-10, 10, -10},   // p2
      {-10, 10, 10},    // p3
      {10, -10, 10},    // p4
      {-10, -10, 10},   // p5
      {-10, -10, -10},  // p6
      {10, -10, -10},   // p7
  };
  std::vector<Point4> vertex4s{};
  std::transform(vertex3s.begin(), vertex3s.end(), std::back_inserter(vertex4s),
                 [](auto const &p3) { return Point4(p3, 1.0f); });
  cube.set_vertexs(vertex4s);
  cube.set_trans_vertexs(vertex4s);
  return cube;
}

}  // namespace sren
