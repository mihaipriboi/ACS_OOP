#pragma once

#include "../map/MapConstants.h"
#include "AgentConstants.h"

#include <string>

using namespace std;

class Agent {
protected:
  int id;
  AgentType type;
  int posX, posY;
  int speed;
  int battery;
  int maxBattery;
  int consumption;
  int costPerTick;
  int capacity;
  AgentState state;

public:
  Agent(int id, AgentType t, int x, int y) 
    : id(id), type(t), posX(x), posY(y), state(AgentState::IDLE) {}
  
  virtual ~Agent() {}

  int getId() const { return id; }
  int getSpeed() const { return speed; }
  int getBattery() const { return battery; }
  int getMaxBattery() const { return maxBattery; }
  int getConsumption() const { return consumption; }
  int getCostPerTick() const { return costPerTick; }
  int getCapacity() const { return capacity; }

  virtual char getSymbol() const = 0;
  virtual bool canPassWalls() const = 0;
  
  AgentType getType() const { return type; }
  int getX() const { return posX; }
  int getY() const { return posY; }
  AgentState getState() const { return state; }
};