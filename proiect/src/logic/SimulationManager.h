#pragma once

#include "PackageManager.h"
#include "IDispatchStrategy.h"
#include "../map/Map.h"
#include "../agents/Agent.h"
#include "../core/ConfigManager.h"

#include <vector>
#include <memory>
#include <thread>
#include <chrono>

using namespace std;

class SimulationManager {
private:
  Map* gameMap;
  vector<unique_ptr<Agent>>& fleet; /* Reference to fleet owned by main */
  PackageManager& pkgManager;       /* Reference to manager owned by main */
  IDispatchStrategy* strategy;
  
  int currentTick;
  int maxTicks;
  const int targetFPS = 10;

public:
  SimulationManager(Map* m, vector<unique_ptr<Agent>>& f, PackageManager& p);
  
  void setStrategy(IDispatchStrategy* s) { strategy = s; }
  bool isFinished() const { return currentTick >= maxTicks; }
  int getCurrentTick() const { return currentTick; }
  
  void runSingleTick();
  void renderUI();
};