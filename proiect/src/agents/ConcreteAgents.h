#pragma once

#include "Agent.h"
#include "../pathfinding/AStarAlgorithm.h"
#include "../pathfinding/LinearPathAlgorithm.h"

#include <memory>

/* * Drones: High speed (3), ignores walls.
 * High maintenance cost and consumption.
 */
class Drone : public Agent {
public:
  Drone(int id, int x, int y) 
    : Agent(id, AgentType::DRONE, x, y, make_unique<LinearPathAlgorithm>()) {
    speed = 3;
    battery = 100;
    maxBattery = 100;
    consumption = 10;
    costPerTick = 15;
    capacity = 1;
  }
  
  char getSymbol() const override { 
    return AGENT_CHARS[(int)AgentType::DRONE]; 
  }
  
  bool canPassWalls() const override { 
    return true;
  }
};

 /* * Robots: Slow (1).
 * Low maintenance, high capacity.
 */
class Robot : public Agent {
public:
  Robot(int id, int x, int y) 
    : Agent(id, AgentType::ROBOT, x, y, make_unique<AStarAlgorithm>()) {
    speed = 1;
    battery = 300;
    maxBattery = 300;
    consumption = 2;
    costPerTick = 1;
    capacity = 4;
  }
  
  char getSymbol() const override { 
    return AGENT_CHARS[(int)AgentType::ROBOT]; 
  }
  
  bool canPassWalls() const override { 
    return false;
  }
};

 /* * Scooters: Moderate speed (2).
 * Balanced stats.
 */
class Scooter : public Agent {
public:
  Scooter(int id, int x, int y) 
    : Agent(id, AgentType::SCOOTER, x, y, make_unique<AStarAlgorithm>()) {
    speed = 2;
    battery = 200;
    maxBattery = 200;
    consumption = 5;
    costPerTick = 4;
    capacity = 2;
  }
  
  char getSymbol() const override { 
    return AGENT_CHARS[(int)AgentType::SCOOTER]; 
  }
  
  bool canPassWalls() const override { 
    return false;
  }
};