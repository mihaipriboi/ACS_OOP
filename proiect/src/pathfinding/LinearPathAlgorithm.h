#pragma once

#include "IPathAlgorithm.h"

#include <vector>

using namespace std;

class LinearPathAlgorithm : public IPathAlgorithm {
public:
  vector<pair<int, int>> calculatePath(int startX, int startY, int endX, int endY, const Map& map) override {
    vector<pair<int, int>> path;
    int currX = startX;
    int currY = startY;

    while(currX != endX || currY != endY) {
      if(currX < endX) currX++;
      else if(currX > endX) currX--;
      else if(currY < endY) currY++;
      else if(currY > endY) currY--;

      path.push_back({currX, currY});
    }
    return path;
  }
};