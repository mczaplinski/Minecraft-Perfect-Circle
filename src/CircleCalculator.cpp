#include "CircleCalculator.h"

#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

#include <stdlib.h>

CircleCalculator::CircleCalculator() {
  m_iDiameter = 0;
  m_fRoundnessFactor = 0.0f;
  m_bEven = false;
  m_fRadius = 0.0f;
  m_iRadiusCeil = 0;
  m_fOffset = 0.0f;
  m_bEasyMode = true;
}

CircleCalculator::~CircleCalculator() {}

bool CircleCalculator::mainMenu() {
  printConsoleHeader();

  std::cout << " Welcome to Minecraft Perfect Circle Tool v" << VERSION_MAJOR
            << "." << VERSION_MINOR << std::endl
            << std::endl;
  std::cout << " Main Menu:" << std::endl;
  std::cout << " [1] Generate new circle" << std::endl;
  std::cout << " [2] Toggle Easy Mode = " << (m_bEasyMode ? "TRUE" : "FALSE")
            << std::endl;
  std::cout << " [q] Quit" << std::endl;

  std::cout << std::endl;
  std::cout << " Your Choice: ";

  char cChoice = '0';
  fflush(stdin);
  std::cin.sync();
  std::cin >> cChoice;

  switch (cChoice) {
  case '1':
    Run();
    break;

  case '2':
    m_bEasyMode = !m_bEasyMode;
    break;

  case 'q':
    return false;

  default:
    break;
  }

  return true;
}

void CircleCalculator::printConsoleHeader() {
  // clear console
  system("cls");

  // flush buffer
  fflush(stdin);
  fflush(stdout);
  std::cin.sync();

  // print header
  std::cout << "#################################" << std::endl;
  std::cout << "# Minecraft Perfect Circle Tool #" << std::endl;
  std::cout << "#################################" << std::endl;
  std::cout << std::endl;
}

bool CircleCalculator::Run(int d, float rf) {

  bool bWidthEqualsRadius = false;
  bool bProgress = true;
  char cProgressResponse[2] = "t";

  // if diameter is not given as parameter
  if (d < 0 && rf < 0) {
    if (requestDiameter() == false) {
      return 0;
    }
  } else {
    m_iDiameter = d;
  }

  if (rf < 0) {
    if (m_bEasyMode) {
      m_fRoundnessFactor = m_fDefaultRoundnessFactor;
    } else {
      if (requestRoundnessFactor() == false) {
        return 0;
      }
    }
  } else {
    m_fRoundnessFactor = rf;
  }

  printConsoleHeader();

  std::cout << "You chose d=" << m_iDiameter << " rf=" << m_fRoundnessFactor
            << std::endl;

  initCircle();

  bWidthEqualsRadius = calcCircle();

  if (!bWidthEqualsRadius) {
    bool bYes = false;

    std::cout << std::endl
              << "The calculated circle has become smaller than the "
                 "requested size."
              << std::endl
              << "Likely, the roundness was chosen too high. Nevertheless, "
                 "display the result? (Y/N)"
              << std::endl;

    fflush(stdin);
    std::cin.sync();
    std::cin >> cProgressResponse;
    std::string sProgressResponse = (std::string)cProgressResponse;
    bYes = sProgressResponse == "Y" || sProgressResponse == "y" ||
           sProgressResponse == "Yes" || sProgressResponse == "yES" ||
           sProgressResponse == "yes" || sProgressResponse == "YES";
    if (bYes) {
      bProgress = true;
    } else { // everything but yes -> return to main menu
      bProgress = false;
    }
  }

  if (bProgress) {
    // outputQuarter();
    outputAndSaveComplete();

    // Hold circle on screen before returning to menu
    std::cout << std::endl
              << "Press any button to return to main menu..." << std::endl;
    fflush(stdin);
    std::cin.sync();
    std::cin.get();
  }

  return bProgress;
}

