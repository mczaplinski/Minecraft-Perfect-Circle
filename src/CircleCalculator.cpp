#include "CircleCalculator.h"

#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

CircleCalculator::CircleCalculator() {
  m_iDiameter = 0;
  m_fRoundnessFactor = 0.0f;
  m_bEven = false;
  m_fRadius = 0.0f;
  m_iRadiusCeil = 0;
  m_fOffset = 0.0f;
}
CircleCalculator::~CircleCalculator() {}

bool CircleCalculator::Run() {
  std::cout << "######################################" << std::endl;

  // read values
  if (requestValues() == false) {
    return 0;
  }

  std::cout << "You chose d=" << m_iDiameter << " b=" << m_fRoundnessFactor
            << std::endl;

  CalcCircle();

  OutputQuarter();

  OutputAndSaveComplete();
}

bool CircleCalculator::requestValues() {
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
    m_fRoundnessFactor = std::stof(sRoundnessFactor);
  } else {
    m_fRoundnessFactor = 0;
  }

  m_iDiameter = std::stoi(sDiameter);

  // calculate other often used values
  m_fRadius = (float)m_iDiameter / 2;
  m_iRadiusCeil = (int)ceil(m_fRadius);
  m_pQuarterPoints = new int *[m_iRadiusCeil];

  // even vs odd
  if (m_iDiameter % 2 == 0) { // even
    m_fOffset = -0.5f;
    m_bEven = true;
  } else { // odd
    m_fOffset = 0.0f;
    m_bEven = false;
  }

  return true;
}
void CircleCalculator::CalcCircle() {
  // std::cout << std::endl << std::endl << "CALCULATION:" << std::endl;

  // calculation of quarter circle
  for (int i = m_iRadiusCeil - 1; i >= 0; i--) {
    m_pQuarterPoints[i] = new int[m_iRadiusCeil];
    for (int j = 0; j < m_iRadiusCeil; j++) {
      float abs = sqrt((i - m_fOffset) * (i - m_fOffset) +
                       (j - m_fOffset) * (j - m_fOffset));

      // output condition for each point
      // std::cout << "(" + std::to_string(abs) + "<" +
      //                 std::to_string(m_fRadius - m_fRoundnessFactor) + "),";

      if (abs < m_fRadius - m_fRoundnessFactor) {
        m_pQuarterPoints[i][j] = 1;
      } else {
        m_pQuarterPoints[i][j] = 0;
      }
    }
  }
}
void CircleCalculator::OutputQuarter() {
  std::cout << std::endl << std::endl << "OUTPUT QUARTER:" << std::endl;

  for (int i = m_iRadiusCeil - 1; i >= 0; i--) {
    for (int j = 0; j < m_iRadiusCeil; j++) {
      std::cout << (m_pQuarterPoints[i][j] == 1 ? "#" : " ") << " ";
    }
    std::cout << std::endl;
  }
}
void CircleCalculator::OutputAndSaveComplete() {

  std::cout << std::endl << std::endl << "OUTPUT FULL CIRCLE:" << std::endl;

  bool even = false;
  if (m_iDiameter % 2 == 0) {
    even = true;
  }

  // open file
  std::ofstream fileOutput;
  fileOutput.open("circle_" + std::to_string(m_iDiameter) + "_" +
                  std::to_string(m_fRoundnessFactor) + ".txt");
  fileOutput.flush();

  fileOutput << "Circle diameter " << m_iDiameter
             << " roundness = " << m_fRoundnessFactor << std::endl;

  // output full circle
  for (int i = m_iRadiusCeil - 1; i > -m_iRadiusCeil; i--) {
    std::string stringLine = "";
    for (int j = -(m_iRadiusCeil - 1); j < m_iRadiusCeil; j++) {

      if (j == 0 && even) {
        std::cout << (m_pQuarterPoints[abs(i)][abs(j)] == 1 ? "# " : "  ");
        stringLine += (m_pQuarterPoints[abs(i)][abs(j)] == 1 ? "# " : "  ");
      }
      std::cout << (m_pQuarterPoints[abs(i)][abs(j)] == 1 ? "# " : "  ");
      stringLine += (m_pQuarterPoints[abs(i)][abs(j)] == 1 ? "# " : "  ");
    }
    if (i == 0 && even) {
      std::cout << std::endl;
      stringLine += "\n";
      for (int j = -(m_iRadiusCeil - 1); j < m_iRadiusCeil; j++) {

        if (j == 0) {
          std::cout << "# ";
          stringLine += "# ";
        }
        std::cout << (m_pQuarterPoints[abs(i)][abs(j)] == 1 ? "# " : "  ");
        stringLine += (m_pQuarterPoints[abs(i)][abs(j)] == 1 ? "# " : "  ");
      }
    }
    std::cout << std::endl;
    fileOutput << stringLine << "\n";
  }
  std::cout << std::endl;
  fileOutput.close();
}
