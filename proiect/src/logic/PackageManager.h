#pragma once

#include "Package.h"
#include "../map/Map.h"
#include "../core/ConfigManager.h"

#include <vector>
#include <memory>
#include <cstdlib>

using namespace std;

class PackageManager {
private:
  vector<unique_ptr<Package>> pendingPackages;
  vector<pair<int, int>> clientLocations;
  int idCounter;

public:
  PackageManager();
  
  /* Scans map to find all Client (D) coordinates  */
  void discoverClients(const Map& map);
  
  /* Logic for spawning a package at the Hub */
  void spawnPackage(int currentTick);
  
  const vector<unique_ptr<Package>>& getPendingPackages() const;
  void removeDelivered();
};