#pragma once

#include "IDispatchStrategy.h"
#include "../map/Map.h"
#include "../agents/Agent.h"

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class OptimizedGreedyStrategy : public IDispatchStrategy {
private:
  /* Manhattan distance helper for grid-based range calculation */
  int calculateDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  }

  /* * Range Check Logic:
   * Max Steps = (Current Battery / Consumption per Tick) * Speed
   * Safety: Max Steps must be >= (Distance to Client + Distance back to Hub)
   */
  bool hasEnoughRange(Agent* agent, int destX, int destY, int hubX, int hubY) {
    int distToClient = calculateDistance(agent->getX(), agent->getY(), destX, destY);
    int distBackToHub = calculateDistance(destX, destY, hubX, hubY);
    int totalDist = distToClient + distBackToHub;

    /* Agent stats from specifications [cite: 38, 39] */
    int consumption = 0;
    /* Map consumption based on type manually if not exposed via getter */
    switch(agent->getType()) {
      case AgentType::DRONE:   consumption = 10; break;
      case AgentType::ROBOT:   consumption = 2;  break;
      case AgentType::SCOOTER: consumption = 5;  break;
    }

    int maxTicksAvailable = agent->getBattery() / consumption;
    int maxDistanceAvailable = maxTicksAvailable * agent->getSpeed();

    return maxDistanceAvailable >= totalDist;
  }

public:
  void execute(vector<unique_ptr<Agent>>& fleet, PackageManager& pkgManager, const Map& map) override {
    int hubX = map.getHubX();
    int hubY = map.getHubY();
    auto availablePackages = pkgManager.getPackagesAtHub();

    if(availablePackages.empty()) {
      /* Maintenance: Ensure all non-moving agents outside Hub are coming home */
      for(auto& agent : fleet) {
        if(agent->getState() != AgentState::DEAD && !agent->hasPath()) {
          if(agent->getX() != hubX || agent->getY() != hubY) {
            agent->setNewDestination(hubX, hubY, map);
            agent->setState(AgentState::MOVING);
          }
        }
      }
      return;
    }

    for(auto* pkg : availablePackages) {
      Agent* bestAgent = nullptr;

      /* Prioritize Drone -> Scooter -> Robot based on speed/range [cite: 38] */
      vector<AgentType> priority = {AgentType::DRONE, AgentType::SCOOTER, AgentType::ROBOT};

      for(AgentType type : priority) {
        for(auto& agent : fleet) {
          if(agent->getType() == type && 
             agent->getState() == AgentState::IDLE && 
             agent->getBattery() >= agent->getMaxBattery() &&
             agent->canLoadMore()) {
            
            if(hasEnoughRange(agent.get(), pkg->destX, pkg->destY, hubX, hubY)) {
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

    /* Standard maintenance for rest of the fleet */
    for(auto& agent : fleet) {
      if(agent->getState() == AgentState::DEAD) continue;
      
      if(!agent->hasPath()) {
        if(agent->getX() == hubX && agent->getY() == hubY) {
          if(agent->getBattery() < agent->getMaxBattery()) {
            agent->setState(AgentState::CHARGING); /*  */
          } else {
            agent->setState(AgentState::IDLE); /* [cite: 44] */
          }
        } else {
          agent->setNewDestination(hubX, hubY, map);
          agent->setState(AgentState::MOVING);
        }
      }
    }
  }
};