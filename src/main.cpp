#include "window.hpp"

int main() {
  Window win = Window();
  win.initialize();
  win.transferDataToGPUMemory();
  win.render();
  win.deleteDataFromGPUMemory();
  win.terminate();
  return 0;
}
