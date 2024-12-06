#ifndef MODEGRAPHIQUE_H  
#define MODEGRAPHIQUE_H  

#include <SFML/Graphics.hpp>  
#include "Grid.h"  
#include "StartButton.h"  

class ModeGraphique {
public:
    void run(Grid& grid, int cellSize, int maxIterations);
};

#endif // MODEGRAPHIQUE_H