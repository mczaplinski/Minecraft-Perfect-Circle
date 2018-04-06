#ifndef _CIRCLECALCULATOR_H
#define _CIRCLECALCULATOR_H

class CircleCalculator {
public:
  CircleCalculator();
  ~CircleCalculator();

  bool Run();

  bool requestValues();
  bool CalcCircle();
  void OutputQuarter();
  void OutputAndSaveComplete();

private:
  int m_iDiameter;
  float m_fRadius;
  int m_iRadiusCeil;

  bool m_bEven;
  float m_fOffset;

  float m_fRoundnessFactor;

  int **m_pQuarterPoints; // inner points of blocks inside the circle in first
                          // quadrant
};

#endif // _CIRCLECALCULATOR_H
