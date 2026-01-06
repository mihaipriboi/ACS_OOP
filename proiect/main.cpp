#include "src/core/ConfigManager.h"
#include "src/map/Map.h"
#include "src/map/FileMapLoader.h"
#include "src/map/ProceduralGenerator.h"
#include "src/map/MapExceptions.h"
#include "src/agents/AgentFactory.h"
#include "src/logic/SimulationManager.h"
#include "src/core/UIHelper.h"

#include <memory>
#include <vector>

int main() {
  /* Set console to UTF-8 for Windows compatibility */
  #ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  #endif

  /* Load configuration */
  ConfigManager* config = ConfigManager::getInstance();

  /* Parse simulation_setup.txt and print data */
  if(!config->loadConfig("simulation_setup.txt")) {
    fprintf(stderr, "Error: Could not open simulation_setup.txt\n");
    return 1;
  }

  config->printSettings();
  printf("[Parameters successfully loaded!]\n");

  /* Create map generator */
  Map* gameMap = nullptr;

  while(true) {
    IMapGenerator* generator = nullptr;
    try {
      printf("Procedural generate random map? (Y/n): ");
      char choice = getchar();
      if(choice == '\n') choice = 'y';
      else while(getchar() != '\n');

      if(choice == 'y' || choice == 'Y') {
        generator = new ProceduralGenerator();
      } else {
        char fileName[100];
        printf("Enter map filename: ");
        scanf("%s", fileName);
        while(getchar() != '\n');
        generator = new FileMapLoader(fileName);
      }

      gameMap = generator->generate();

      /* For FileMapLoader, we still need to validate reachability */
      if(!gameMap->validate()) {
        throw MapValidationException("One or more locations are unreachable from the Hub.");
      }

      printf("[Map loaded and validated successfully!]\n\n");
      gameMap->display();
      gameMap->saveToFile("output/debug_map.txt");
      
      delete generator;
      break; /* Success! Exit loop */

    } catch (const MapException& e) {
      fprintf(stderr, "\a[MAP ERROR]: %s\n", e.what());
      if(gameMap) { delete gameMap; gameMap = nullptr; }
      if(generator) delete generator;
      printf("Please try again.\n\n");
    }
  }

  /* Fleet Initialization */
  int hubX = gameMap->getHubX();
  int hubY = gameMap->getHubY();

  vector<unique_ptr<Agent>> fleet;
  int idCounter = 0;

  /* Create the fleet defined in simulation_setup.txt*/
  for(int i = 0; i < config->getDronesCount(); i++) 
    fleet.push_back(AgentFactory::createAgent(AgentType::DRONE, idCounter++, hubX, hubY));
  for(int i = 0; i < config->getRobotsCount(); i++) 
    fleet.push_back(AgentFactory::createAgent(AgentType::ROBOT, idCounter++, hubX, hubY));
  for(int i = 0; i < config->getScootersCount(); i++) 
    fleet.push_back(AgentFactory::createAgent(AgentType::SCOOTER, idCounter++, hubX, hubY));

  printf("\n[Fleet initialized with %zu agents at Hub (%d, %d)]\n", fleet.size(), hubX, hubY);
  
  /* Package Manager Initialization */

  PackageManager pkgManager;
  pkgManager.discoverClients(*gameMap);

  SimulationManager sim(gameMap, fleet, pkgManager);

  printf("\nPress [ENTER] to start the HiveMind simulation...");
  getchar();

  /* Main Simulation Loop */
  while(!sim.isFinished()) {
    sim.runSingleTick();
  }

  /* Clear one last time for the final report */
  printf("\033[H\033[J");
  UIHelper::printHeader("Final Simulation Report");
  
  /* Statistics to be calculated based on agent and package results */
  printf("Total Cost: ...\n");
  printf("Total Revenue: ...\n");
  printf("Drones Lost: ...\n");
  printf("Delivery Success Rate: ...\n");
  
  UIHelper::printHeader("Simulation Terminated");
  
  return 0;
}