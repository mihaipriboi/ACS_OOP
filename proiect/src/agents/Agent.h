#pragma once

#include "../map/MapConstants.h"
#include "AgentConstants.h"
#include "../pathfinding/IPathAlgorithm.h"

#include <string>
#include <vector>
#include <deque>
#include <memory>

using namespace std;

class Map; /* Forward declaration to avoid circular dependency */

class Agent {
protected:
  int id;
  AgentType type;
  int posX, posY;
  int speed;
  int battery;
  int maxBattery;
  int consumption;
  int costPerTick;
  int capacity;
  AgentState state;

  vector<int> carriedPackageIds;
  deque<pair<int, int>> currentPath;
  unique_ptr<IPathAlgorithm> pathfinder;

public:
  Agent(int id, AgentType t, int x, int y, unique_ptr<IPathAlgorithm> pf);
  virtual ~Agent();

  virtual char getSymbol() const = 0;
  virtual bool canPassWalls() const = 0;
  
  /* Logic Methods (Implemented in .cpp) */
  void setNewDestination(int destX, int destY, const Map& map);
  void moveTick();
  void updateTickConsumption();
  void chargeTick();
  void pickUpPackage(int pkgId);
  void dropOffPackage(int pkgId);

  /* Path Management */
  void setPath(const vector<pair<int, int>>& newPath);
  bool hasPath() const { return !currentPath.empty(); }
  pair<int, int> getNextStep();

  /* Inline Getters & Setters */
  int getX() const { return posX; }
  int getY() const { return posY; }
  void setPosition(int x, int y) { posX = x; posY = y; }
  pair<int, int> getDestination() const {
    if(currentPath.empty()) return {posX, posY};
    return currentPath.back();
  }
  const deque<pair<int, int>>& getPath() const { return currentPath; }
  
  int getBattery() const { return battery; }
  int getMaxBattery() const { return maxBattery; }
  int getSpeed() const { return speed; }
  int getCapacity() const { return capacity; }
  int getCostPerTick() const { return costPerTick; }
  int getConsumption() const { return consumption; }
  int getId() const { return id; }
  
  AgentType getType() const { return type; }
  AgentState getState() const { return state; }
  void setState(AgentState s) { state = s; }

  bool canLoadMore() const { return carriedPackageIds.size() < (size_t)capacity; }
  const vector<int>& getCarriedIds() const { return carriedPackageIds; }
  int getCurrentLoad() const { return (int)carriedPackageIds.size(); }
};