#include "CircleCalculator.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Minecraft Perfect Circle Tool v" << VERSION_MAJOR << "."
            << VERSION_MINOR << std::endl;

  CircleCalculator *pCalc = new CircleCalculator();

  while (1) {
    if (pCalc->Run() == false) {
      break;
    }
  }

  return 0;
}
