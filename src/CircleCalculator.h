#ifndef _CIRCLECALCULATOR_H
#define _CIRCLECALCULATOR_H

class CircleCalculator {
public:
  CircleCalculator();
  ~CircleCalculator();

  bool Run(int d = -1, float rf = -1.0f);

  bool mainMenu();

  void printConsoleHeader();
  bool requestDiameter();
  bool requestRoundnessFactor();
  void initCircle();
  bool calcCircle();
  void outputQuarter();
  void outputAndSaveComplete();

private:
  int m_iDiameter;
  float m_fRadius;
  int m_iRadiusCeil;

  bool m_bEven;
  float m_fOffset;

  float m_fRoundnessFactor;

  int **m_pQuarterPoints; // inner points of blocks inside the circle in first
                          // quadrant

  const float m_fDefaultRoundnessFactor = 0.275f;
  bool m_bEasyMode;
};

#endif // _CIRCLECALCULATOR_H
