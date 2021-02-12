#include "tgaimage.h"

#include <math.h>
#include <string.h>
#include <time.h>

#include <fstream>
#include <iostream>

namespace sren {

namespace {

#pragma pack(push, 1)
struct TGA_Header {
  char idlength;
  char colormaptype;
  char datatypecode;
  short colormaporigin;
  short colormaplength;
  char colormapdepth;
  short x_origin;
  short y_origin;
  short width;
  short height;
  char bitsperpixel;
  char imagedescriptor;
};
#pragma pack(pop)

struct TGAColor {
  union {
    struct {
      unsigned char b, g, r, a;
    };
    unsigned char raw[4];
    unsigned int val;
  };
  int bytespp;

  TGAColor() : val(0), bytespp(1) {}

  TGAColor(Color const &c)
      : b(c.b()), g(c.g()), r(c.r()), a(c.a()), bytespp(4) {}

  TGAColor(unsigned char vr, unsigned char vg, unsigned char vb,
           unsigned char va = 255)
      : b(vb), g(vg), r(vr), a(va), bytespp(4) {}

  TGAColor(int v, int bpp) : val(v), bytespp(bpp) {}

  TGAColor(TGAColor const &c) : val(c.val), bytespp(c.bytespp) {}

  TGAColor(unsigned char const *p, int bpp) : val(0), bytespp(bpp) {
    for (int i = 0; i < bpp; i++) {
      raw[i] = p[i];
    }
  }

  TGAColor &operator=(TGAColor const &c) {
    if (this != &c) {
      bytespp = c.bytespp;
      val = c.val;
    }
    return *this;
  }

