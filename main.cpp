#include <SFML/Graphics.hpp>  
#include <iostream>  
#include <string>  
#include "Grid.h"  
#include "ModeGraphique.h"  
#include "ModeConsole.h"  

int main() {
    int rows = 5; // Nombre de lignes  
    int cols = 10; // Nombre de colonnes  
    std::string mode;
    std::string filename;

    std::cout << "Choisissez le mode (terminal ou graphique) : ";
    std::cin >> mode;

    if (mode != "terminal" && mode != "graphique") {
        std::cout << "Mode invalide, veuillez redémarrer et choisir 'terminal' ou 'graphique'." << std::endl;
        return 1;
    }

    Grid grid(rows, cols);

    if (mode == "graphique") {
        int cellSize = 50; // Taille de chaque cellule  
        int maxIterations;

        std::cout << "Entrez le nombre d'itérations (0 pour une simulation infinie) : ";
        std::cin >> maxIterations;

        ModeGraphique graphicalMode;
        graphicalMode.run(grid, cellSize, maxIterations);
    }
    else {
        std::cout << "Entrez le nom du fichier d'entrée : ";
        std::cin >> filename;

        try {
            grid.initializeFromInput(filename);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }

        std::cout << "État initial de la grille : " << std::endl;
        grid.print();

        ModeConsole consoleMode;
        consoleMode.run(grid, filename);
    }

    return 0;
}