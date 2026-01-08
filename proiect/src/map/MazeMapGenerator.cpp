#include "MazeMapGenerator.h"
#include "MapExceptions.h"

#include <algorithm>
#include <ctime>

vector<pair<int, int>> MazeMapGenerator::getNeighbors(int r, int c, int rows, int cols) {
  vector<pair<int, int>> neighbors;
  int dr[] = {-2, 2, 0, 0};
  int dc[] = {0, 0, -2, 2};

  for(int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    if(nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
      neighbors.push_back({nr, nc});
    }
  }
  return neighbors;
}

void MazeMapGenerator::placeSpecial(Map* map, CellType type, int count, int r, int c) {
  for(int i = 0; i < count; i++) {
    int rr, cc;
    do { 
      rr = rand() % r; 
      cc = rand() % c; 
    } while(map->getCell(rr, cc) != CellType::SPACE);
    map->setCell(rr, cc, type);
  }
}

Map* MazeMapGenerator::generate() {
  ConfigManager* cfg = ConfigManager::getInstance();
  int r = cfg->getMapWidth();
  int c = cfg->getMapHeight();
  int complexity = cfg->getWallDensityMaze();
  
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

    // Carve Maze Paths
    vector<pair<int, int>> stack;
    stack.push_back({0, 0});
    map->setCell(0, 0, CellType::SPACE);

    while(!stack.empty()) {
      pair<int, int> curr = stack.back();
      vector<pair<int, int>> neighbors = getNeighbors(curr.first, curr.second, r, c);
      
      neighbors.erase(remove_if(neighbors.begin(), neighbors.end(), [&](pair<int, int> p) {
        return map->getCell(p.first, p.second) == CellType::SPACE;
      }), neighbors.end());

      if(!neighbors.empty()) {
        pair<int, int> next = neighbors[rand() % neighbors.size()];
        map->setCell((curr.first + next.first) / 2, (curr.second + next.second) / 2, CellType::SPACE);
        map->setCell(next.first, next.second, CellType::SPACE);
        stack.push_back(next);
      } else {
        stack.pop_back();
      }
    }

    // Complexity: Open up the maze based on density
    // Higher density = more walls remain (more maze-like)
    for(int i = 1; i < r - 1; i++) {
      for(int j = 1; j < c - 1; j++) {
        if(map->getCell(i, j) == CellType::WALL && (rand() % 100 > complexity)) {
          map->setCell(i, j, CellType::SPACE);
        }
      }
    }

    // Place Special Locations on SPACE cells
    placeSpecial(map, CellType::HUB, 1, r, c);
    placeSpecial(map, CellType::CLIENT, cfg->getClientsCount(), r, c);
    placeSpecial(map, CellType::STATION, cfg->getMaxStations(), r, c);

    // Validate the generated map
    if(map->validate()) return map;

    delete map;
    attempts++;
  }

  throw MapValidationException("Maze generation failed to produce a valid connected map.");
}