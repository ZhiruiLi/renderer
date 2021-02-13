#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "color.h"
#include "model.h"
#include "vector.h"

namespace sren {

enum class PolygonState {
  kActive = 0x1,
  kClipped = 0x2,
  kBackface = 0x4,
};

class VertexAttr {
 public:
  Vector2 texture_uv;
  Color color;
};

class Polygon {
 public:
  Polygon() = default;
  Polygon(std::vector<Vector4> const *vertexs,
          std::vector<VertexAttr> const *vertex_attrs,
          std::array<int, 3> vertex_indexs)
      : vertexs_(vertexs),
        vertex_attrs_(vertex_attrs),
        vertex_indexs_(vertex_indexs) {}

  PolygonState state() const { return state_; };
  void set_state(PolygonState state) { state_ = state; };

  Vector4 const &vertex(int i) const { return (*vertexs_)[vertex_indexs_[i]]; }

 private:
  PolygonState state_{};
  std::vector<Vector4> const *vertexs_{};
  std::vector<VertexAttr> const *vertex_attrs_{};
  std::array<int, 3> vertex_indexs_{};
};

class Object {
 public:
  Object() = default;
  Object(int id, std::string name, Model const &m)
      : id_{id}, name_{std::move(name)} {
    for (int i = 0; i < m.nverts(); i++) {
      auto const &vert3 = m.verts()[i];
      vertexs_.push_back(Vector4(vert3, 1.0f));
      trans_vertexs_.push_back(Vector4(vert3, 1.0f));
      auto const uv = m.uvs()[i];
      vertex_attrs_.push_back(VertexAttr{uv, m.Diffuse(uv)});
    }
    int idx = 0;
    for (int i = 0; i < m.nfaces(); i++) {
      polygons_.push_back(Polygon(&vertexs_, &vertex_attrs_,
                                  {
                                      m.VertIndex(i, 0),
                                      m.VertIndex(i, 1),
                                      m.VertIndex(i, 2),
                                  }));
    }
  }

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

  Vector4 &world_pos() { return world_pos_; }
  Vector4 const &world_pos() const { return world_pos_; }
  Vector4 &local_dir() { return local_dir_; }
  Vector4 const &local_dir() const { return local_dir_; }
  Vector4 &ux() { return ux_; }
  Vector4 const &ux() const { return ux_; }
  Vector4 &uy() { return uy_; }
  Vector4 const &uy() const { return uy_; }
  Vector4 &uz() { return uz_; }
  Vector4 const &uz() const { return uz_; }

  std::vector<Vector4> &vertexs() { return vertexs_; }
  std::vector<Vector4> const &vertexs() const { return vertexs_; }
  std::vector<Vector4> &trans_vertexs() { return trans_vertexs_; }
  std::vector<Vector4> const &trans_vertexs() const { return trans_vertexs_; }
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
  Vector4 world_pos_{0.0f, 0.0f, 0.0f, 1.0f};
  // 物体在局部坐标系下的旋转角度
  Vector4 local_dir_{0.0f, 0.0f, -1.0f, 1.0f};
  // 记录物体朝向的局部坐标轴
  Vector4 ux_{};
  Vector4 uy_{};
  Vector4 uz_{};
  // 原始物体的顶点
  std::vector<Vector4> vertexs_{};
  // 变换后物体的顶点
  std::vector<Vector4> trans_vertexs_{};
  // 顶点的属性
  std::vector<VertexAttr> vertex_attrs_{};
  // 物体的面信息
  std::vector<Polygon> polygons_{};
};

}  // namespace sren
