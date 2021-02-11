#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "src/vector.h"

namespace sren {

Model::Model(std::string_view filename) : verts_(), faces_() {
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
      for (int i = 0; i < 3; i++) iss >> v.data()[i];
      verts_.push_back(v);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<int> f;
      int itrash, idx;
      iss >> trash;
      while (iss >> idx >> trash >> itrash >> trash >> itrash) {
        idx--;  // in wavefront obj all indices start at 1, not zero
        f.push_back(idx);
      }
      faces_.push_back(f);
    }
  }
  std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}

int Model::nverts() const { return (int)verts_.size(); }

int Model::nfaces() const { return (int)faces_.size(); }

std::vector<int> const &Model::face(int i) const { return faces_[i]; }

std::vector<int> &Model::face(int i) { return faces_[i]; }

Vector3 const &Model::vert(int i) const { return verts_[i]; }

Vector3 &Model::vert(int i) { return verts_[i]; }

}  // namespace sren
