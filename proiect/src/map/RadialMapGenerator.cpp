#include "RadialMapGenerator.h"
#include "MapExceptions.h"

#include <algorithm>
#include <ctime>
#include <cmath>

void RadialMapGenerator::placeSpecial(Map* map, CellType type, int count, int r, int c) {
  for(int i = 0; i < count; i++) {
    int rr, cc;
    do { 
      rr = rand() % r; 
      cc = rand() % c; 
    } while(map->getCell(rr, cc) != CellType::SPACE);
    map->setCell(rr, cc, type);
  }
}

Map* RadialMapGenerator::generate() {
  ConfigManager* cfg = ConfigManager::getInstance();
  int r = cfg->getMapWidth();
  int c = cfg->getMapHeight();
  int centerX = r / 2;
  int centerY = c / 2;
  
  int ringSpacing = cfg->getRadialRingSpacing(); 
  int plazaRadius = cfg->getRadialPlazaRadius();
  int ringRoadWidth = cfg->getRadialRingRoadWidth();
  int maxRings = cfg->getRadialMaxRings();
  

  const int MAX_ATTEMPTS = 50; 
  int attempts = 0;
  srand(time(nullptr));

  while(attempts < MAX_ATTEMPTS) {
    Map* map = new Map(r, c);
    int maxRadialDist = maxRings * ringSpacing;

    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        double dx = i - centerX;
        double dy = j - centerY;
        double dist = sqrt(dx*dx + dy*dy);
        
        /* Alleys: 4 Cardinal directions */
        bool isAlley = (i == centerX || j == centerY);
        /* But a 25% chance for the alley to be blocked */
        if(isAlley && (rand() % 4 == 0)) isAlley = false;

        /* Central Plaza */
        bool isPlaza = (dist < (double)plazaRadius);

        /* Restricted Radial Area (The "City Center") */
        if (dist <= (double)maxRadialDist) {
          bool isRing = ((int)dist % ringSpacing < ringRoadWidth);
          
          if (isPlaza || isAlley || isRing) {
            map->setCell(i, j, CellType::SPACE);
          } else {
            map->setCell(i, j, CellType::WALL);
          }
        } 
        /* Peripheral Area (The "Suburbs" - fully closed off, we don't deliver here) */
        else {
          map->setCell(i, j, CellType::WALL);
        }
      }
    }

    /* Ensure Hub is at center */
    map->setCell(centerX, centerY, CellType::HUB);

    /* Place Clients and Stations */
    placeSpecial(map, CellType::CLIENT, cfg->getClientsCount(), r, c);
    placeSpecial(map, CellType::STATION, cfg->getMaxStations(), r, c);

    if(map->validate()) return map;

    delete map;
    attempts++;
  }

  throw MapValidationException("Radial generation failed. Try increasing max rings or reducing density.");
}