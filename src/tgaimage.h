#pragma once

#include <fstream>

#include "color.h"

namespace sren {

class TGAImage {
 private:
  unsigned char *data;
  int width_;
  int height_;
  int bytespp_;

  bool LoadRleData(std::ifstream &in);
  bool UnloadRleData(std::ofstream &out) const;

 public:
  enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

  TGAImage();
  TGAImage(int w, int h, int bpp);
  TGAImage(TGAImage const &img);
  ~TGAImage();

  bool ReadFile(const char *filename);
  bool WriteFile(const char *filename, bool rle = true) const;
  bool FlipHorizontally();
  bool FlipVertically();
  bool Scale(int w, int h);
  Color Get(int x, int y) const;
  bool Set(int x, int y, Color c);
  void Clear();
  TGAImage &operator=(const TGAImage &img);
  int width() const;
  int height() const;
  int bytespp() const;
  unsigned char *buffer() const;
};

}  // namespace sren
