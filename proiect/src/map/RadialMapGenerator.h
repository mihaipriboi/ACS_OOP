#pragma once

#include "IMapGenerator.h"
#include "Map.h"
#include "../core/ConfigManager.h"

#include <vector>

using namespace std;

/* * RadialMapGenerator:
 * Generates a central open plaza for the Hub.
 * Surrounds the center with concentric ring roads and urban blocks.
 * Perfect for testing radial distribution efficiency.
 * Alleyways at cardinal directions connect the rings.
 * There is a chance the alleys are blocked, adding variability.
 */
class RadialMapGenerator : public IMapGenerator {
private:
  /* Helper to place special cells like HUB, STATION, CLIENT */
  void placeSpecial(Map* map, CellType type, int count, int r, int c);

public:
  /* Main generation entry point */
  Map* generate() override;
};