#include <iostream>

#include "window.h"

int main() {
  sren::Window window("Test", 300, 200);
  window.set_main_loop([](sren::FrameBuffer *buff) {
    buff->Clear();
    for (int i = 0; i < buff->width() / 2; i++) {
      for (int j = 0; j < buff->height() / 3; j++) {
        buff->Draw({i, j}, {255, 0, 0});
      }
    }
  });
  window.Run();
}
