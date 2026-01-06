#include "SimulationManager.h"
#include "../core/UIHelper.h"
#include "../agents/AgentConstants.h"
#include "../map/MapConstants.h"

#include <cstdio>

SimulationManager::SimulationManager(Map* m, vector<unique_ptr<Agent>>& f, PackageManager& p) 
  : gameMap(m), fleet(f), pkgManager(p), currentTick(0), strategy(nullptr) {
  maxTicks = ConfigManager::getInstance()->getMaxTicks();
}

void SimulationManager::runSingleTick() {
  if(currentTick % ConfigManager::getInstance()->getSpawnFrequency() == 0) {
    pkgManager.spawnPackage(currentTick);
  }
  
  /* Placeholder for Physics update logic */
  for(auto& agent : fleet) {
    if(agent->getState() == AgentState::DEAD) continue;
    /* updateAgentPhysics(agent); */
  }
  
  if(strategy) {
    strategy->execute(fleet, pkgManager, *gameMap);
  }

  renderUI();
  
  this_thread::sleep_for(chrono::milliseconds(1000 / targetFPS));
  currentTick++;
}

void SimulationManager::renderUI() {
  /* ANSI Colors */
  const char* RED = "\033[1;31m";
  const char* YEL = "\033[1;33m";
  const char* GRN = "\033[1;32m";
  const char* RST = "\033[0m";

  /* Clear Screen */
  printf("\033[H\033[J");
  
  UIHelper::printHeader("HiveMind Live Simulation");
  printf("Tick: %d / %d\n\n", currentTick, maxTicks);

  for(int i = 0; i < gameMap->getRows(); i++) {
    for(int j = 0; j < gameMap->getCols(); j++) {
      bool agentFound = false;
      for(auto& agent : fleet) {
        if(agent->getState() != AgentState::DEAD && agent->getX() == i && agent->getY() == j 
           && (gameMap->getCell(i, j) == CellType::WALL || gameMap->getCell(i, j) == CellType::SPACE)) {
          printf("%s ", AGENT_CHARS_TERMINAL[(int)agent->getType()].c_str());
          agentFound = true;
          break;
        }
      }
      if(!agentFound) {
        printf("%s ", CELL_CHARS_TERMINAL[(int)gameMap->getCell(i, j)].c_str());
      }
    }
    printf("\n");
  }

  UIHelper::printHeader("Legend");
  printf("Environment: %s:Wall  %s:Road  %s:Hub  %s:Station  %s:Client\n",
         CELL_CHARS_TERMINAL[0].c_str(), CELL_CHARS_TERMINAL[1].c_str(), 
         CELL_CHARS_TERMINAL[2].c_str(), CELL_CHARS_TERMINAL[3].c_str(), 
         CELL_CHARS_TERMINAL[4].c_str());
  printf("Agents:      %s:Drone %s:Robot %s:Scooter\n",
         AGENT_CHARS_TERMINAL[0].c_str(), AGENT_CHARS_TERMINAL[1].c_str(), 
         AGENT_CHARS_TERMINAL[2].c_str());
  
  printf("\n");
  UIHelper::printHeader("Fleet Telemetry");
  printf(" %-3s | %-7s | %-7s | %-4s | %-3s | %-11s\n", "ID", "Type", "Pos", "Bat", "Pkg", "Dest");
  printf("-----|---------|---------|------|-----|---------\n");
  for(const auto& agent : fleet) {
    const char* batCol = GRN;
    int bat = agent->getBattery();
    int maxBat = agent->getMaxBattery();
    int batPerc = (bat * 100) / maxBat;
    
    if(agent->getState() == AgentState::DEAD || batPerc <= 0) batCol = RED;
    else if(batPerc < 25) batCol = YEL;

    printf(" %02d  | %-7s | (%2d,%2d) | %s%3d%%%s | %d/%d | %-11s\n",
           agent->getId(),
           agentTypeToString(agent->getType()), 
           agent->getX(), agent->getY(), 
           batCol, batPerc, RST,
           0, agent->getCapacity(),
           (agent->getState() == AgentState::DEAD ? "OFFLINE" : "IDLE"));
  }

  int overdueCount = 0;
  const auto& pkgs = pkgManager.getPendingPackages();

  printf("\n");
  UIHelper::printHeader("Pending Packages (On Time)");
  printf(" %-3s | %-11s | %-6s | %-8s\n", "ID", "Destination", "Reward", "Deadline");
  printf("-----|-------------|--------|----------\n");
  
  for(const auto& p : pkgs) {
    int remaining = p->deadline - (currentTick - p->spawnTick);
    if(remaining < 0) {
      overdueCount++;
      continue;
    }

    const char* timeCol = (remaining <= 2) ? YEL : RST;
    printf(" %02d  | (%2d, %2d)    | %4d   | %s%d ticks%s\n", 
           p->id, p->destX, p->destY, p->reward, 
           timeCol, remaining, RST);
  }

  if(overdueCount > 0) {
    printf("\n%sOverdue Packages: %d%s\n", RED, overdueCount, RST);
  }
  
  UIHelper::printHeader("");
}