#ifndef SIMULATION_SERVICE_H
#define SIMULATION_SERVICE_H

#include <string>
#include "Grid.h"
#include <windows.h>

class SimulationService {
public:
    void runSimulation(Grid& grid, int generations, const std::string& outputDir, const std::string& baseFilename);
    bool createDirectory(const std::string& path);
    bool directoryExists(const std::string& path);
};

#endif
