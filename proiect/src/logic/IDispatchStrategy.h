#pragma once

#include "../agents/Agent.h"
#include "PackageManager.h"
#include "../map/Map.h"

#include <vector>

using namespace std;

class IDispatchStrategy {
public:
  virtual ~IDispatchStrategy() {}
  
  virtual void execute(vector<unique_ptr<Agent>>& fleet, PackageManager& pkgManager, const Map& map) = 0;
};