#pragma once

#include "IDispatchStrategy.h"
#include "../map/Map.h"
#include "../agents/Agent.h"

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/* * AdvancedHiveStrategy:
 * 1. Assigns packages to IDLE agents at the Hub if they can complete the round trip with current battery.
 * 2. Prioritizes faster agents (Drones > Scooters > Robots) for assignments.
 * 3. Implements range check to ensure agents can complete round trip.
 * 4. Automatically returns agents to the Hub if they have no current path.
 */

class AdvancedHiveStrategy : public IDispatchStrategy {
private:
  int getActualPathDistance(Agent* agent, int x1, int y1, int x2, int y2, const Map& map) {
    if(x1 == x2 && y1 == y2) return 0;

    if(agent->canPassWalls()) {
      LinearPathAlgorithm lpa;
      vector<pair<int, int>> path = lpa.calculatePath(x1, y1, x2, y2, map);
      if(path.empty()) return 999999;
      return (int)path.size();
    }

    /* Ground units must use A* to find a valid route  */
    AStarAlgorithm astar;
    vector<pair<int, int>> path = astar.calculatePath(x1, y1, x2, y2, map);

    /* If no path exists, return a value representing infinity */
    if(path.empty()) return 999999;
    return (int)path.size();
  }

  bool hasEnoughRange(Agent* agent, int destX, int destY, int hubX, int hubY, const Map& map) {
    int distToClient = getActualPathDistance(agent, agent->getX(), agent->getY(), destX, destY, map);
    int distBackToHub = getActualPathDistance(agent, destX, destY, hubX, hubY, map);
    int totalSteps = distToClient + distBackToHub;

    /* If any segment is unreachable, the agent cannot take the package */
    if(totalSteps >= 999999) return false;

    int tripTicks = (int)ceil((double)totalSteps / agent->getSpeed()) + 2; /* +2 ticks for loading/unloading */

    int requiredBattery = tripTicks * agent->getConsumption();

    return requiredBattery <= agent->getBattery();
  }

public:
  void execute(vector<unique_ptr<Agent>>& fleet, PackageManager& pkgManager, const Map& map) override {
    int hubX = map.getHubX();
    int hubY = map.getHubY();
    auto availablePackages = pkgManager.getPackagesAtHub();

    if(!availablePackages.empty()) {
      for(auto* pkg : availablePackages) {
        Agent* bestAgent = nullptr;

        /* Prioritize Drone -> Scooter -> Robot based on speed/range */
        vector<AgentType> priority = {AgentType::DRONE, AgentType::SCOOTER, AgentType::ROBOT};

        for(AgentType type : priority) {
          for(auto& agent : fleet) {
            if(agent->getType() == type && 
              agent->getState() != AgentState::DEAD && 
              agent->canLoadMore()) {
              
              if(hasEnoughRange(agent.get(), pkg->destX, pkg->destY, hubX, hubY, map)) {
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
          /* Remove package from local tracking list for this tick */
          availablePackages.erase(remove(availablePackages.begin(), availablePackages.end(), pkg), availablePackages.end());
        }
      }
    }

    /* Standard maintenance for the fleet */
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