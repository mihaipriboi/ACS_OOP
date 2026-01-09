#pragma once

#include "MapConstants.h"

#include <vector>
#include <cstdio>

using namespace std;

class Map {
private:
  int rows, cols; /* Original dimensions */
  int bRows, bCols; /* Bordered dimensions (rows+2, cols+2) */
  int hubX, hubY; /* Hub coordinates */
  vector<vector<CellType>> grid;

  static ValidationType validationType;

public:
  Map(int r, int c);
  
  static void setValidationType(ValidationType type) { validationType = type; }

  void setCell(int r, int c, CellType type);
  CellType getCell(int r, int c) const;
  
  int getRows() const { return rows; }
  int getCols() const { return cols; }
  int getHubX() const { return hubX; }
  int getHubY() const { return hubY; }

  bool validate() const;
  /* Standard validation for ground agents (BFS) */
  bool validateStandard() const;
  /* Specialized drone validation for energy-constrained flight */
  bool validateDroneAccessible() const;

  void display() const;
  void saveToFile(const char* filename) const;
  void saveToFile(FILE* file) const;
};