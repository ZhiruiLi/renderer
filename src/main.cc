#include <iostream>

#include "draw2d.h"
#include "window.h"

int main() {
  sren::Window window("Test", 300, 200);
  window.set_main_loop([](sren::FrameBuffer *fb) {
    fb->Clear();
    sren::DrawLine({0.0f, 0.0f}, {99.0f, 99.0f}, {255, 0, 0}, fb);
    sren::DrawLine({299.0f, 199.0f}, {0.0f, 0.0f}, {255, 0, 0}, fb);
  });
  window.Run();
}
