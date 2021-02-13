#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace sren {

Model::Model(std::string const &filename)
    : verts_(),
      uv_(),
      norms_(),
      facet_vrt_(),
      facet_tex_(),
      facet_nrm_(),
      diffusemap_(),
      normalmap_(),
      specularmap_() {
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
      norms_.push_back(n.Normalize());
    } else if (!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      Vector2 uv;
      for (int i = 0; i < 2; i++) iss >> uv[i];
      uv_.push_back(uv);
    } else if (!line.compare(0, 2, "f ")) {
      int f, t, n;
      iss >> trash;
      int cnt = 0;
      while (iss >> f >> trash >> t >> trash >> n) {
        facet_vrt_.push_back(--f);
        facet_tex_.push_back(--t);
        facet_nrm_.push_back(--n);
        cnt++;
      }
      if (3 != cnt) {
        std::cerr << "Error: the obj file is supposed to be triangulated"
                  << std::endl;
        in.close();
        return;
      }
    }
  }
  in.close();
  std::cerr << "# v# " << nverts() << " f# " << nfaces() << " vt# "
            << uv_.size() << " vn# " << norms_.size() << std::endl;
  LoadTexture(filename, "_diffuse.tga", diffusemap_);
  LoadTexture(filename, "_nm_tangent.tga", normalmap_);
  LoadTexture(filename, "_spec.tga", specularmap_);
}

int Model::nverts() const { return verts_.size(); }

int Model::nfaces() const { return facet_vrt_.size() / 3; }

int Model::VertIndex(int iface, int nthvert) const {
  return facet_vrt_[iface * 3 + nthvert];
}

Vector3 Model::Vert(int iface, int nthvert) const {
  return verts_[VertIndex(iface, nthvert)];
}

void Model::LoadTexture(std::string const &filename, std::string const &suffix,
                        TGAImage &img) {
  size_t dot = filename.find_last_of(".");
  if (dot == std::string::npos) return;
  std::string texfile = filename.substr(0, dot) + suffix;
  auto const ok = img.ReadFile(texfile.c_str());
  std::cerr << "texture file " << texfile << " loading "
            << (ok ? "ok" : "failed") << std::endl;
  img.FlipVertically();
}

Color Model::Diffuse(Vector2 const &uvf) const {
  return diffusemap_.Get(uvf[0] * diffusemap_.width(),
                         uvf[1] * diffusemap_.height());
}

Vector3 Model::TextureNormal(Vector2 const &uv) const {
  Color c =
      normalmap_.Get(uv[0] * normalmap_.width(), uv[1] * normalmap_.height());
  Vector3 res;
  for (int i = 0; i < 3; i++) res[2 - i] = c[i] / 255. * 2 - 1;
  return res;
}

double Model::Specular(Vector2 const &uvf) const {
  return specularmap_.Get(uvf[0] * specularmap_.width(),
                          uvf[1] * specularmap_.height())[0];
}

Vector2 Model::UV(int iface, int nthvert) const {
  return uv_[facet_tex_[iface * 3 + nthvert]];
}

Vector3 Model::VertexNormal(int iface, int nthvert) const {
  return norms_[facet_nrm_[iface * 3 + nthvert]];
}

}  // namespace sren
