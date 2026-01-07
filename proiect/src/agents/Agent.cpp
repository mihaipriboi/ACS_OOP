#include "Agent.h"
#include "../map/Map.h"

#include <algorithm>

Agent::Agent(int id, AgentType t, int x, int y, unique_ptr<IPathAlgorithm> pf) 
  : id(id), type(t), posX(x), posY(y), state(AgentState::IDLE), pathfinder(move(pf)) {}

Agent::~Agent() {}

void Agent::setNewDestination(int destX, int destY, const Map& map) {
  if(!pathfinder) return;
  vector<pair<int, int>> path = pathfinder->calculatePath(posX, posY, destX, destY, map);
  setPath(path);
}

void Agent::moveTick() {
  if(state == AgentState::DEAD || currentPath.empty()) return;

  for(int i = 0; i < speed; i++) {
    if(currentPath.empty()) break;

    pair<int, int> nextPos = currentPath.front();
    currentPath.pop_front();

    setPosition(nextPos.first, nextPos.second);

    setState(AgentState::MOVING);
  }
}

void Agent::updateTickConsumption() {
  if(state == AgentState::MOVING) {
    battery -= consumption;
    if(battery < 0) {
      battery = 0;
      state = AgentState::DEAD; /* Agent dies if battery depletes */
    }
  }
}

void Agent::chargeTick() {
  /* Charge 25% of max battery per tick */
  battery += (maxBattery / 4);
  if(battery > maxBattery) battery = maxBattery;
}

void Agent::pickUpPackage(int pkgId) {
  if(canLoadMore()) {
    carriedPackageIds.push_back(pkgId);
  }
}

void Agent::dropOffPackage(int pkgId) {
  auto it = find(carriedPackageIds.begin(), carriedPackageIds.end(), pkgId);
  if(it != carriedPackageIds.end()) {
    carriedPackageIds.erase(it);
  }
}

void Agent::setPath(const vector<pair<int, int>>& newPath) {
  currentPath.clear();
  for(const auto& p : newPath) currentPath.push_back(p);
}

pair<int, int> Agent::getNextStep() {
  if(currentPath.empty()) return {posX, posY};
  pair<int, int> next = currentPath.front();
  currentPath.pop_front();
  return next;
}