#pragma once

#include "IMapGenerator.h"
#include "Map.h"
#include "../core/ConfigManager.h"

#include <vector>

using namespace std;

/* * MazeMapGenerator:
 * Generate structured, maze-like maps.
 * Uses Recursive Backtracking to ensure connectivity.
 */
class MazeMapGenerator : public IMapGenerator {
private:
  /* Helper to get valid neighbor cells at distance 2 */
  vector<pair<int, int>> getNeighbors(int r, int c, int rows, int cols);
  
  /* Helper to place special cells like HUB, STATION, CLIENT */
  void placeSpecial(Map* map, CellType type, int count, int r, int c);

public:
  /* Main generation entry point  */
  Map* generate() override;
};