#include "SimulationManager.h"
#include "../core/UIHelper.h"
#include "../agents/AgentConstants.h"
#include "../map/MapConstants.h"

#include <cstdio>

SimulationManager::SimulationManager(Map* m, vector<unique_ptr<Agent>>& f, PackageManager& p, bool headless) 
  : gameMap(m), fleet(f), pkgManager(p), currentTick(0), totalCosts(0), totalPenalties(0),
   totalProfits(0), finalScore(0), packagesDelivered(0), packagesDeliveredLate(0), strategy(nullptr), headlessMode(headless) {
  maxTicks = ConfigManager::getInstance()->getMaxTicks();
  targetFPS = ConfigManager::getInstance()->getTargetFPS();
  AGENT_DEATH_PENALTY = ConfigManager::getInstance()->getAgentDeathPenalty();
  PACKAGE_OVERDUE_PENALTY = ConfigManager::getInstance()->getPackageOverduePenalty();
  PACKAGE_NOT_DELIVERED_PENALTY = ConfigManager::getInstance()->getPackageNotDeliveredPenalty();
}

void SimulationManager::runSingleTick() {
  if(currentTick % ConfigManager::getInstance()->getSpawnFrequency() == 0) {
    pkgManager.spawnPackage(currentTick);
  }

  bool aliveAgents = false;
  
  for(auto& agent : fleet) {
    if(agent->getState() == AgentState::DEAD) continue;
    updateAgentPhysics(agent.get());
    processDeliveries(agent.get());
    agent->moveTick();
    aliveAgents = true;
  }

  if(!aliveAgents) {
    currentTick = maxTicks; /* End simulation if all agents are dead */
    return;
  }
  
  if(strategy) {
    strategy->execute(fleet, pkgManager, *gameMap);
  }

  if(!headlessMode) {
    renderUI();
    this_thread::sleep_for(chrono::milliseconds(1000 / targetFPS));
  }
  
  currentTick++;
}

void SimulationManager::updateAgentPhysics(Agent* agent) {
  if(agent->getState() == AgentState::MOVING) {
    addCosts(agent->getCostPerTick());
  }

  CellType currentCell = gameMap->getCell(agent->getX(), agent->getY());
  bool atCharger = (currentCell == CellType::HUB || currentCell == CellType::STATION);

  if(atCharger) {
    if(agent->getBattery() < agent->getMaxBattery()) {
      agent->setState(AgentState::CHARGING);
      agent->chargeTick();
    } else {
      agent->setState(AgentState::IDLE);
    }
  } else if(agent->getState() == AgentState::MOVING) {
    agent->updateTickConsumption();
  }

  if(agent->getBattery() <= 0 && !atCharger) {
    agent->setState(AgentState::DEAD);
    addPenalties(AGENT_DEATH_PENALTY);
  }
}

void SimulationManager::processDeliveries(Agent* agent) {
  if(agent->getState() == AgentState::DEAD) return;

  /* Get the list of IDs this agent is carrying */
  const vector<int>& carriedIds = agent->getCarriedIds();
  if(carriedIds.empty()) return;

  /* We use a temporary vector to avoid modifying the list while iterating */
  vector<int> deliveredThisTick;

  for(int pkgId : carriedIds) {
    Package* p = pkgManager.getPackageById(pkgId);
    if(!p) continue;

    /* Check if agent is at the package's destination */
    if(agent->getX() == p->destX && agent->getY() == p->destY) {
      int remainingTime = p->deadline - (currentTick - p->spawnTick);
      addProfits(p->reward);

      /* Apply Penalties for lateness */
      if(remainingTime < 0) {
        addPenalties(PACKAGE_OVERDUE_PENALTY);
        packagesDeliveredLate++;
      }
      
      pkgManager.markAsDelivered(pkgId);
      deliveredThisTick.push_back(pkgId);

      packagesDelivered++;
    }
  }

  /* Remove delivered items from the agent's carried list */
  for(int id : deliveredThisTick) {
    agent->dropOffPackage(id);
  }
}

void SimulationManager::calculateFinalScore() {
  /* Additional penalties for undelivered packages */
  const auto& pkgs = pkgManager.getPendingPackages();
  for(const auto& p : pkgs) {
    if(p->status != PackageStatus::DELIVERED) {
      addPenalties(PACKAGE_NOT_DELIVERED_PENALTY);
    }
  }
}