bool CircleCalculator::requestDiameter() {
  char cDiameter[10] = "";

  printConsoleHeader();

  // diameter info
  std::cout << "Please specify the diameter of the circle:" << std::endl
            << std::endl
            << "The diameter is the number of blocks "
               "from one side to the other along one axis."
            << std::endl
            << "The value can be even or uneven." << std::endl
            << "Type a number smaller than zero to return to the main menu."
            << std::endl
            << std::endl;

  std::cout << "Diameter d = ";

  // request input from user
  fflush(stdin);
  std::cin.sync();
  std::cin >> cDiameter;
  std::cout << std::endl;
  std::string sDiameter = (std::string)cDiameter;
  m_iDiameter = std::stoi(sDiameter);

  if (m_iDiameter <= 0) {
    return false;
  }

  return true;
}

bool CircleCalculator::requestRoundnessFactor() {
  char cRoundnessFactor[10] = "";

  printConsoleHeader();

  // diameter info
  std::cout
      << "Please specify the roundness factor of the circle:" << std::endl
      << std::endl
      << "Warning: You are not in easy mode." << std::endl
      << "If you do not want to specify this value, please return to the main "
         "menu and select easy mode instead!"
      << std::endl
      << std::endl
      << "The roundness factor a number used to slack the decision boundary of "
         "the circle to a "
         "little extend."
      << std::endl
      << "The lower the value, the more square-shaped your circle is going to "
         "be. Don't go below 0."
      << std::endl
      << "The higher the value, the more star-shaped your "
         "circle will become. Don't go higher than 0.499."
      << std::endl
      << "Too high values will "
         "crop the circle, i.e. the circle gets smaller than the desired "
         "diameter."
      << std::endl
      << "The optimal circle lies somewhere in between. We have "
         "found 0.275 to be a good starting value for a generally subjectively "
         "good circle."
      << std::endl
      << "Type a number smaller than zero to return "
         "to the main menu."
      << std::endl
      << std::endl;

  std::cout << "Roundness factor rf = ";

  // request input from user
  fflush(stdin);
  std::cin.sync();
  std::cin >> cRoundnessFactor;
  std::cout << std::endl;
  std::string sRoundnessFactor = (std::string)cRoundnessFactor;

  if (sRoundnessFactor != "") {
    m_fRoundnessFactor = std::stof(sRoundnessFactor);
  } else {
    m_fRoundnessFactor = m_fDefaultRoundnessFactor;
  }

  return true;
}

void CircleCalculator::initCircle() {
  // calculate often used values
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
}

bool CircleCalculator::calcCircle() {
  // std::cout << std::endl << std::endl << "CALCULATION:" << std::endl;
  bool widthEqualsRadius = false;
  int width = 0;
  // calculation of quarter circle
  for (int i = m_iRadiusCeil - 1; i >= 0; i--) {
    width = 0;
    m_pQuarterPoints[i] = new int[m_iRadiusCeil];
    for (int j = 0; j < m_iRadiusCeil; j++) {
      float abs = sqrt((i - m_fOffset) * (i - m_fOffset) +
                       (j - m_fOffset) * (j - m_fOffset));

#ifdef DEBUG_OUTPUT
      // output condition for each point in the first quarter of the circle!
      std::cout << "(" + std::to_string(abs) + "<" +
                       std::to_string(m_fRadius - m_fRoundnessFactor) + "),";
#endif

      if (abs < m_fRadius - m_fRoundnessFactor) {
        m_pQuarterPoints[i][j] = 1;
        width++;
      } else {
        m_pQuarterPoints[i][j] = 0;
      }
    }
    if (width == m_iRadiusCeil) {
      widthEqualsRadius = true;
    }
#ifdef DEBUG_OUTPUT
    std::cout << std::endl;
#endif
  }
  return widthEqualsRadius;
}

void CircleCalculator::outputQuarter() {
  std::cout << std::endl << std::endl << "OUTPUT QUARTER:" << std::endl;

  for (int i = m_iRadiusCeil - 1; i >= 0; i--) {
    for (int j = 0; j < m_iRadiusCeil; j++) {
      std::cout << (m_pQuarterPoints[i][j] == 1 ? "#" : " ") << " ";
    }
    std::cout << std::endl;
  }
}

void CircleCalculator::outputAndSaveComplete() {

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
