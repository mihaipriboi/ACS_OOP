#pragma once

#include "Agent.h"
#include "../pathfinding/AStarAlgorithm.h"
#include "../pathfinding/LinearPathAlgorithm.h"

#include <memory>

/* * Drones: High speed (3), ignores walls[cite: 38].
 * High maintenance cost and consumption[cite: 38].
 */
class Drone : public Agent {
public:
  Drone(int id, int x, int y) 
    : Agent(id, AgentType::DRONE, x, y, make_unique<LinearPathAlgorithm>()) {
    speed = 3;             /* 3 cells per tick [cite: 38] */
    battery = 100;         /* 100 max battery [cite: 38] */
    maxBattery = 100;      /* [cite: 38] */
    consumption = 10;      /* 10 bat/tick [cite: 38] */
    costPerTick = 15;      /* 15 $/tick [cite: 38] */
    capacity = 1;          /* 1 package [cite: 38] */
  }
  
  char getSymbol() const override { 
    return AGENT_CHARS[(int)AgentType::DRONE]; 
  }
  
  bool canPassWalls() const override { 
    return true;
  }
};

 /* * Robots: Slow (1)[cite: 38].
 * Low maintenance, high capacity[cite: 38].
 */
class Robot : public Agent {
public:
  Robot(int id, int x, int y) 
    : Agent(id, AgentType::ROBOT, x, y, make_unique<AStarAlgorithm>()) {
    speed = 1;             /* 1 cell per tick [cite: 38] */
    battery = 300;         /* 300 max battery [cite: 38] */
    maxBattery = 300;      /* [cite: 38] */
    consumption = 2;       /* 2 bat/tick [cite: 38] */
    costPerTick = 1;       /* 1 $/tick [cite: 38] */
    capacity = 4;          /* 4 packages [cite: 38] */
  }
  
  char getSymbol() const override { 
    return AGENT_CHARS[(int)AgentType::ROBOT]; 
  }
  
  bool canPassWalls() const override { 
    return false;
  }
};

 /* * Scooters: Moderate speed (2)[cite: 38].
 * Balanced stats[cite: 38].
 */
class Scooter : public Agent {
public:
  Scooter(int id, int x, int y) 
    : Agent(id, AgentType::SCOOTER, x, y, make_unique<AStarAlgorithm>()) {
    speed = 2;             /* 2 cells per tick [cite: 38] */
    battery = 200;         /* 200 max battery [cite: 38] */
    maxBattery = 200;      /* [cite: 38] */
    consumption = 5;       /* 5 bat/tick [cite: 38] */
    costPerTick = 4;       /* 4 $/tick [cite: 38] */
    capacity = 2;          /* 2 packages [cite: 38] */
  }
  
  char getSymbol() const override { 
    return AGENT_CHARS[(int)AgentType::SCOOTER]; 
  }
  
  bool canPassWalls() const override { 
    return false;
  }
};