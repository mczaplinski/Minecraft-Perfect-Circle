#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

bool requestValues(int &diameter, float &roundnessFactor) {

  char cDiameter[10] = "";
  char cRoundnessFactor[10] = "";

  std::cout << "(0 to exit) Insert d=2r=  ";
  fflush(stdin);
  std::cin.sync();
  std::cin >> cDiameter;
  std::cout << std::endl;
  std::string sDiameter = (std::string)cDiameter;

  if (sDiameter == "0") {
    return false;
  }

  std::cout << "Insert roundness (good: 0.275, max. 0.4999)= ";
  fflush(stdin);
  std::cin.sync();
  std::cin >> cRoundnessFactor;
  std::cout << std::endl;
  std::string sRoundnessFactor = (std::string)cRoundnessFactor;

  if (sRoundnessFactor != "") {
    roundnessFactor = std::stof(sRoundnessFactor);
  } else {
    roundnessFactor = 0;
  }

  diameter = std::stoi(sDiameter);

  return true;
}

void CalcCircle(int **points, int diameter, float roundnessFactor) {
  // std::cout << std::endl << std::endl << "CALCULATION:" << std::endl;
  float radius = (float)diameter / 2;
  int radiusCeil = (int)ceil(radius);

  float offset;
  bool even = false;
  if (diameter % 2 == 0) {
    // even
    offset = -0.5f;
    even = true;
  } else {
    // odd
    offset = 0.0f;
  }

  for (int i = radiusCeil - 1; i >= 0; i--) {
    points[i] = new int[radiusCeil];
    for (int j = 0; j < radiusCeil; j++) {
      float abs =
          sqrt((i - offset) * (i - offset) + (j - offset) * (j - offset));

      /*// output condition for each point
      std::cout << "(" + std::to_string(abs) + "<" +
                       std::to_string(radius - roundnessFactor) + "),";*/

      if (abs < radius - roundnessFactor) {
        points[i][j] = 1;
      } else {
        points[i][j] = 0;
      }
    }
    // std::cout << std::endl;
  }
}

void OutputQuarter(int **points, int diameter) {
  std::cout << std::endl << std::endl << "OUTPUT QUARTER:" << std::endl;

  float radius = (float)diameter / 2;
  int radiusCeil = (int)ceil(radius);

  for (int i = radiusCeil - 1; i >= 0; i--) {
    for (int j = 0; j < radiusCeil; j++) {
      std::cout << (points[i][j] == 1 ? "#" : " ") << " ";
    }
    std::cout << std::endl;
  }
}

void OutputAndSaveComplete(int **points, int diameter, float roundnessFactor) {
  std::cout << std::endl << std::endl << "OUTPUT FULL CIRCLE:" << std::endl;

  float radius = (float)diameter / 2;
  int radiusCeil = (int)ceil(radius);
  bool even = false;
  if (diameter % 2 == 0) {
    even = true;
  }

  // open file
  std::ofstream fileOutput;
  fileOutput.open("circle_" + std::to_string(diameter) + "_" +
                  std::to_string(roundnessFactor) + ".txt");
  fileOutput.flush();

  fileOutput << "Circle diameter " << diameter
             << " roundness = " << roundnessFactor << std::endl;

  // output full circle
  for (int i = radiusCeil - 1; i > -radiusCeil; i--) {
    std::string stringLine = "";
    for (int j = -(radiusCeil - 1); j < radiusCeil; j++) {

      if (j == 0 && even) {
        std::cout << (points[abs(i)][abs(j)] == 1 ? "# " : "  ");
        stringLine += (points[abs(i)][abs(j)] == 1 ? "# " : "  ");
      }
      std::cout << (points[abs(i)][abs(j)] == 1 ? "# " : "  ");
      stringLine += (points[abs(i)][abs(j)] == 1 ? "# " : "  ");
    }
    if (i == 0 && even) {
      std::cout << std::endl;
      stringLine += "\n";
      for (int j = -(radiusCeil - 1); j < radiusCeil; j++) {

        if (j == 0) {
          std::cout << "# ";
          stringLine += "# ";
        }
        std::cout << (points[abs(i)][abs(j)] == 1 ? "# " : "  ");
        stringLine += (points[abs(i)][abs(j)] == 1 ? "# " : "  ");
      }
    }
    std::cout << std::endl;
    fileOutput << stringLine << "\n";
  }
  std::cout << std::endl;
  fileOutput.close();
}

int main(int argc, char *argv[]) {

  std::cout << "Minecraft Perfect Circle Tool v" << VERSION_MAJOR << "."
            << VERSION_MINOR << std::endl;

  // init
  int diameter = 0;
  float roundnessFactor = 0;

  while (1) {
    std::cout << "######################################" << std::endl;

    // read values
    if (requestValues(diameter, roundnessFactor) == false) {
      return 0;
    }

    std::cout << "You chose d=" << diameter << " b=" << roundnessFactor
              << std::endl;

    float radius = (float)diameter / 2;
    int radiusCeil = (int)ceil(radius);
    int **points = new int *[radiusCeil];

    CalcCircle(points, diameter, roundnessFactor);

    // OutputQuarter(points, diameter);

    OutputAndSaveComplete(points, diameter, roundnessFactor);
  }

  return 0;
}
