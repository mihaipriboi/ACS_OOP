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

  int wallDensityRandom;      // Percentage of walls in random generation
  int wallDensityMaze;        // Percentage of walls in maze generation
  int wallDensityArchipelago; // Percentage of walls in archipelago generation

  int radialRingSpacing;      // Spacing between rings in radial generation
  int radialPlazaRadius;      // Radius of the central plaza in radial generation
  int radialRingRoadWidth;    // Width of the ring roads in radial generation
  int radialMaxRings;         // Maximum number of rings in radial generation

  int districtBlockSize;      // Block size for district generation

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
  int getWallDensityRandom() const { return wallDensityRandom; }
  int getWallDensityMaze() const { return wallDensityMaze; }
  int getWallDensityArchipelago() const { return wallDensityArchipelago; }
  int getRadialRingSpacing() const { return radialRingSpacing; }
  int getRadialPlazaRadius() const { return radialPlazaRadius; }
  int getRadialRingRoadWidth() const { return radialRingRoadWidth; }
  int getRadialMaxRings() const { return radialMaxRings; }
  int getDistrictBlockSize() const { return districtBlockSize; }

  /* Displays the current configuration in the terminal */
  void printSettings();
};