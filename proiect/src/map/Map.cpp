#include "Map.h"
#include "../core/UIHelper.h"

#include <queue>

Map::Map(int r, int c) : rows(r), cols(c), bRows(r + 2), bCols(c + 2), hubX(-1), hubY(-1) {
  /* Initialize the entire grid with WALL */
  grid.assign(bRows, vector<CellType>(bCols, CellType::WALL));
  
  /* Set the internal playable area to SPACE */
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= cols; j++) {
      grid[i][j] = CellType::SPACE;
    }
  }
}

void Map::setCell(int r, int c, CellType type) {
  grid[r + 1][c + 1] = type;
}

CellType Map::getCell(int r, int c) const {
  return grid[r + 1][c + 1];
}

void Map::display() const {
  UIHelper::printHeader(" City Map ");
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= cols; j++) {
      printf("%s ", CELL_CHARS_TERMINAL[(int)grid[i][j]].c_str());
    }
    printf("\n");
  }

  /* Printing the Legend */
  UIHelper::printHeader(" Legend ");
  printf("%s : Wall (Obstacle/#)\n", CELL_CHARS_TERMINAL[(int)CellType::WALL].c_str());
  printf("%s : Road (Space/.)\n", CELL_CHARS_TERMINAL[(int)CellType::SPACE].c_str());
  printf("%s : Hub (Base/H)\n", CELL_CHARS_TERMINAL[(int)CellType::HUB].c_str());
  printf("%s : Station (Charging/S)\n", CELL_CHARS_TERMINAL[(int)CellType::STATION].c_str());
  printf("%s : Client (Destination/C)\n", CELL_CHARS_TERMINAL[(int)CellType::CLIENT].c_str());
  UIHelper::printHeader();
}

bool Map::validate() const {
  int startR = -1, startC = -1;
  int targetsNeeded = 0;

  /* Search for Hub and count targets within playable area */
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= cols; j++) {
      if(grid[i][j] == CellType::HUB) { 
        const_cast<Map*>(this)->hubX = i - 1;
        const_cast<Map*>(this)->hubY = j - 1;
        startR = i; startC = j; 
      }
      if(grid[i][j] == CellType::CLIENT || grid[i][j] == CellType::STATION) {
        targetsNeeded++;
      }
    }
  }

  if(startR == -1) return false;

  vector<vector<bool>> visited(bRows, vector<bool>(bCols, false));
  queue<pair<int, int>> q;
  q.push({startR, startC});
  visited[startR][startC] = true;

  int reachedTargets = 0;
  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  while(!q.empty()) {
    pair<int, int> curr = q.front(); 
    q.pop();
    
    for(int i = 0; i < 4; i++) {
      int nr = curr.first + dr[i];
      int nc = curr.second + dc[i];

      /* No boundary checks needed because the border is WALL */
      if(!visited[nr][nc] && grid[nr][nc] != CellType::WALL) {
        visited[nr][nc] = true;
        if(grid[nr][nc] == CellType::CLIENT || grid[nr][nc] == CellType::STATION) {
          reachedTargets++;
        }
        q.push({nr, nc});
      }
    }
  }

  return reachedTargets == targetsNeeded;
}

void Map::saveToFile(const char* filename) const {
  FILE* file = fopen(filename, "w");
  if(!file) return;
  fprintf(file, "%d %d\n", rows, cols);
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= cols; j++) {
      fprintf(file, "%c", CELL_CHARS[(int)grid[i][j]]);
    }
    fprintf(file, "\n");
  }
  fclose(file);
}