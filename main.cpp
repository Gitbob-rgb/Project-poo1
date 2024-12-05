#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "SimulationService.h"

int main() {
    int rows = 10, cols = 10, cellSize = 50, maxIterations;
    std::string mode;

    std::cout << "Choisissez le mode (terminal ou graphique) : ";
    std::cin >> mode;

    Grid grid(rows, cols);
    SimulationService service;

    if (mode == "terminal") {
        std::string filename;
        std::cout << "Entrez le nom du fichier d'entrée : ";
        std::cin >> filename;

        grid.initializeFromInput(filename);

        int generations;
        std::cout << "Entrez le nombre de générations à simuler : ";
        std::cin >> generations;

        std::string outputDir = "output";
        service.runSimulation(grid, generations, outputDir, "grid");
    }
    else if (mode == "graphique") {
        sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize), "Jeu de la Vie");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            grid.update();
            window.clear(sf::Color::Black);

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                    cell.setPosition(j * cellSize, i * cellSize);
                    cell.setFillColor(grid.getCellState(i, j) ? sf::Color::White : sf::Color::Black);
                    window.draw(cell);
                }
            }
            window.display();
        }
    }
    else {
        std::cout << "Mode invalide." << std::endl;
    }

    return 0;
}
