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
  const int targetFPS = 30;

  int totalCosts;
  int totalPenalties;
  int totalProfits;
  int finalScore;
  int packagesDelivered;
  int packagesDeliveredLate;

  const int AGENT_DEATH_PENALTY = 500;
  const int PACKAGE_OVERDUE_PENALTY = 50;
  const int PACKAGE_NOT_DELIVERED_PENALTY = 200;

public:
  SimulationManager(Map* m, vector<unique_ptr<Agent>>& f, PackageManager& p);
  
  void setStrategy(IDispatchStrategy* s) { strategy = s; }
  bool isFinished() const { return currentTick >= maxTicks; }
  int getCurrentTick() const { return currentTick; }

  void addCosts(int amount) { totalCosts += amount; finalScore -= amount; }
  void addPenalties(int amount) { totalPenalties += amount; finalScore -= amount; }
  void addProfits(int amount) { totalProfits += amount; finalScore += amount; }

  void runSingleTick();
  void updateAgentPhysics(Agent* agent);
  void processDeliveries(Agent* agent);
  void calculateFinalScore();

  void renderUI();
};