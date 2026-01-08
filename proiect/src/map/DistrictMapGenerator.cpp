#include "DistrictMapGenerator.h"
#include "MapExceptions.h"

#include <algorithm>
#include <ctime>

void DistrictMapGenerator::placeSpecial(Map* map, CellType type, int count, int r, int c) {
  for(int i = 0; i < count; i++) {
    int rr, cc;
    int safety = 0;
    do { 
      rr = rand() % r; 
      cc = rand() % c; 
      safety++;
    } while(map->getCell(rr, cc) != CellType::SPACE && safety < 1000);
    map->setCell(rr, cc, type);
  }
}

Map* DistrictMapGenerator::generate() {
  ConfigManager* cfg = ConfigManager::getInstance();
  int r = cfg->getMapWidth();
  int c = cfg->getMapHeight();
  
  /* Load Block Size from setup.txt (e.g., 3 means 3x3 buildings) */
  int blockSize = cfg->getDistrictBlockSize();
  if (blockSize <= 0) blockSize = 3; 

  const int MAX_ATTEMPTS = 50; 
  int attempts = 0;
  srand(time(nullptr));

  while(attempts < MAX_ATTEMPTS) {
    Map* map = new Map(r, c);

    /* 1. Create the Grid Pattern */
    /* Logic: A cell is a street if its coordinate is a multiple of (blockSize + 1) */
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        if(i % (blockSize + 1) == 0 || j % (blockSize + 1) == 0) {
          map->setCell(i, j, CellType::SPACE);
        } else {
          map->setCell(i, j, CellType::WALL);
        }
      }
    }

    /* 2. Place Special Locations */
    placeSpecial(map, CellType::HUB, 1, r, c);
    placeSpecial(map, CellType::CLIENT, cfg->getClientsCount(), r, c);
    placeSpecial(map, CellType::STATION, cfg->getMaxStations(), r, c);

    /* 3. Static Validation (Range-Aware) */
    if(map->validate()) return map;

    delete map;
    attempts++;
  }

  throw MapValidationException("District generation failed. Blocks might be too large for the map size.");
}