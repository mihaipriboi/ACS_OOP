#pragma once

#include "Package.h"
#include "../map/Map.h"
#include "../core/ConfigManager.h"

#include <vector>
#include <memory>
#include <cstdlib>
#include <random>

using namespace std;

class PackageManager {
private:
  vector<unique_ptr<Package>> allPackages;
  vector<pair<int, int>> clientLocations;
  int idCounter;

  mt19937 rng;

public:
  PackageManager(uint32_t seed = 12345) : idCounter(0), rng(seed) {}
  
  /* Scans map to find all Client (D) coordinates  */
  void discoverClients(const Map& map);
  
  /* Logic for spawning a package at the Hub */
  void spawnPackage(int currentTick);
  
  Package* getPackageById(int id);
  
  vector<Package*> getPackagesAtHub();
  vector<Package*> getPendingPackages();

  void markAsInTransit(int pkgId, int agentId);
  void markAsDelivered(int pkgId);
};