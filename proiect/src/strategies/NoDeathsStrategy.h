#pragma once

#include "IDispatchStrategy.h"
#include "../map/Map.h"
#include "../agents/Agent.h"
#include "../pathfinding/AStarAlgorithm.h"
#include "../pathfinding/LinearPathAlgorithm.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

/* * NoDeathsStrategy Strategy:
 * 1. Assigns packages to IDLE agents at the Hub if they have enough battery and range.
 * 2. Prioritizes faster agents (Drones > Scooters > Robots) for assignments.
 * 3. Implements precise pathfinding to ensure agents can complete round trip without dying.
 * 4. Automatically returns agents to the Hub if they have no current path.
 */

class NoDeathsStrategy : public IDispatchStrategy {
private:
  /* Cache to store: [PackageID, AgentType] -> Required Battery Units */
  map<pair<int, AgentType>, int> energyCache;

  int getActualPathDistance(Agent* agent, int x1, int y1, int x2, int y2, const Map& map) {
    if(x1 == x2 && y1 == y2) return 0;

    if(agent->canPassWalls()) {
      LinearPathAlgorithm lpa;
      auto path = lpa.calculatePath(x1, y1, x2, y2, map);
      return path.empty() ? 999999 : (int)path.size();
    }

    AStarAlgorithm astar;
    auto path = astar.calculatePath(x1, y1, x2, y2, map);
    return path.empty() ? 999999 : (int)path.size();
  }

  int getCachedTripCost(Agent* agent, Package* pkg, int hubX, int hubY, const Map& map) {
    pair<int, AgentType> key = {pkg->id, agent->getType()};
    
    if(energyCache.find(key) != energyCache.end()) {
      return energyCache[key];
    }

    int distToClient = getActualPathDistance(agent, hubX, hubY, pkg->destX, pkg->destY, map);
    int distBackToHub = getActualPathDistance(agent, pkg->destX, pkg->destY, hubX, hubY, map);
    int totalSteps = distToClient + distBackToHub;

    if(totalSteps >= 999999) {
      energyCache[key] = 999999;
      return 999999;
    }

    /* Ticks = Steps / Speed. We use +2 for safety margin during delivery. */
    int tripTicks = (int)ceil((double)totalSteps / agent->getSpeed()) + 2;
    int requiredBattery = tripTicks * agent->getConsumption();

    energyCache[key] = requiredBattery;
    return requiredBattery;
  }

  /* Modified to prioritize the longest paths */
  int getPackagePriority(Package* pkg, int hubX, int hubY) {
    /* Using Manhattan as a heuristic for sorting priority to keep the execute tick fast */
    return abs(pkg->destX - hubX) + abs(pkg->destY - hubY);
  }

public:
  const char* getName() const override { return "No Deaths"; }

  void execute(vector<unique_ptr<Agent>>& fleet, PackageManager& pkgManager, const Map& map) override {
    int hubX = map.getHubX();
    int hubY = map.getHubY();
    auto availablePackages = pkgManager.getPackagesAtHub();

    /* Sort packages by distance (longest first) */
    sort(availablePackages.begin(), availablePackages.end(), 
         [this, hubX, hubY](Package* a, Package* b) {
           return getPackagePriority(a, hubX, hubY) > getPackagePriority(b, hubX, hubY);
         });

    if(!availablePackages.empty()) {
      for(auto* pkg : availablePackages) {
        Agent* bestAgent = nullptr;

        /* Standard dispatch priority: Drones -> Scooters -> Robots  */
        vector<AgentType> priority = {AgentType::DRONE, AgentType::SCOOTER, AgentType::ROBOT};

        for(AgentType type : priority) {
          for(auto& agent : fleet) {
            if(agent->getType() == type && 
               agent->getX() == hubX && agent->getY() == hubY &&
               agent->getState() != AgentState::DEAD && 
               agent->canLoadMore()) {
              
              int requiredBattery = getCachedTripCost(agent.get(), pkg, hubX, hubY, map);

              /* Robots (300 battery) will pass this check for long paths where Drones (100) might fail. */
              if(agent->getBattery() >= requiredBattery && requiredBattery < 999999) {
                bestAgent = agent.get();
                break;
              }
            }
          }
          if(bestAgent) break;
        }

        if(bestAgent) {
          pkgManager.markAsInTransit(pkg->id, bestAgent->getId());
          bestAgent->pickUpPackage(pkg->id);
          bestAgent->setNewDestination(pkg->destX, pkg->destY, map);
          bestAgent->setState(AgentState::MOVING);
          
          availablePackages.erase(remove(availablePackages.begin(), availablePackages.end(), pkg), availablePackages.end());
        }
      }
    }

    for(auto& agent : fleet) {
      if(agent->getState() == AgentState::DEAD) continue;
      
      if(!agent->hasPath()) {
        if(agent->getX() == hubX && agent->getY() == hubY) {
          if(agent->getBattery() < agent->getMaxBattery()) {
            agent->setState(AgentState::CHARGING);
          } else {
            agent->setState(AgentState::IDLE);
          }
        } else {
          agent->setNewDestination(hubX, hubY, map);
          agent->setState(AgentState::MOVING);
        }
      }
    }
  }
};