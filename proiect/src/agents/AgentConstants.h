#pragma once

#include <string>

using namespace std;

enum class AgentState { 
  IDLE, 
  MOVING, 
  CHARGING, 
  DEAD 
};

enum class AgentType {
  DRONE,
  ROBOT,
  SCOOTER
};

/* Helper to get string names for display */
inline const char* agentTypeToString(AgentType type) {
  switch(type) {
    case AgentType::DRONE:   return "Drone";
    case AgentType::ROBOT:   return "Robot";
    case AgentType::SCOOTER: return "Scooter";
    default:                 return "Unknown";
  }
}

/* Arrays to convert AgentType to terminal symbols */
const char AGENT_CHARS[] = {'a', 'r', 's'};
const string AGENT_CHARS_TERMINAL[] = {"\u25b2", "\u25a0", "\u25bc"}; 
//                                    ▲ (Drone)  ■ (Robot)  ▼ (Scooter)