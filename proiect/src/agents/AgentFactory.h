#pragma once

#include "ConcreteAgents.h"

#include <memory>

class AgentFactory {
public:
  /* Centralized creation using AgentType enum for safety */
  static unique_ptr<Agent> createAgent(AgentType type, int id, int x, int y) {
    switch(type) {
      case AgentType::DRONE:
        return make_unique<Drone>(id, x, y);
      case AgentType::ROBOT:
        return make_unique<Robot>(id, x, y);
      case AgentType::SCOOTER:
        return make_unique<Scooter>(id, x, y);
      default:
        return nullptr;
    }
  }
};