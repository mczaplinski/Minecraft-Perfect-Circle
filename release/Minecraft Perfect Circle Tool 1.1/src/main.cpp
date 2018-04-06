#include "CircleCalculator.h"
#include <iostream>

int main(int argc, char *argv[]) {
  CircleCalculator *pCalc = new CircleCalculator();

  while (1) {
    if (pCalc->mainMenu() == false) {
      return EXIT_SUCCESS;
    }
  }
}
