#include "ArchipelagoMapGenerator.h"
#include "MapExceptions.h"

#include <algorithm>
#include <ctime>

int ArchipelagoMapGenerator::countAliveNeighbors(Map* map, int r, int c, int rows, int cols) {
  int count = 0;
  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      if(i == 0 && j == 0) continue;
      int nr = r + i;
      int nc = c + j;
      if(nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
        if(map->getCell(nr, nc) == CellType::SPACE) count++;
      }
    }
  }
  return count;
}

void ArchipelagoMapGenerator::placeSpecial(Map* map, CellType type, int count, int r, int c) {
  for(int i = 0; i < count; i++) {
    int rr, cc;
    int safetyBreak = 0;
    do { 
      rr = rand() % r; 
      cc = rand() % c; 
      safetyBreak++;
    } while(map->getCell(rr, cc) != CellType::SPACE && safetyBreak < 1000);
    
    // If we can't find space, force it (islands might be small)
    map->setCell(rr, cc, type);
  }
}

Map* ArchipelagoMapGenerator::generate() {
  ConfigManager* cfg = ConfigManager::getInstance();
  int r = cfg->getMapWidth();
  int c = cfg->getMapHeight();

  const int MAX_ATTEMPTS = 50;
  int attempts = 0;
  srand(time(nullptr));

  while(attempts < MAX_ATTEMPTS) {
    Map* map = new Map(r, c);

    // Initial Random Noise
    // Higher percentage = more land initially
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++) {
        if(rand() % 100 < cfg->getWallDensityArchipelago()) {
          map->setCell(i, j, CellType::SPACE);
        } else {
          map->setCell(i, j, CellType::WALL);
        }
      }
    }

    // Cellular Automata Smoothing (5 iterations)
    for(int step = 0; step < 5; step++) {
      vector<vector<CellType>> nextGrid(r, vector<CellType>(c));
      for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
          int neighbors = countAliveNeighbors(map, i, j, r, c);
          if(map->getCell(i, j) == CellType::SPACE) {
            nextGrid[i][j] = (neighbors >= 2) ? CellType::SPACE : CellType::WALL;
          } else {
            nextGrid[i][j] = (neighbors >= 4) ? CellType::SPACE : CellType::WALL;
          }
        }
      }
      for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
          map->setCell(i, j, nextGrid[i][j]);
        }
      }
    }

    // Place Special Locations
    placeSpecial(map, CellType::HUB, 1, r, c);
    placeSpecial(map, CellType::CLIENT, cfg->getClientsCount(), r, c);
    placeSpecial(map, CellType::STATION, cfg->getMaxStations(), r, c);

    // Validate the generated map
    // Ensures Hub (B) can reach all Clients (D) and Stations (S)
    if(map->validate()) return map;

    delete map;
    attempts++;
  }

  throw MapValidationException("Island generation failed to produce a valid connected map.");
}