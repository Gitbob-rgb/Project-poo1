#include "Grid.h"

Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, std::vector<bool>(cols, false));
}

int Grid::countLivingNeighbors(int x, int y) {
    int livingNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                if (cells[newX][newY]) {
                    livingNeighbors++;
                }
            }
        }
    }
    return livingNeighbors;
}

void Grid::initializeFromInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Could not open file.");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int state;
            file >> state;
            cells[i][j] = (state == 1);
        }
    }
    file.close();
}

void Grid::update() {
    std::vector<std::vector<bool>> newCells = cells;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int livingNeighbors = countLivingNeighbors(i, j);
            if (cells[i][j]) {
                newCells[i][j] = !(livingNeighbors < 2 || livingNeighbors > 3);
            }
            else {
                newCells[i][j] = (livingNeighbors == 3);
            }
        }
    }
    cells = newCells;
}

void Grid::toggleCell(int mouseX, int mouseY, int cellSize) {
    int col = mouseX / cellSize;
    int row = mouseY / cellSize;
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        cells[row][col] = !cells[row][col];
    }
}

void Grid::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << (cells[i][j] ? "1 " : "0 ");
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

void Grid::saveToFile(const std::string& directory, const std::string& baseFilename, int generation) const {
    std::ofstream outFile(directory + "\\" + baseFilename + "_gen_" + std::to_string(generation) + ".txt");
    if (!outFile) throw std::runtime_error("Could not open output file.");
    for (const auto& row : cells) {
        for (bool cell : row) {
            outFile << (cell ? "1 " : "0 ");
        }
        outFile << std::endl;
    }
    outFile.close();
}
