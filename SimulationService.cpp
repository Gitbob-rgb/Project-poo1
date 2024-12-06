#include "SimulationService.h"  
#include <iostream>  
#include <thread>  
#include <chrono>  

void SimulationService::runSimulation(Grid& grid, int maxIterations, const std::string& outputDir, const std::string& baseFilename) {
    int iterationsCount = 0;

    for (int generation = 0; (maxIterations == 0 || iterationsCount < maxIterations); ++generation) {
        grid.update();
        std::cout << "État de la grille à la génération " << generation + 1 << " : " << std::endl;
        grid.print();

        // Save each generation  
        grid.saveToFile(outputDir, baseFilename, generation + 1);
        iterationsCount++;

        // Sleep for a while to simulate time passing, adjust as needed  
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}