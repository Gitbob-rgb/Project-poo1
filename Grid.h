#ifndef GRID_H  
#define GRID_H  

#include <vector>  
#include <iostream>  
#include <fstream>  
#include <stdexcept>  
#include <string>  
#include <sstream>  
#include <SFML/Graphics.hpp>  

class Grid {
private:
    std::vector<std::vector<bool>> cells;
    int rows;
    int cols;

    int countLivingNeighbors(int x, int y);

public:
    Grid(int r, int c);
    void initializeFromInput(const std::string& filename);
    void update();
    void draw(sf::RenderWindow& window, int cellSize) const;
    void toggleCell(int mouseX, int mouseY, int cellSize);
    void print() const;
    void saveToFile(const std::string& directory, const std::string& baseFilename, int generation) const;

    // Nouvelle méthode pour vérifier si toutes les cellules sont mortes  
    bool areAllCellsDead() const;
    bool validateGrid(int expectedAliveCount);
    int countLivingCells() const; // Déclaration de la nouvelle méthode
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

#endif // GRID_H