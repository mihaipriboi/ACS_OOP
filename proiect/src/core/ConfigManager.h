#pragma once

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

/* Singleton class to handle simulation parameters */
class ConfigManager {
private:
  static ConfigManager* instance;

  ConfigManager(); // Private constructor

  /* Simulation Parameters */
  int mapWidth;
  int mapHeight;
  int maxTicks;
  int maxStations;
  int clientsCount;
  int dronesCount;
  int robotsCount;
  int scootersCount;
  int totalPackages;
  int spawnFrequency;

  int wallDensity; // Percentage of walls in procedural generation

public:
  static ConfigManager* getInstance();

  /* Loads configuration */
  bool loadConfig(const char* filename);
  
  /* Const Getters, Read-only */
  int getMapWidth() const { return mapWidth; }
  int getMapHeight() const { return mapHeight; }
  int getMaxTicks() const { return maxTicks; }
  int getMaxStations() const { return maxStations; }
  int getClientsCount() const { return clientsCount; }
  int getDronesCount() const { return dronesCount; }
  int getRobotsCount() const { return robotsCount; }
  int getScootersCount() const { return scootersCount; }
  int getTotalPackages() const { return totalPackages; }
  int getSpawnFrequency() const { return spawnFrequency; }
  int getWallDensity() const { return wallDensity; }
  
  /* Displays the current configuration in the terminal */
  void printSettings();
};