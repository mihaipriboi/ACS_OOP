#include "src/core/ConfigManager.h"
#include "src/map/Map.h"
#include "src/map/MapConstants.h"
#include "src/map/FileMapLoader.h"
#include "src/map/RandomMapGenerator.h"
#include "src/map/MazeMapGenerator.h"
#include "src/map/ArchipelagoMapGenerator.h"
#include "src/map/CanyonMapGenerator.h"
#include "src/map/RadialMapGenerator.h"
#include "src/map/DistrictMapGenerator.h"
#include "src/map/MapExceptions.h"
#include "src/agents/AgentFactory.h"
#include "src/core/UIHelper.h"
#include "src/logic/SimulationManager.h"
#include "src/logic/PackageManager.h"
#include "src/strategies/IDispatchStrategy.h"
#include "src/strategies/GreedyStrategy.h"
#include "src/strategies/NoDeathStrategy.h"
#include "src/strategies/ChargingStrategy.h"
#include "src/strategies/AdvancedHiveStrategy.h"

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
      /* Ask what kind of validation to perform */
      char valChoice;
      do {
        printf("\nSelect validation method:\n");
        printf("1. Standard Validation (Ground agents must reach targets)\n");
        printf("2. Drone Validation (Aerial range connectivity)\n");
        printf("Enter choice (1-2, default 1): ");
        valChoice = getchar();
        if(valChoice == '\n') { valChoice = '1'; break; }
        while(getchar() != '\n'); // Clear buffer
      } while (valChoice != '1' && valChoice != '2');

      Map::setValidationType(valChoice == '1' ? ValidationType::STANDARD : ValidationType::DRONE);

      /* Ask user for map generation method */
      char choice;
      do {
        printf("\nProcedural generate random map? (Y/n): ");
        choice = getchar();
        if(choice == '\n') { choice = 'y'; break; }
        while(getchar() != '\n');
        choice = tolower(choice);
      } while (choice != 'y' && choice != 'n');

      if(choice == 'y' || choice == 'Y') {
        /* Ask user for procedural generation method */
        char methodChoice;
        do {
          printf("\nSelect procedural generation method:\n");
          printf("1. Random Generation\n");
          printf("2. Maze-like Generation\n");
          printf("3. Archipelago Generation\n");
          printf("4. Canyon Generation\n");
          printf("5. Radial Generation\n");
          printf("6. District Generation\n");
          printf("Enter choice (1-6, default 1): ");
          methodChoice = getchar();
          if(methodChoice == '\n') { methodChoice = '1'; break; }
          while(getchar() != '\n');
        } while (methodChoice < '1' || methodChoice > '6');

        switch(methodChoice) {
          case '2': generator = new MazeMapGenerator(); break;
          case '3': generator = new ArchipelagoMapGenerator(); break;
          case '4': generator = new CanyonMapGenerator(); break;
          case '5': generator = new RadialMapGenerator(); break;
          case '6': generator = new DistrictMapGenerator(); break;
          default: generator = new RandomMapGenerator(); break;
        }
      } else {
        char fileName[100];
        printf("Enter map filename: ");
        scanf("%s", fileName);
        while(getchar() != '\n');
        generator = new FileMapLoader(fileName);
      }

      gameMap = generator->generate();

      if(!gameMap->validate()) {
        throw MapValidationException("One or more locations are unreachable from the Hub.");
      }

      printf("[Map loaded and validated successfully!]\n\n");
      gameMap->display();
      gameMap->saveToFile("output/debug_map.txt");
      
      delete generator;
      break; /* Success! Exit loop */

    } catch (const MapException& e) {
      fprintf(stderr, "\a\033[1;31m[MAP ERROR]: %s\033[0m\n", e.what());
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
  for(int i = 0; i < config->getScootersCount(); i++) 
    fleet.push_back(AgentFactory::createAgent(AgentType::SCOOTER, idCounter++, hubX, hubY));
  for(int i = 0; i < config->getRobotsCount(); i++) 
    fleet.push_back(AgentFactory::createAgent(AgentType::ROBOT, idCounter++, hubX, hubY));

  printf("\n[Fleet initialized with %zu agents at Hub (%d, %d)]\n", fleet.size(), hubX, hubY);
  
  /* Package Manager Initialization */

  PackageManager pkgManager;
  pkgManager.discoverClients(*gameMap);

  SimulationManager sim(gameMap, fleet, pkgManager, false);

  /* Ask user for delivery strategy */
  char strategyChoice;
  do {
    printf("\nSelect the displayed delivery strategy (the others will run in the background):\n");
    printf("1. Greedy\n");
    printf("2. No Deaths\n");
    printf("3. Station Aware\n");
    printf("4. Advanced Hive\n");
    printf("Enter choice (1-4, default 4): ");
    strategyChoice = getchar();
    if(strategyChoice == '\n') { strategyChoice = '4'; break; }
    while(getchar() != '\n');
  } while (strategyChoice < '1' || strategyChoice > '4');

  switch(strategyChoice) {
    case '1': sim.setStrategy(new GreedyStrategy()); break;
    case '2': sim.setStrategy(new NoDeathStrategy()); break;
    case '3': sim.setStrategy(new ChargingStrategy()); break;
    default: sim.setStrategy(new AdvancedHiveStrategy()); break;
  }

  /* Array that holds all simulation strategies */
  vector<IDispatchStrategy*> strategies;
  strategies.push_back(new GreedyStrategy());
  strategies.push_back(new NoDeathStrategy());
  strategies.push_back(new ChargingStrategy());
  strategies.push_back(new AdvancedHiveStrategy());

  vector<string> strategyNames = {
    "Greedy", 
    "No Deaths",
    "Station Aware",
    "Advanced Hive"
  };

  /* Array of Simulation Managers for each strategy */
  vector<SimulationManager*> simulations;

  /* Array of Package Managers for each simulation */
  vector<PackageManager*> pkgManagers;
  for(size_t i = 0; i < strategies.size(); i++) {
    pkgManagers.push_back(new PackageManager());
    pkgManagers.back()->discoverClients(*gameMap);
  }

  /* Array of agents for each simulation */
  vector<vector<unique_ptr<Agent>>> agentPools;
  for(size_t i = 0; i < strategies.size(); i++) {
    agentPools.push_back(vector<unique_ptr<Agent>>());
    int idCounter = 0;
    for(int j = 0; j < config->getDronesCount(); j++) 
      agentPools[i].push_back(AgentFactory::createAgent(AgentType::DRONE, idCounter++, hubX, hubY));
    for(int j = 0; j < config->getScootersCount(); j++) 
      agentPools[i].push_back(AgentFactory::createAgent(AgentType::SCOOTER, idCounter++, hubX, hubY));
    for(int j = 0; j < config->getRobotsCount(); j++) 
      agentPools[i].push_back(AgentFactory::createAgent(AgentType::ROBOT, idCounter++, hubX, hubY));
  }

  for(size_t i = 0; i < strategies.size(); i++) {
    simulations.push_back(new SimulationManager(gameMap, agentPools[i], *pkgManagers[i], true));
    simulations.back()->setStrategy(strategies[i]);
  }

  printf("\nPress [ENTER] to start the HiveMind simulation...");

  getchar();

  /* Main Simulation Loop */
  while(!sim.isFinished()) {
    sim.runSingleTick();
  }

  sim.calculateFinalScore();
  sim.renderUI();
  printf("\n");
  UIHelper::printHeader("Simulation Terminated");
  printf("\n");

  printf("[Headless simulations running... Please wait.]\n");

  /* Run the headless simulations */
  for(auto& simulation : simulations) {
    while(!simulation->isFinished()) {
      simulation->runSingleTick();
    }
    simulation->calculateFinalScore();
  }

  /* Display results of all strategies */
  // table with name of strategy, costs, penalties, profits, final score, packages delivered, late deliveries
  const char* RED = "\033[1;31m";
  const char* YEL = "\033[1;33m";
  const char* GRN = "\033[1;32m";
  const char* RST = "\033[0m";

  UIHelper::printHeader("Strategy Comparison");
  
  // Header with fixed widths
  printf(" %-22s | %-12s | %-10s | %-10s | %-10s | %-9s | %-10s\n", 
         "Strategy", "Final Score", "Costs", "Penalties", "Profits", "Delivered", "Late");
  printf("------------------------|--------------|------------|------------|------------|-----------|--------\n");

  for(size_t i = 0; i < simulations.size(); i++) {
    int score = simulations[i]->getFinalScore();
    const char* scoreCol = (score > 0) ? GRN : (score < 0 ? RED : RST);
    
    printf(" %-22s | %s%-12d%s | %s%-10d%s | %s%-10d%s | %s%-10d%s | %-9d | %s%-10d%s\n", 
      strategyNames[i].c_str(),
      scoreCol, score, RST,
      YEL, simulations[i]->getCosts(), RST,
      RED, simulations[i]->getPenalties(), RST,
      GRN, simulations[i]->getProfits(), RST,
      simulations[i]->getPackagesDelivered(),
      RED, simulations[i]->getPackagesDeliveredLate(), RST
    );
  }

  /* Output final statistics for each strategy to file */
  FILE* statsFile = fopen("output/strategy_comparison.txt", "w");
  if(statsFile) {
    fprintf(statsFile, "Strategy Comparison\n");
    fprintf(statsFile, "Strategy               | Final Score | Penalties | Profits   | Costs     | Delivered | Late      \n");
    fprintf(statsFile, "-----------------------|-------------|-----------|-----------|-----------|-----------|-----------\n");
    for(size_t i = 0; i < simulations.size(); i++) {
      fprintf(statsFile, "%-22s | %-11d | %-9d | %-9d | %-9d | %-9d | %-9d\n", 
        strategyNames[i].c_str(),
        simulations[i]->getFinalScore(),
        simulations[i]->getPenalties(),
        simulations[i]->getProfits(),
        simulations[i]->getCosts(),
        simulations[i]->getPackagesDelivered(),
        simulations[i]->getPackagesDeliveredLate()
      );
    }

    fprintf(statsFile, "\nSimulated Map\n");
    gameMap->saveToFile(statsFile);

    fprintf(statsFile, "\nFleet Composition\n");
    fprintf(statsFile, "Agent Type | Count\n");
    fprintf(statsFile, "-----------|------\n");
    fprintf(statsFile, "Drones     | %d\n", config->getDronesCount());
    fprintf(statsFile, "Scooters   | %d\n", config->getScootersCount());
    fprintf(statsFile, "Robots     | %d\n", config->getRobotsCount());

    fprintf(statsFile, "\nSimulation Parameters\n");
    fprintf(statsFile, "Max Ticks: %d\n", config->getMaxTicks());
    fprintf(statsFile, "Total Packages: %d\n", config->getTotalPackages());
    fprintf(statsFile, "Package Spawn Frequency: %d ticks\n", config->getSpawnFrequency());

    fclose(statsFile);
    printf("\n[Strategy comparison saved to output/strategy_comparison.txt]\n");
  } else {
    fprintf(stderr, "\a\033[1;31m[ERROR]: Could not write strategy comparison to file.\033[0m\n");
  }
  
  return 0;
}