#include "PackageManager.h"

PackageManager::PackageManager() : idCounter(0) {}

void PackageManager::discoverClients(const Map& map) {
  for(int i = 0; i < map.getRows(); i++) {
    for(int j = 0; j < map.getCols(); j++) {
      if(map.getCell(i, j) == CellType::CLIENT) {
        clientLocations.push_back({i, j});
      }
    }
  }
}

void PackageManager::spawnPackage(int currentTick) {
  if(clientLocations.empty()) return;

  ConfigManager* cfg = ConfigManager::getInstance();
  
  /* Ensure we don't exceed total package limit if one exists */
  if(idCounter >= cfg->getTotalPackages()) return;

  /* Select random values for package attributes */
  int targetIdx = rand() % clientLocations.size();
  int reward = 200 + (rand() % 601); // 200-800
  int deadline = 10 + (rand() % 11); // 10-20

  pendingPackages.push_back(make_unique<Package>(
    idCounter++, 
    clientLocations[targetIdx].first, 
    clientLocations[targetIdx].second, 
    reward, 
    deadline, 
    currentTick
  ));
}

const vector<unique_ptr<Package>>& PackageManager::getPendingPackages() const {
  return pendingPackages;
}