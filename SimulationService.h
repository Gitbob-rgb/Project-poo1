#ifndef SIMULATIONSERVICE_H  
#define SIMULATIONSERVICE_H  

#include "Grid.h"  
#include <string>  

class SimulationService {
public:
    static void runSimulation(Grid& grid, int maxIterations, const std::string& outputDir, const std::string& baseFilename);
};

#endif // SIMULATIONSERVICE_H
