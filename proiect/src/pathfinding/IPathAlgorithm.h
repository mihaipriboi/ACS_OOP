#pragma once

#include "../map/Map.h"

#include <vector>
#include <utility>

using namespace std;

/* * IPathAlgorithm Interface:
 * Abstract strategy for calculating a route between two coordinates.
 */
class IPathAlgorithm {
public:
  virtual ~IPathAlgorithm() {}
  
  /* Returns a vector of (x, y) coordinates representing the path */
  virtual vector<pair<int, int>> calculatePath(int startX, int startY, 
                                               int endX, int endY, 
                                               const Map& map) = 0;
};