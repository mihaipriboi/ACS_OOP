#pragma once

#include "IDispatchStrategy.h"
#include "../map/Map.h"
#include "../agents/Agent.h"

#include <vector>

using namespace std;

/* * GreedyStrategy Strategy:
 * 1. Assigns packages to IDLE agents at the Hub if battery is 100%.
 * 2. Automatically returns agents to the Hub if they have no current path.
 */
class GreedyStrategy : public IDispatchStrategy {
public:
  void execute(vector<unique_ptr<Agent>>& fleet, PackageManager& pkgManager, const Map& map) override {
    int hubX = map.getHubX();
    int hubY = map.getHubY();

    /* Fetch all packages currently waiting at the Hub */
    auto availablePackages = pkgManager.getPackagesAtHub();

    for(auto& agent : fleet) {
      /* Skip agents that are out of the simulation */
      if(agent->getState() == AgentState::DEAD) {
        continue;
      }

      /* Only make decisions if the agent is not currently moving  */
      if(!agent->hasPath()) {
        bool atHub = (agent->getX() == hubX && agent->getY() == hubY);

        if(atHub) {
          /* Charge until 100% before taking a new task  */
          if(agent->getBattery() >= agent->getMaxBattery()) {
            if(!availablePackages.empty() && agent->canLoadMore()) {
              Package* p = availablePackages.back();
              availablePackages.pop_back();

              /* Assign package and set destination to Client (D) */
              pkgManager.markAsInTransit(p->id, agent->getId());
              agent->pickUpPackage(p->id);
              agent->setNewDestination(p->destX, p->destY, map);
              agent->setState(AgentState::MOVING);
            } else {
              /* Wait at hub for new packages */
              agent->setState(AgentState::IDLE);
            }
          } else {
            /* If at hub and not full, charge battery */
            agent->setState(AgentState::CHARGING);
          }
        } else {
          /* Agent is at a Client or elsewhere and idle; send back to Hub */
          agent->setNewDestination(hubX, hubY, map);
          agent->setState(AgentState::MOVING);
        }
      }
    }
  }
};