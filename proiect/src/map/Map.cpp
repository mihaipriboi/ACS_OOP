#include "Map.h"
#include "../core/UIHelper.h"
#include "../agents/AgentFactory.h"

#include <queue>
#include <cmath>

ValidationType Map::validationType = ValidationType::STANDARD;

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
  switch(validationType) {
    case ValidationType::STANDARD:
      return validateStandard();
    case ValidationType::DRONE:
      return validateDroneAccessible();
    default:
      return false;
  }
}

/* * validateStandard:
 * Ensures all Clients (C) and Stations (S) can be reached by ground units,
 * starting from the Hub (H), considering the maximum range of the most
 * efficient ground unit (Robot).
 */
bool Map::validateStandard() const {
  /* Calculate max range of the Robot */
  unique_ptr<Agent> tempRobot = AgentFactory::createAgent(AgentType::ROBOT, -1, 0, 0);
  int robotMaxRange = (tempRobot->getMaxBattery() / 2) * tempRobot->getSpeed();

  int startR = -1, startC = -1;
  struct Target { int r, c; bool reached; CellType type; };
  vector<Target> targets;

  /* Collect Hub and targets */
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= cols; j++) {
      if(grid[i][j] == CellType::HUB) { 
        const_cast<Map*>(this)->hubX = i - 1;
        const_cast<Map*>(this)->hubY = j - 1;
        startR = i; startC = j; 
      }
      if(grid[i][j] == CellType::CLIENT || grid[i][j] == CellType::STATION) {
        targets.push_back({i, j, false, grid[i][j]});
      }
    }
  }
  if(startR == -1) return false;

  /* Multi-stage BFS: Stations act as relay points */
  queue<pair<int, int>> powerSources;
  powerSources.push({startR, startC});

  while(!powerSources.empty()) {
    pair<int, int> source = powerSources.front();
    powerSources.pop();

    /* Local BFS to find what this specific source can reach within robotMaxRange */
    queue<pair<pair<int, int>, int>> q; // {{r, c}, currentDist}
    q.push({source, 0});

    vector<vector<bool>> localVisited(bRows, vector<bool>(bCols, false));
    localVisited[source.first][source.second] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while(!q.empty()) {
      auto curr = q.front();
      q.pop();

      int r = curr.first.first;
      int c = curr.first.second;
      int d = curr.second;

      /* Check if this cell is one of our targets */
      for(auto& t : targets) {
        if(!t.reached && t.r == r && t.c == c) {
          t.reached = true;
          /* If we reached a Station, it becomes a new power source for the next relay */
          if(t.type == CellType::STATION) {
            powerSources.push({t.r, t.c});
          }
        }
      }

      /* Stop exploring this path if we hit the battery limit */
      if(d >= robotMaxRange) continue;

      /* Explore neighbors */
      for(int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(!localVisited[nr][nc] && grid[nr][nc] != CellType::WALL) {
          localVisited[nr][nc] = true;
          q.push({{nr, nc}, d + 1});
        }
      }
    }
  }

  /* Map is valid only if all targets were reached within energy limits */
  for(const auto& t : targets) {
    if(!t.reached) return false;
  }

  return true;
}

/* * validateDroneAccessible:
 * Ensures all Clients (D) can be reached by a drone, potentially 
 * using Charging Stations (S) as intermediate hops.
 */
bool Map::validateDroneAccessible() const {
  /* Calculate maximum range of a Drone on full charge */
  unique_ptr<Agent> tempDrone = AgentFactory::createAgent(AgentType::DRONE, -1, -1, -1);
  int droneMaxRange = (tempDrone->getMaxBattery() / tempDrone->getConsumption()) * tempDrone->getSpeed();

  struct Point { int r, c; };
  Point hubPos = {-1, -1};
  vector<Point> stations;
  vector<Point> clients;

  /* Collect all points of interest */
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= cols; j++) {
      if(grid[i][j] == CellType::HUB) hubPos = {i, j};
      else if(grid[i][j] == CellType::STATION) stations.push_back({i, j});
      else if(grid[i][j] == CellType::CLIENT) clients.push_back({i, j});
    }
  }

  if(hubPos.r == -1) return false;

  /* BFS to find reachable stations from the Hub */
  vector<bool> stationReachable(stations.size(), false);
  queue<Point> q;
  q.push(hubPos);

  while(!q.empty()) {
    Point curr = q.front();
    q.pop();

    for(size_t i = 0; i < stations.size(); i++) {
      if(!stationReachable[i]) {
        int dist = abs(curr.r - stations[i].r) + abs(curr.c - stations[i].c);
        if(dist <= droneMaxRange) {
          stationReachable[i] = true;
          q.push(stations[i]);
        }
      }
    }
  }

  /* Check if every client is reachable from the Hub or a reachable station */
  for(const auto& client : clients) {
    bool reachable = false;
    
    /* Can drone fly from Hub directly to client? */
    if((abs(hubPos.r - client.r) + abs(hubPos.c - client.c)) <= droneMaxRange) {
      reachable = true;
    }

    /* If not, can it reach from any reachable station? */
    if(!reachable) {
      for(size_t i = 0; i < stations.size(); i++) {
        if(stationReachable[i]) {
          int dist = abs(stations[i].r - client.r) + abs(stations[i].c - client.c);
          if(dist <= droneMaxRange) {
            reachable = true;
            break;
          }
        }
      }
    }

    if(!reachable) return false; /* Found an isolated client */
  }

  return true;
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

void Map::saveToFile(FILE* file) const {
  if(!file) return;
  fprintf(file, "%d %d\n", rows, cols);
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= cols; j++) {
      fprintf(file, "%c", CELL_CHARS[(int)grid[i][j]]);
    }
    fprintf(file, "\n");
  }
}