void SimulationManager::renderUI() {
  /* ANSI Colors */
  const char* RED = "\033[1;31m";
  const char* YEL = "\033[1;33m";
  const char* GRN = "\033[1;32m";
  const char* RST = "\033[0m";

  /* Path Colors */
  const char* P_DRONE   = "\033[1;34m"; // Blue
  const char* P_SCOOTER = "\033[1;32m"; // Green
  const char* P_ROBOT   = "\033[1;35m"; // Purple/Magenta

  /* Clear Screen */
  printf("\033[H\033[J");
  
  UIHelper::printHeader("HiveMind Live Simulation");
  printf(" Tick: %d / %d\n\n", currentTick, maxTicks);

  for(int i = 0; i < gameMap->getRows(); i++) {
    for(int j = 0; j < gameMap->getCols(); j++) {
      bool agentFound = false;
      bool pathFound = false;
      const char* pathColor = RST;

      // Check for Agents (Highest Priority)
      for(auto& agent : fleet) {
        if(agent->getState() != AgentState::DEAD && agent->getX() == i && agent->getY() == j) {
          printf("%s ", AGENT_CHARS_TERMINAL[(int)agent->getType()].c_str());
          agentFound = true;
          break;
        }
      }
      if(agentFound) continue;

      // Check for Paths (Medium Priority)
      for(auto& agent : fleet) {
        if(agent->getState() == AgentState::DEAD) continue;
        
        // Assuming agent->getPath() returns a collection of pair<int, int>
        for(const auto& step : agent->getPath()) {
          if(step.first == i && step.second == j) {
            pathFound = true;
            if(agent->getType() == AgentType::DRONE) pathColor = P_DRONE;
            else if(agent->getType() == AgentType::SCOOTER) pathColor = P_SCOOTER;
            else if(agent->getType() == AgentType::ROBOT) pathColor = P_ROBOT;
            break;
          }
        }
        if(pathFound) break;
      }

      // Render the tile
      if(pathFound) {
        printf("%s%s%s ", pathColor, CELL_CHARS_TERMINAL[(int)CellType::PATH].c_str(), RST);
      } else {
        printf("%s ", CELL_CHARS_TERMINAL[(int)gameMap->getCell(i, j)].c_str());
      }
    }
    printf("\n");
  }

  UIHelper::printHeader("Legend");
  printf(" Environment: %s:Wall  %s:Road  %s:Hub  %s:Station  %s:Client\n",
         CELL_CHARS_TERMINAL[0].c_str(), CELL_CHARS_TERMINAL[1].c_str(), 
         CELL_CHARS_TERMINAL[2].c_str(), CELL_CHARS_TERMINAL[3].c_str(), 
         CELL_CHARS_TERMINAL[4].c_str());
  printf(" Agents:      %s:Drone  %s:Scooter  %s:Robot\n",
         AGENT_CHARS_TERMINAL[0].c_str(), AGENT_CHARS_TERMINAL[2].c_str(), 
         AGENT_CHARS_TERMINAL[1].c_str());
  
  printf("\n");
  UIHelper::printHeader("Financial Overview");
  printf(" Total Profits:    %s%d credits%s\n", GRN, totalProfits, RST);
  printf(" Total Costs:      %s%d credits%s\n", YEL, totalCosts, RST);
  printf(" Total Penalties:  %s%d credits%s\n\n", RED, totalPenalties, RST);
  if(finalScore < 0)
    printf(" Total Score:      %s%d credits%s\n", RED, finalScore, RST);
  else if(finalScore == 0)
    printf(" Total Score:      %d credits\n", finalScore);
  else
    printf(" Total Score:      %s%d credits%s\n", GRN, finalScore, RST);
  printf("\n Packages Delivered: %d\n", packagesDelivered);
  printf("      Of Which Late: %s%d%s\n", RED, packagesDeliveredLate, RST);

  printf("\n");
  UIHelper::printHeader("Fleet Telemetry");
  printf(" %-3s | %-7s | %-7s | %-4s | %-3s | %-7s | %-11s\n", "ID", "Type", "Pos", "Bat", "Pkg", "Dest", "State");
  printf("-----|---------|---------|------|-----|---------|-----------\n");
  for(const auto& agent : fleet) {
    const char* batCol = GRN;
    int bat = agent->getBattery();
    int maxBat = agent->getMaxBattery();
    int batPerc = (bat * 100) / maxBat;
    
    if(agent->getState() == AgentState::DEAD || batPerc <= 0) batCol = RED;
    else if(batPerc < 25) batCol = YEL;

    if(agent->getState() == AgentState::MOVING && agent->hasPath()) {
      printf(" %02d  | %-7s | (%2d,%2d) | %s%3d%%%s | %d/%d | (%2d,%2d) | %-11s\n",
            agent->getId(),
            agentTypeToString(agent->getType()), 
            agent->getX(), agent->getY(), 
            batCol, batPerc, RST,
            agent->getCurrentLoad(), agent->getCapacity(),
            agent->getDestination().first, agent->getDestination().second,
            AGENT_STATE_STRINGS[(int)agent->getState()].c_str());
    } else {
      printf(" %02d  | %-7s | (%2d,%2d) | %s%3d%%%s | %d/%d |   N/A   | %-11s\n",
            agent->getId(),
            agentTypeToString(agent->getType()), 
            agent->getX(), agent->getY(), 
            batCol, batPerc, RST,
            agent->getCurrentLoad(), agent->getCapacity(),
            AGENT_STATE_STRINGS[(int)agent->getState()].c_str());
    }
  }

  const auto& pkgs = pkgManager.getPendingPackages();
  int overdueCount = 0;

  printf("\n");
  UIHelper::printHeader("Pending Packages");
  printf(" %-3s | %-11s | %-6s | %-8s\n", "ID", "Destination", "Reward", "Deadline");
  printf("-----|-------------|--------|----------\n");
  
  // reverse order to show the most recently spawned packages first
  for(auto it = pkgs.rbegin(); it != pkgs.rend(); ++it) {
    const auto& p = *it;

    int remaining = p->deadline - (currentTick - p->spawnTick);

    const char* timeCol = (remaining <= 3) ? YEL : RST;

    if(remaining > 6) { timeCol = GRN; } 
    else if(remaining >= 0 && remaining <= 3) { timeCol = YEL; } 
    else { 
      timeCol = RED;
      overdueCount++; 
    }

    if(overdueCount < 5 || timeCol != RED) {
      printf(" %02d  | (%2d, %2d)    | %4d   | %s%d ticks%s\n", 
             p->id, p->destX, p->destY, p->reward, 
             timeCol, remaining, RST);
    }
  }

  if(overdueCount >= 5) {
    printf("%s ... and %d more overdue packages not shown ...%s\n", RED, overdueCount - 5, RST);
  }
}