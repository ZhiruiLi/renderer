#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace sren {

Model::Model(const char *filename) : verts_(), faces_(), norms_(), uv_() {
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail()) return;
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      Vector3 v;
      for (int i = 0; i < 3; i++) iss >> v[i];
      verts_.push_back(v);
    } else if (!line.compare(0, 3, "vn ")) {
      iss >> trash >> trash;
      Vector3 n;
      for (int i = 0; i < 3; i++) iss >> n[i];
      norms_.push_back(n);
    } else if (!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      Vector2 uv;
      for (int i = 0; i < 2; i++) iss >> uv[i];
      uv_.push_back(uv);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<Vector3> f;
      Vector3 tmp;
      iss >> trash;
      while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
        for (int i = 0; i < 3; i++)
          tmp[i]--;  // in wavefront obj all indices start at 1, not zero
        f.push_back(tmp);
      }
      faces_.push_back(f);
    }
  }
  std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << " vt# "
            << uv_.size() << " vn# " << norms_.size() << std::endl;
  load_texture(filename, "_diffuse.tga", diffusemap_);
}

Model::~Model() {}

int Model::nverts() const { return (int)verts_.size(); }

int Model::nfaces() const { return (int)faces_.size(); }

std::vector<int> Model::face(int idx) const {
  std::vector<int> face;
  for (int i = 0; i < (int)faces_[idx].size(); i++)
    face.push_back(faces_[idx][i][0]);
  return face;
}

Vector3 Model::vert(int i) const { return verts_[i]; }

void Model::load_texture(std::string filename, const char *suffix,
                         TGAImage &img) {
  std::string texfile(filename);
  size_t dot = texfile.find_last_of(".");
  if (dot != std::string::npos) {
    texfile = texfile.substr(0, dot) + std::string(suffix);
    std::cerr << "texture file " << texfile << " loading "
              << (img.ReadFile(texfile.c_str()) ? "ok" : "failed") << std::endl;
    img.FlipVertically();
  }
}

Color Model::diffuse(Vector2 uv) const {
  return diffusemap_.Get(uv.x(), uv.y());
}

Vector2 Model::uv(int iface, int nvert) const {
  int idx = faces_[iface][nvert][1];
  return Vector2(uv_[idx].x() * diffusemap_.width(),
                 uv_[idx].y() * diffusemap_.height());
}

}  // namespace sren
