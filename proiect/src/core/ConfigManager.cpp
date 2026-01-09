#include "ConfigManager.h"
#include "UIHelper.h"

#include <cstring>

ConfigManager* ConfigManager::instance = nullptr;

ConfigManager::ConfigManager() : 
  mapWidth(0), mapHeight(0), maxTicks(0), maxStations(0), 
  clientsCount(0), dronesCount(0), robotsCount(0), 
  scootersCount(0), totalPackages(0), spawnFrequency(0) {}

ConfigManager* ConfigManager::getInstance() {
  if(instance == nullptr) {
    instance = new ConfigManager();
  }
  return instance;
}

bool ConfigManager::loadConfig(const char* filename) {
  FILE* file = fopen(filename, "r");
  if(!file) return false;

  char line[256];
  while(fgets(line, sizeof(line), file)) {
    /* Skip empty lines or lines starting with comments */
    if(line[0] == '\n' || line[0] == '\r' || (line[0] == '/' && line[1] == '/')) {
      continue;
    }

    char key[100];
    int val;

    int found = sscanf(line, "%s %d", key, &val);
    
    if(found >= 2) {
      if(strcmp(key, "MAP_SIZE:") == 0) {
        mapWidth = val;
        sscanf(strstr(line, key) + strlen(key) + strlen(" "), "%*d %d", &mapHeight);
      }
      else if(strcmp(key, "MAX_TICKS:") == 0) maxTicks = val;
      else if(strcmp(key, "MAX_STATIONS:") == 0) maxStations = val;
      else if(strcmp(key, "CLIENTS_COUNT:") == 0) clientsCount = val;
      else if(strcmp(key, "DRONES:") == 0) dronesCount = val;
      else if(strcmp(key, "ROBOTS:") == 0) robotsCount = val;
      else if(strcmp(key, "SCOOTERS:") == 0) scootersCount = val;
      else if(strcmp(key, "TOTAL_PACKAGES:") == 0) totalPackages = val;
      else if(strcmp(key, "SPAWN_FREQUENCY:") == 0) spawnFrequency = val;
      else if(strcmp(key, "WALL_DENSITY_RANDOM:") == 0) wallDensityRandom = val;
      else if(strcmp(key, "WALL_DENSITY_MAZE:") == 0) wallDensityMaze = val;
      else if(strcmp(key, "WALL_DENSITY_ARCHIPELAGO:") == 0) wallDensityArchipelago = val;
      else if(strcmp(key, "RADIAL_RING_SPACING:") == 0) radialRingSpacing = val;
      else if(strcmp(key, "RADIAL_PLAZA_RADIUS:") == 0) radialPlazaRadius = val;
      else if(strcmp(key, "RADIAL_RING_ROAD_WIDTH:") == 0) radialRingRoadWidth = val;
      else if(strcmp(key, "RADIAL_MAX_RINGS:") == 0) radialMaxRings = val;
      else if(strcmp(key, "DISTRICT_BLOCK_SIZE:") == 0) districtBlockSize = val;
      else if(strcmp(key, "AGENT_DEATH_PENALTY:") == 0) agentDeathPenalty = val;
      else if(strcmp(key, "PACKAGE_OVERDUE_PENALTY:") == 0) packageOverduePenalty = val;
      else if(strcmp(key, "PACKAGE_NOT_DELIVERED_PENALTY:") == 0) packageNotDeliveredPenalty = val;
      else if(strcmp(key, "TARGET_FPS:") == 0) targetFPS = val;
    }
  }

  fclose(file);
  return true;
}

void ConfigManager::printSettings() {
  UIHelper::printHeader("HiveMind Simulation Setup");
  printf("Map Resolution: %d x %d\n", mapWidth, mapHeight);
  printf("Duration: %d ticks\n", maxTicks);
  printf("Extra Stations: %d\n", maxStations);
  printf("Client Targets: %d\n", clientsCount);
  printf("Total Packages to Deliver: %d\n", totalPackages);
  printf("Spawn Frequency: 1 every %d ticks\n", spawnFrequency);
  UIHelper::printHeader("Initial Fleet");
  printf("Drones: %d\n", dronesCount);
  printf("Robots: %d\n", robotsCount);
  printf("Scooters: %d\n", scootersCount);
  UIHelper::printHeader("Penalties");
  printf("Agent Death Penalty: %d\n", agentDeathPenalty);
  printf("Package Overdue Penalty: %d\n", packageOverduePenalty);
  printf("Package Not Delivered Penalty: %d\n", packageNotDeliveredPenalty);
  UIHelper::printHeader("Procedural Generation");
  printf("Wall Density (Random): %d%%\n", wallDensityRandom);
  printf("Wall Density (Maze): %d%%\n", wallDensityMaze);
  printf("Wall Density (Archipelago): %d%%\n", wallDensityArchipelago);
  printf("Radial Ring Spacing: %d\n", radialRingSpacing);
  printf("Radial Plaza Radius: %d\n", radialPlazaRadius);
  printf("Radial Ring Road Width: %d\n", radialRingRoadWidth);
  printf("Radial Max Rings: %d\n", radialMaxRings);
  printf("District Block Size: %d\n", districtBlockSize);
  UIHelper::printHeader("Simulation Settings");
  printf("Target FPS: %d\n", targetFPS);
  UIHelper::printHeader();
  printf("\n");
}