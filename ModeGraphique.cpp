#include "ModeGraphique.h"  
#include <iostream>  
#include <thread>  
#include <chrono>  

void ModeGraphique::run(Grid& grid, int cellSize, int maxIterations) {
    sf::RenderWindow window(sf::VideoMode(grid.getCols() * cellSize, grid.getRows() * cellSize + 50), "Jeu de la Vie");
    sf::Font font;
    if (!font.loadFromFile("MinecraftStandard.otf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return;
    }

    StartButton startButton(10, grid.getRows() * cellSize + 10, 450, 30, font);
    bool simulationRunning = false;
    int iterationsCount = 0;
    bool isClickEnabled = true; // Nouvelle variable pour g�rer l'�tat des clics  

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // V�rifiez si le bouton de d�marrage a �t� cliqu�  
                    if (startButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                        if (!startButton.getIsDisabled()) {
                            if (simulationRunning) {
                                startButton.pauseSimulation(); // Met en pause la simulation  
                                simulationRunning = false; // Change l'�tat de la simulation  
                            }
                            else {
                                startButton.startSimulation(); // D�marre la simulation  
                                simulationRunning = true; // Change l'�tat de la simulation  
                                iterationsCount = 0; // R�initialiser le compteur des it�rations  
                            }
                        }
                    }

                    // D�sactiver l'action de clic si les clics ne sont pas autoris�s  
                    if (isClickEnabled) {
                        // Autoriser le clic sur la grille pour basculer les cellules seulement si la simulation n'a pas atteint le maximum d'it�rations  
                        if (!simulationRunning || (maxIterations > 0 && iterationsCount < maxIterations)) {
                            grid.toggleCell(event.mouseButton.x, event.mouseButton.y, cellSize);
                        }
                    }
                }
            }
        }

        // V�rifiez si la simulation est en cours  
        if (simulationRunning) {
            grid.update(); // Met � jour l'�tat des cellules  
            iterationsCount++; // Incr�mente le compteur des it�rations  
            if (maxIterations > 0 && iterationsCount >= maxIterations) {
                startButton.disableButton(); // D�sactive le bouton de d�marrage  
                simulationRunning = false; // Arr�te la simulation  
                isClickEnabled = false; // D�sactive tous les clics  
            }
        }

        window.clear(sf::Color::Black); // Efface la fen�tre  
        grid.draw(window, cellSize); // Dessine la grille  
        startButton.draw(window); // Dessine le bouton de d�marrage  
        window.display(); // Affiche tout  

        if (simulationRunning) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause de 100 ms entre les mises � jour  
        }
    }
}