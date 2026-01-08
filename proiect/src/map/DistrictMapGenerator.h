#pragma once

#include "IMapGenerator.h"
#include "Map.h"
#include "../core/ConfigManager.h"

#include <vector>

using namespace std;

/* * DistrictMapGenerator:
 * Generates structured urban blocks (WALLs) and intersecting streets (SPACE).
 * Uses configurable block sizes to define city density.
 */
class DistrictMapGenerator : public IMapGenerator {
private:
  void placeSpecial(Map* map, CellType type, int count, int r, int c);

public:
  Map* generate() override;
};