#include <SFML/Graphics.hpp>  
#include <iostream>  
#include <string>  
#include "Grid.h"  
#include "ModeGraphique.h"  
#include "ModeConsole.h"  
#include <windows.h>
int main() {
    SetConsoleOutputCP(CP_UTF8);
    int rows = 5; // Nombre de lignes  
    int cols = 10; // Nombre de colonnes  
    std::string mode;
    std::string filename;

    std::cout << "Choisissez le mode (terminal ou graphique) : ";
    std::cin >> mode;

    if (mode != "terminal" && mode != "graphique") {
        std::cout << u8"Mode invalide, veuillez red�marrer et choisir 'terminal' ou 'graphique'." << std::endl;
        return 1;
    }

    Grid grid(rows, cols);

    if (mode == "graphique") {
        int cellSize = 50; // Taille de chaque cellule  
        int maxIterations;

        std::cout << u8"Entrez le nombre d'it�rations (0 pour une simulation infinie) : ";
        std::cin >> maxIterations;

        ModeGraphique graphicalMode;
        graphicalMode.run(grid, cellSize, maxIterations);
    }
    else {
        std::cout << u8"Entrez le nom du fichier d'entr�e : ";
        std::cin >> filename;

        try {
            grid.initializeFromInput(filename);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }

        std::cout << u8"�tat initial de la grille : " << std::endl;
        grid.print();

        ModeConsole consoleMode;
        consoleMode.run(grid, filename);
    }

    return 0;
}