  Color ToColor() const {
    switch (bytespp) {
      case 1:
        return Color::RGB(b, b, b);
      case 3:
        return Color::RGB(r, g, b);
    }
    return Color::RGBA(r, g, b, a);
  }
};
}  // namespace

TGAImage::TGAImage() : data(NULL), width_(0), height_(0), bytespp_(0) {}

TGAImage::TGAImage(int w, int h, int bpp)
    : data(NULL), width_(w), height_(h), bytespp_(bpp) {
  unsigned long nbytes = width_ * height_ * bytespp_;
  data = new unsigned char[nbytes];
  memset(data, 0, nbytes);
}

TGAImage::TGAImage(TGAImage const &img) {
  width_ = img.width_;
  height_ = img.height_;
  bytespp_ = img.bytespp_;
  unsigned long nbytes = width_ * height_ * bytespp_;
  data = new unsigned char[nbytes];
  memcpy(data, img.data, nbytes);
}

TGAImage::~TGAImage() {
  if (data) delete[] data;
}

TGAImage &TGAImage::operator=(TGAImage const &img) {
  if (this != &img) {
    if (data) delete[] data;
    width_ = img.width_;
    height_ = img.height_;
    bytespp_ = img.bytespp_;
    unsigned long nbytes = width_ * height_ * bytespp_;
    data = new unsigned char[nbytes];
    memcpy(data, img.data, nbytes);
  }
  return *this;
}

bool TGAImage::ReadFile(char const *filename) {
  if (data) delete[] data;
  data = NULL;
  std::ifstream in;
  in.open(filename, std::ios::binary);
  if (!in.is_open()) {
    std::cerr << "can't open file " << filename << "\n";
    in.close();
    return false;
  }
  TGA_Header header;
  in.read((char *)&header, sizeof(header));
  if (!in.good()) {
    in.close();
    std::cerr << "an error occured while reading the header\n";
    return false;
  }
  width_ = header.width;
  height_ = header.height;
  bytespp_ = header.bitsperpixel >> 3;
  if (width_ <= 0 || height_ <= 0 ||
      (bytespp_ != GRAYSCALE && bytespp_ != RGB && bytespp_ != RGBA)) {
    in.close();
    std::cerr << "bad bpp (or width/height) value\n";
    return false;
  }
  unsigned long nbytes = bytespp_ * width_ * height_;
  data = new unsigned char[nbytes];
  if (3 == header.datatypecode || 2 == header.datatypecode) {
    in.read((char *)data, nbytes);
    if (!in.good()) {
      in.close();
      std::cerr << "an error occured while reading the data\n";
      return false;
    }
  } else if (10 == header.datatypecode || 11 == header.datatypecode) {
    if (!LoadRleData(in)) {
      in.close();
      std::cerr << "an error occured while reading the data\n";
      return false;
    }
  } else {
    in.close();
    std::cerr << "unknown file format " << (int)header.datatypecode << "\n";
    return false;
  }
  if (!(header.imagedescriptor & 0x20)) {
    FlipVertically();
  }
  if (header.imagedescriptor & 0x10) {
    FlipHorizontally();
  }
  std::cerr << width_ << "x" << height_ << "/" << bytespp_ * 8 << "\n";
  in.close();
  return true;
}

bool TGAImage::LoadRleData(std::ifstream &in) {
  unsigned long pixelcount = width_ * height_;
  unsigned long currentpixel = 0;
  unsigned long currentbyte = 0;
  TGAColor colorbuffer;
  do {
    unsigned char chunkheader = 0;
    chunkheader = in.get();
    if (!in.good()) {
      std::cerr << "an error occured while reading the data\n";
      return false;
    }
    if (chunkheader < 128) {
      chunkheader++;
      for (int i = 0; i < chunkheader; i++) {
        in.read((char *)colorbuffer.raw, bytespp_);
        if (!in.good()) {
          std::cerr << "an error occured while reading the header\n";
          return false;
        }
        for (int t = 0; t < bytespp_; t++)
          data[currentbyte++] = colorbuffer.raw[t];
        currentpixel++;
        if (currentpixel > pixelcount) {
          std::cerr << "Too many pixels read\n";
          return false;
        }
      }
    } else {
      chunkheader -= 127;
      in.read((char *)colorbuffer.raw, bytespp_);
      if (!in.good()) {
        std::cerr << "an error occured while reading the header\n";
        return false;
      }
      for (int i = 0; i < chunkheader; i++) {
        for (int t = 0; t < bytespp_; t++)
          data[currentbyte++] = colorbuffer.raw[t];
        currentpixel++;
        if (currentpixel > pixelcount) {
          std::cerr << "Too many pixels read\n";
          return false;
        }
      }
    }
  } while (currentpixel < pixelcount);
  return true;
}

bool TGAImage::WriteFile(char const *filename, bool rle) const {
  unsigned char developer_area_ref[4] = {0, 0, 0, 0};
  unsigned char extension_area_ref[4] = {0, 0, 0, 0};
  unsigned char footer[18] = {'T', 'R', 'U', 'E', 'V', 'I', 'S', 'I', 'O',
                              'N', '-', 'X', 'F', 'I', 'L', 'E', '.', '\0'};
  std::ofstream out;
  out.open(filename, std::ios::binary);
  if (!out.is_open()) {
    std::cerr << "can't open file " << filename << "\n";
    out.close();
    return false;
  }
  TGA_Header header;
  memset((void *)&header, 0, sizeof(header));
  header.bitsperpixel = bytespp_ << 3;
  header.width = width_;
  header.height = height_;
  header.datatypecode =
      (bytespp_ == GRAYSCALE ? (rle ? 11 : 3) : (rle ? 10 : 2));
  header.imagedescriptor = 0x20;  // top-left origin
  out.write((char *)&header, sizeof(header));
  if (!out.good()) {
    out.close();
    std::cerr << "can't dump the tga file\n";
    return false;
  }
  if (!rle) {
    out.write((char *)data, width_ * height_ * bytespp_);
    if (!out.good()) {
      std::cerr << "can't unload raw data\n";
      out.close();
      return false;
    }
  } else {
    if (!UnloadRleData(out)) {
      out.close();
      std::cerr << "can't unload rle data\n";
      return false;
    }
  }
  out.write((char *)developer_area_ref, sizeof(developer_area_ref));
  if (!out.good()) {
    std::cerr << "can't dump the tga file\n";
    out.close();
    return false;
  }
  out.write((char *)extension_area_ref, sizeof(extension_area_ref));
  if (!out.good()) {
    std::cerr << "can't dump the tga file\n";
    out.close();
    return false;
  }
  out.write((char *)footer, sizeof(footer));
  if (!out.good()) {
    std::cerr << "can't dump the tga file\n";
    out.close();
    return false;
  }
  out.close();
  return true;
}

// TODO: it is not necessary to break a raw chunk for two equal pixels (for the
// matter of the resulting size)
bool TGAImage::UnloadRleData(std::ofstream &out) const {
  unsigned char const max_chunk_length = 128;
  unsigned long npixels = width_ * height_;
  unsigned long curpix = 0;
  while (curpix < npixels) {
    unsigned long chunkstart = curpix * bytespp_;
    unsigned long curbyte = curpix * bytespp_;
    unsigned char run_length = 1;
    bool raw = true;
    while (curpix + run_length < npixels && run_length < max_chunk_length) {
      bool succ_eq = true;
      for (int t = 0; succ_eq && t < bytespp_; t++) {
        succ_eq = (data[curbyte + t] == data[curbyte + t + bytespp_]);
      }
      curbyte += bytespp_;
      if (1 == run_length) {
        raw = !succ_eq;
      }
      if (raw && succ_eq) {
        run_length--;
        break;
      }
      if (!raw && !succ_eq) {
        break;
      }
      run_length++;
    }
    curpix += run_length;
    out.put(raw ? run_length - 1 : run_length + 127);
    if (!out.good()) {
      std::cerr << "can't dump the tga file\n";
      return false;
    }
    out.write((char *)(data + chunkstart),
              (raw ? run_length * bytespp_ : bytespp_));
    if (!out.good()) {
      std::cerr << "can't dump the tga file\n";
      return false;
    }
  }
  return true;
}

Color TGAImage::Get(int x, int y) const {
  if (!data || x < 0 || y < 0 || x >= width_ || y >= height_) {
    return Color();
  }
  return TGAColor(data + (x + y * width_) * bytespp_, bytespp_).ToColor();
}

bool TGAImage::Set(int x, int y, Color c) {
  if (!data || x < 0 || y < 0 || x >= width_ || y >= height_) {
    return false;
  }
  memcpy(data + (x + y * width_) * bytespp_, TGAColor(c).raw, bytespp_);
  return true;
}

int TGAImage::bytespp() const { return bytespp_; }

int TGAImage::width() const { return width_; }

int TGAImage::height() const { return height_; }

bool TGAImage::FlipHorizontally() {
  if (!data) return false;
  int half = width_ >> 1;
  for (int i = 0; i < half; i++) {
    for (int j = 0; j < height_; j++) {
      Color c1 = Get(i, j);
      Color c2 = Get(width_ - 1 - i, j);
      Set(i, j, c2);
      Set(width_ - 1 - i, j, c1);
    }
  }
  return true;
}

bool TGAImage::FlipVertically() {
  if (!data) return false;
  unsigned long bytes_per_line = width_ * bytespp_;
  unsigned char *line = new unsigned char[bytes_per_line];
  int half = height_ >> 1;
  for (int j = 0; j < half; j++) {
    unsigned long l1 = j * bytes_per_line;
    unsigned long l2 = (height_ - 1 - j) * bytes_per_line;
    memmove((void *)line, (void *)(data + l1), bytes_per_line);
    memmove((void *)(data + l1), (void *)(data + l2), bytes_per_line);
    memmove((void *)(data + l2), (void *)line, bytes_per_line);
  }
  delete[] line;
  return true;
}

unsigned char *TGAImage::buffer() const { return data; }

void TGAImage::Clear() { memset((void *)data, 0, width_ * height_ * bytespp_); }

bool TGAImage::Scale(int w, int h) {
  if (w <= 0 || h <= 0 || !data) return false;
  unsigned char *tdata = new unsigned char[w * h * bytespp_];
  int nscanline = 0;
  int oscanline = 0;
  int erry = 0;
  unsigned long nlinebytes = w * bytespp_;
  unsigned long olinebytes = width_ * bytespp_;
  for (int j = 0; j < height_; j++) {
    int errx = width_ - w;
    int nx = -bytespp_;
    int ox = -bytespp_;
    for (int i = 0; i < width_; i++) {
      ox += bytespp_;
      errx += w;
      while (errx >= (int)width_) {
        errx -= width_;
        nx += bytespp_;
        memcpy(tdata + nscanline + nx, data + oscanline + ox, bytespp_);
      }
    }
    erry += h;
    oscanline += olinebytes;
    while (erry >= (int)height_) {
      if (erry >= (int)height_ << 1)  // it means we jump over a scanline
        memcpy(tdata + nscanline + nlinebytes, tdata + nscanline, nlinebytes);
      erry -= height_;
      nscanline += nlinebytes;
    }
  }
  delete[] data;
  data = tdata;
  width_ = w;
  height_ = h;
  return true;
}

}  // namespace sren
