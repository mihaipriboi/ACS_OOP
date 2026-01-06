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
      else if(strcmp(key, "WALL_DENSITY:") == 0) wallDensity = val;
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
  UIHelper::printHeader("Procedural Generation");
  printf("Wall Density: %d%%\n", wallDensity);
  UIHelper::printHeader();
  printf("\n");
}