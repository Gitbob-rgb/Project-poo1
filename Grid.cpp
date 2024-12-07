#include "Grid.h"  

Grid::Grid(int r, int c) : rows(r), cols(c) {
    cells.resize(rows, std::vector<bool>(cols, false));
}

int Grid::countLivingNeighbors(int x, int y) {
    int livingNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Ignore la cellule elle-même  

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
    if (!file.is_open()) {
        throw std::runtime_error("ne peut pas ouvrir le fichier");
    }
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
                // Règle de survie  
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    newCells[i][j] = false;
                }
            }
            else {
                // Règle de reproduction  
                if (livingNeighbors == 3) {
                    newCells[i][j] = true;
                }
            }
        }
    }
    cells = newCells;
}

void Grid::draw(sf::RenderWindow& window, int cellSize) const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setFillColor(cells[i][j] ? sf::Color::White : sf::Color::Black);
            window.draw(cell);
        }
    }
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
    std::stringstream ss;
    ss << directory << "/" << baseFilename << "_gen_" << generation << ".txt";

    std::ofstream outFile(ss.str());
    if (!outFile) {
        std::cerr << u8"Erreur : Impossible d'ouvrir le fichier de sortie." << std::endl;
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outFile << (cells[i][j] ? "1 " : "0 ");
        }
        outFile << std::endl;
    }
    outFile.close();
}

// Implémentation de la méthode areAllCellsDead  
bool Grid::areAllCellsDead() const {
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell) { // Si une cellule est vivante  
                return false; // Retourne false si au moins une cellule est vivante  
            }
        }
    }
    return true; // Retourne true si toutes les cellules sont mortes  
}

// Méthode pour compter les cellules vivantes  
int Grid::countLivingCells() const {
    int count = 0;
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            if (cell == 1) { // Cellule vivante  
                count++;
            }
        }
    }
    return count;
}

bool Grid::validateGrid(int expectedAliveCount) {
    return countLivingCells() == expectedAliveCount;
}