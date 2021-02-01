#include <iostream>

#include "draw2d.h"
#include "window.h"

auto const red = sren::Color(255, 0, 0);
int main() {
  sren::Window window("Test", 300, 200);
  window.set_main_loop([](sren::FrameBuffer *fb) {
    fb->Clear();
    sren::DrawTriangle({50.0f, 60.0f}, {30.0f, 40.0f}, {30.0f, 50.0f}, red, fb);
    sren::DrawTriangle({299.0f, 199.0f}, {99.0f, 99.0f}, {0.0f, 0.0f}, red, fb);
    sren::DrawLine({0.0f, 0.0f}, {99.0f, 99.0f}, red, fb);
    sren::DrawLine({299.0f, 199.0f}, {0.0f, 0.0f}, red, fb);
  });
  window.Run();
}
