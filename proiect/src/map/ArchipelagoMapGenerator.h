#pragma once

#include "IMapGenerator.h"
#include "Map.h"
#include "../core/ConfigManager.h"

#include <vector>

using namespace std;

/* * ArchipelagoMapGenerator:
 * Generates organic, archipelago-like landmasses.
 * Uses Cellular Automata (Birth/Survival rules) to create clusters.
 */
class ArchipelagoMapGenerator : public IMapGenerator {
private:
  /* Helper to count neighboring space cells for automata rules */
  int countAliveNeighbors(Map* map, int r, int c, int rows, int cols);
  
  /* Helper to place special cells like HUB, STATION, CLIENT */
  void placeSpecial(Map* map, CellType type, int count, int r, int c);

public:
  /* Main generation entry point */
  Map* generate() override;
};