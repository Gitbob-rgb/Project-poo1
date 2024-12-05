#include "SimulationService.h"
#include <iostream>
#include <stdexcept>

bool SimulationService::directoryExists(const std::string& path) {
    DWORD fileAttr = GetFileAttributesA(path.c_str());
    return (fileAttr != INVALID_FILE_ATTRIBUTES && (fileAttr & FILE_ATTRIBUTE_DIRECTORY));
}

bool SimulationService::createDirectory(const std::string& path) {
    return CreateDirectoryA(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
}

void SimulationService::runSimulation(Grid& grid, int generations, const std::string& outputDir, const std::string& baseFilename) {
    if (!directoryExists(outputDir) && !createDirectory(outputDir)) {
        throw std::runtime_error("Could not create output directory: " + outputDir);
    }
    for (int generation = 0; generation < generations; ++generation) {
        grid.update();
        grid.saveToFile(outputDir, baseFilename, generation + 1);
    }
}
