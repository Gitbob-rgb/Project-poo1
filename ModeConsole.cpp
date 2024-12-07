#include "ModeConsole.h"  
#include <iostream>  
#include <windows.h>  // Pour Windows  
#include <errno.h>    // Pour obtenir les erreurs 
#include <cstring>
#include <cstdlib>
using namespace std;
bool directoryExists(const string& path) {
    DWORD ftyp = GetFileAttributesA(path.c_str());
    return (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY));
}

// Function to create a directory using Win32 API  
bool createDirectory(const string& path) {
    return CreateDirectoryA(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
}

void ModeConsole::run(Grid& grid, const std::string& inputFilename) {
    int generations;
    std::cout << u8"Entrez le nombre de générations à simuler : ";
    std::cin >> generations;

    std::string outputDir = inputFilename + "_out";
    string a = "rmdir /s /q " + outputDir;
    system(a.c_str());
    // Vérifiez si le répertoire existe  
    if (!directoryExists(outputDir)) {
        if (createDirectory(outputDir)) {
            std::cout << u8"Le répertoire de sortie a été créé : " << outputDir << std::endl;
        }
        else {
            std::cerr << u8"Erreur : Impossible de créer le répertoire de sortie." << std::endl;
            return; // Sortir si la création du répertoire échoue  
        }
    }
    else {
        std::cout << u8"Le répertoire de sortie existe déjà : " << outputDir << std::endl;
    }

    for (int generation = 0; generation < generations; ++generation) {
        grid.update();
        std::cout << u8"État de la grille à la génération " << generation + 1 << " : " << std::endl;
        grid.print();

        // Sauvegarder chaque génération  
        grid.saveToFile(outputDir, inputFilename, generation + 1);
    }
}