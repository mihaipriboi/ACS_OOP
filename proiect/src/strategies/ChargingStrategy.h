#pragma once

#include "IDispatchStrategy.h"
#include "../map/Map.h"
#include "../agents/Agent.h"

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/* * ChargingStrategy:
 * 1. Assigns packages to IDLE agents if they can complete the trip or reach a station.
 * 2. Strategy: Hub -> Client -> Nearest Charging Station (S or B).
 * 3. Ensures agents stay at stations to recharge fully before returning to the Hub.
 */
class ChargingStrategy : public IDispatchStrategy {
private:
  /* Manhattan distance helper for grid-based range calculation */
  int calculateDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  }

  /* Scans the map for all valid charging locations (Hub and Stations) */
  vector<pair<int, int>> getChargingLocations(const Map& map) {
    vector<pair<int, int>> stations;
    for(int r = 0; r < map.getRows(); r++) {
      for(int c = 0; c < map.getCols(); c++) {
        CellType type = map.getCell(r, c);
        if(type == CellType::STATION || type == CellType::HUB) {
          stations.push_back({r, c});
        }
      }
    }
    return stations;
  }

  /* Finds the coordinate of the closest station to a specific point */
  pair<int, int> findNearestStation(int x, int y, const vector<pair<int, int>>& stations) {
    pair<int, int> nearest = stations[0];
    int minDist = calculateDistance(x, y, nearest.first, nearest.second);

    for(const auto& st : stations) {
      int d = calculateDistance(x, y, st.first, st.second);
      if(d < minDist) {
        minDist = d;
        nearest = st;
      }
    }
    return nearest;
  }

  /* * Extended Range Check:
   * Total Distance = (Agent to Client) + (Client to Nearest Station)
   * Includes safety buffer for pathing around obstacles.
   */
  bool canReachSafety(Agent* agent, int destX, int destY, const vector<pair<int, int>>& stations) {
    int distToClient = calculateDistance(agent->getX(), agent->getY(), destX, destY);
    pair<int, int> nearSt = findNearestStation(destX, destY, stations);
    int distToStation = calculateDistance(destX, destY, nearSt.first, nearSt.second);
    
    int totalDistNeeded = distToClient + distToStation;
    int maxDistanceAvailable = (agent->getBattery() / agent->getConsumption()) * agent->getSpeed();

    return maxDistanceAvailable >= (totalDistNeeded + 2);
  }

public:
  const char* getName() const override { return "Charging"; }

  void execute(vector<unique_ptr<Agent>>& fleet, PackageManager& pkgManager, const Map& map) override {
    int hubX = map.getHubX();
    int hubY = map.getHubY();
    auto stations = getChargingLocations(map);
    auto availablePackages = pkgManager.getPackagesAtHub();

    /* Dispatching Logic: Only send agents if IDLE and fully charged */
    if(!availablePackages.empty()) {
      for(auto* pkg : availablePackages) {
        Agent* bestAgent = nullptr;
        vector<AgentType> priority = {AgentType::DRONE, AgentType::SCOOTER, AgentType::ROBOT};

        for(AgentType type : priority) {
          for(auto& agent : fleet) {
            if(agent->getType() == type && 
              agent->getState() == AgentState::IDLE && 
              agent->getBattery() >= agent->getMaxBattery() &&
              agent->canLoadMore()) {
              
              if(canReachSafety(agent.get(), pkg->destX, pkg->destY, stations)) {
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

    /* Maintenance Logic: Returns to Hub only after full recharge */
    for(auto& agent : fleet) {
      if(agent->getState() == AgentState::DEAD || agent->hasPath()) continue;

      /* Wait until SimulationManager finishes charging the agent */
      if(agent->getState() == AgentState::CHARGING) continue;

      if(agent->getX() == hubX && agent->getY() == hubY) {
        /* Already at Hub and not charging implies it is IDLE and 100% */
        agent->setState(AgentState::IDLE);
      } else {
        /* Agent is not at the Hub and not charging. Determine if it needs a station or can go home. */
        int distToHub = calculateDistance(agent->getX(), agent->getY(), hubX, hubY);
        int range = (agent->getBattery() / agent->getConsumption()) * agent->getSpeed();

        if(range < distToHub + 2) {
          pair<int, int> nearSt = findNearestStation(agent->getX(), agent->getY(), stations);
          /* If not already at this station, move to it. Physics will handle the CHARGING state. */
          if(agent->getX() != nearSt.first || agent->getY() != nearSt.second) {
            agent->setNewDestination(nearSt.first, nearSt.second, map);
            agent->setState(AgentState::MOVING);
          }
        } else {
          /* Enough range to reach home safely */
          agent->setNewDestination(hubX, hubY, map);
          agent->setState(AgentState::MOVING);
        }
      }
    }
  }
};