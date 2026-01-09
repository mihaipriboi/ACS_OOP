#pragma once

#include "PackageManager.h"
#include "../strategies/IDispatchStrategy.h"
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
  
  bool headlessMode;

  int currentTick;
  int maxTicks;
  int targetFPS = 50; /* Default */

  int totalCosts;
  int totalPenalties;
  int totalProfits;
  int finalScore;
  int packagesDelivered;
  int packagesDeliveredLate;

  int AGENT_DEATH_PENALTY;
  int PACKAGE_OVERDUE_PENALTY;
  int PACKAGE_NOT_DELIVERED_PENALTY;

public:
  SimulationManager(Map* m, vector<unique_ptr<Agent>>& f, PackageManager& p, bool headless);
  
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

  int getCosts() const { return totalCosts; }
  int getPenalties() const { return totalPenalties; }
  int getProfits() const { return totalProfits; }
  int getFinalScore() const { return finalScore; }
  int getPackagesDelivered() const { return packagesDelivered; }
  int getPackagesDeliveredLate() const { return packagesDeliveredLate; }
};