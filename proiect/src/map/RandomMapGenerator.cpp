#include "RandomMapGenerator.h"
#include "MapExceptions.h"

#include <cstdlib>
#include <ctime>

Map* RandomMapGenerator::generate() {
  ConfigManager* cfg = ConfigManager::getInstance();
  int r = cfg->getMapWidth();
  int c = cfg->getMapHeight();
  
  const int MAX_ATTEMPTS = 100;
  int attempts = 0;
  srand(time(nullptr));

  while(attempts < MAX_ATTEMPTS) {
    Map* map = new Map(r, c);
    
    // Place Hub
    map->setCell(rand() % r, rand() % c, CellType::HUB);

    // Place Clients
    for(int i = 0; i < cfg->getClientsCount(); i++) {
      int rr, cc;
      do { 
        rr = rand() % r; 
        cc = rand() % c; 
      } while(map->getCell(rr, cc) != CellType::SPACE);
      map->setCell(rr, cc, CellType::CLIENT);
    }

    // Place Stations
    for(int i = 0; i < cfg->getMaxStations(); i++) {
      int rr, cc;
      do { 
        rr = rand() % r; 
        cc = rand() % c; 
      } while(map->getCell(rr, cc) != CellType::SPACE);
      map->setCell(rr, cc, CellType::STATION);
    }

    // Place Walls
    int density = cfg->getWallDensityRandom();
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        if(map->getCell(i, j) == CellType::SPACE && (rand() % 100 < density)) {
          map->setCell(i, j, CellType::WALL);
        }
      }
    }

    if(map->validate()) return map;

    delete map;
    attempts++;
  }

  throw MapValidationException("Procedural generation failed after 100 attempts. Check configuration parameters.");
}