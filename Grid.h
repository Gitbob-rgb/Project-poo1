#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

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
    void toggleCell(int mouseX, int mouseY, int cellSize);
    void print() const;
    void saveToFile(const std::string& directory, const std::string& baseFilename, int generation) const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    bool getCellState(int row, int col) const { return cells[row][col]; }
};

#endif
