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

  allPackages.push_back(make_unique<Package>(
    idCounter++, 
    clientLocations[targetIdx].first, 
    clientLocations[targetIdx].second, 
    reward, 
    deadline, 
    currentTick
  ));
}

Package* PackageManager::getPackageById(int id) {
  for(auto& p : allPackages) {
    if(p->id == id) return p.get();
  }
  return nullptr;
}

/* Returns packages currently available for pickup at the Hub */
vector<Package*> PackageManager::getPackagesAtHub() {
  vector<Package*> atHub;
  for(auto& p : allPackages) {
    if(p->status == PackageStatus::AT_HUB) atHub.push_back(p.get());
  }
  return atHub;
}

vector<Package*> PackageManager::getPendingPackages() {
  vector<Package*> pending;
  for(auto& p : allPackages) {
    if(p->status != PackageStatus::DELIVERED) pending.push_back(p.get());
  }
  return pending;
}

/* Status update methods */
void PackageManager::markAsInTransit(int pkgId, int agentId) {
  Package* p = getPackageById(pkgId);
  if(p) {
    p->status = PackageStatus::IN_TRANSIT;
    p->carrierId = agentId;
  }
}

void PackageManager::markAsDelivered(int pkgId) {
  Package* p = getPackageById(pkgId);
  if(p) p->status = PackageStatus::DELIVERED;
}