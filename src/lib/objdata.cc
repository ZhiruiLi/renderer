#include "objdata.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "model.h"

namespace sren {

bool LoadObjFile(std::string const &filename, Model *model) {
  std::vector<Vector3> vertexs{};
  std::vector<Vector2> uvs{};
  std::vector<Vector3> normals{};
  std::vector<Color> colors{};
  std::vector<FaceDataIndex> face_indexs{};

  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail()) return false;
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      Vector3 v;
      for (int i = 0; i < 3; i++) iss >> v[i];
      vertexs.push_back(v);
      Color c = Color::RGB(0x0);
      for (int i = 0; i < 3; i++) iss >> c[i];
      colors.push_back(c);
    } else if (!line.compare(0, 3, "vn ")) {
      iss >> trash >> trash;
      Vector3 n;
      for (int i = 0; i < 3; i++) iss >> n[i];
      normals.push_back(n.Normalize());
    } else if (!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      Vector2 uv;
      for (int i = 0; i < 2; i++) iss >> uv[i];
      uvs.push_back(uv);
    } else if (!line.compare(0, 2, "f ")) {
      int f, t, n;
      iss >> trash;
      int cnt = 0;
      while (iss >> f >> trash >> t >> trash >> n) {
        face_indexs.emplace_back(--f, --t, --n);
        cnt++;
      }
      if (3 != cnt) {
        std::cerr << "Error: the obj file is supposed to be triangulated"
                  << std::endl;
        in.close();
        return false;
      }
    }
  }
  in.close();
  std::cerr << "# v# " << vertexs.size() << " f# " << face_indexs.size()
            << " vt# " << uvs.size() << " vn# " << normals.size() << std::endl;
  model->vertexs() = std::move(vertexs);
  model->uvs() = std::move(uvs);
  model->normals() = std::move(normals);
  model->colors() = std::move(colors);
  model->face_indexs() = std::move(face_indexs);
  return true;
}

}  // namespace sren
