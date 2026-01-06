#pragma once

#include "Agent.h"

/* * Drones: High speed (3), ignores walls.
 * High maintenance cost and consumption.
 */
class Drone : public Agent {
public:
  Drone(int id, int x, int y) : Agent(id, AgentType::DRONE, x, y) {
    speed = 3;             /* 3 cells per tick  */
    battery = 100;         /* 100 max battery  */
    maxBattery = 100;
    consumption = 10;      /* 10 bat/tick  */
    costPerTick = 15;      /* 15 $/tick  */
    capacity = 1;          /* 1 package  */
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
  Robot(int id, int x, int y) : Agent(id, AgentType::ROBOT, x, y) {
    speed = 1;             /* 1 cell per tick  */
    battery = 300;         /* 300 max battery  */
    maxBattery = 300;
    consumption = 2;       /* 2 bat/tick  */
    costPerTick = 1;       /* 1 $/tick  */
    capacity = 4;          /* 4 packages  */
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
  Scooter(int id, int x, int y) : Agent(id, AgentType::SCOOTER, x, y) {
    speed = 2;             /* 2 cells per tick  */
    battery = 200;         /* 200 max battery  */
    maxBattery = 200;
    consumption = 5;       /* 5 bat/tick  */
    costPerTick = 4;       /* 4 $/tick  */
    capacity = 2;          /* 2 packages  */
  }
  
  char getSymbol() const override { 
    return AGENT_CHARS[(int)AgentType::SCOOTER]; 
  }
  
  bool canPassWalls() const override { 
    return false;
  }
};