#pragma once

#include "IMapGenerator.h"
#include "Map.h"
#include "../core/ConfigManager.h"

#include <vector>

using namespace std;

/* * CanyonMapGenerator:
 * Generates a narrow central corridor.
 * Forces agents into a linear flow, testing bottleneck efficiency and 
 * long-range battery management.
 */
class CanyonMapGenerator : public IMapGenerator {
private:
  /* Helper to place special cells like HUB, STATION, CLIENT */
  void placeSpecial(Map* map, CellType type, int count, int r, int c);

public:
  /* Main generation entry point */
  Map* generate() override;
};