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
    bool isClickEnabled = true; // Nouvelle variable pour gérer l'état des clics  

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Vérifiez si le bouton de démarrage a été cliqué  
                    if (startButton.isClicked(event.mouseButton.x, event.mouseButton.y)) {
                        if (!startButton.getIsDisabled()) {
                            if (simulationRunning) {
                                startButton.pauseSimulation(); // Met en pause la simulation  
                                simulationRunning = false; // Change l'état de la simulation  
                            }
                            else {
                                startButton.startSimulation(); // Démarre la simulation  
                                simulationRunning = true; // Change l'état de la simulation  
                                iterationsCount = 0; // Réinitialiser le compteur des itérations  
                            }
                        }
                    }

                    // Désactiver l'action de clic si les clics ne sont pas autorisés  
                    if (isClickEnabled) {
                        // Autoriser le clic sur la grille pour basculer les cellules seulement si la simulation n'a pas atteint le maximum d'itérations  
                        if (!simulationRunning || (maxIterations > 0 && iterationsCount < maxIterations)) {
                            grid.toggleCell(event.mouseButton.x, event.mouseButton.y, cellSize);
                        }
                    }
                }
            }
        }

        // Vérifiez si la simulation est en cours  
        if (simulationRunning) {
            grid.update(); // Met à jour l'état des cellules  
            iterationsCount++; // Incrémente le compteur des itérations  
            if (maxIterations > 0 && iterationsCount >= maxIterations) {
                startButton.disableButton(); // Désactive le bouton de démarrage  
                simulationRunning = false; // Arrête la simulation  
                isClickEnabled = false; // Désactive tous les clics  
            }
        }

        window.clear(sf::Color::Black); // Efface la fenêtre  
        grid.draw(window, cellSize); // Dessine la grille  
        startButton.draw(window); // Dessine le bouton de démarrage  
        window.display(); // Affiche tout  

        if (simulationRunning) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause de 100 ms entre les mises à jour  
        }
    }
}