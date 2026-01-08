#include "CanyonMapGenerator.h"
#include "MapExceptions.h"

#include <algorithm>
#include <ctime>

void CanyonMapGenerator::placeSpecial(Map* map, CellType type, int count, int r, int c) {
  for(int i = 0; i < count; i++) {
    int rr, cc;
    do { 
      rr = rand() % r; 
      cc = rand() % c; 
    } while(map->getCell(rr, cc) != CellType::SPACE);
    map->setCell(rr, cc, type);
  }
}

Map* CanyonMapGenerator::generate() {
  ConfigManager* cfg = ConfigManager::getInstance();
  int r = cfg->getMapWidth();
  int c = cfg->getMapHeight();
  
  const int MAX_ATTEMPTS = 50; 
  int attempts = 0;
  srand(time(nullptr));

  while(attempts < MAX_ATTEMPTS) {
    Map* map = new Map(r, c);

    // Initialize the entire grid as WALL (#)
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        map->setCell(i, j, CellType::WALL);
      }
    }

    // Carve a horizontal "Canyon" through the middle
    // The height of the canyon is roughly 1/3 of the map height
    int canyonHeight = (r / 3 > 0) ? r / 3 : 1;
    int startRow = (r - canyonHeight) / 2;

    for(int i = startRow; i < startRow + canyonHeight; i++) {
      for(int j = 0; j < c; j++) {
        map->setCell(i, j, CellType::SPACE);
      }
    }

    // Place Special Locations (HUB, CLIENTS, STATIONS) 
    // They are guaranteed to be placed inside the SPACE of the canyon
    placeSpecial(map, CellType::HUB, 1, r, c);
    placeSpecial(map, CellType::CLIENT, cfg->getClientsCount(), r, c);
    placeSpecial(map, CellType::STATION, cfg->getMaxStations(), r, c);

    // Validate using the Range-Aware Standard logic or Drone logic
    if(map->validate()) return map;

    delete map;
    attempts++;
  }

  throw MapValidationException("Canyon generation failed to produce a valid connected map.");
}