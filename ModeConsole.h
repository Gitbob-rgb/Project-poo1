#ifndef MODECONSOLE_H  
#define MODECONSOLE_H  

#include "Grid.h"  
#include <string>  

class ModeConsole {
public:
    void run(Grid& grid, const std::string& inputFilename);
};

#endif // MODECONSOLE_H