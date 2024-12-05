# Jeu de la Vie de Conway

Ce projet implémente une version interactive du **Jeu de la Vie** de Conway en C++. Il offre deux modes d'exécution : **graphique** (avec SFML) et **terminal**.

## Fonctionnalités principales

### 1. Mode graphique
- Interface graphique utilisant **SFML**.
- Grille interactive permettant de :
  - Démarrer, pauser ou réinitialiser la simulation.
  - Cliquer sur des cellules pour les activer ou désactiver.
- Affichage en temps réel :
  - Nombre de cellules vivantes.
  - Nombre d'itérations.
- Limitation optionnelle du nombre maximum d'itérations.

### 2. Mode terminal
- Chargement d'une configuration initiale à partir d'un fichier texte.
- Simulation d'un nombre défini de générations.
- Sauvegarde automatique des états de la grille à chaque génération dans des fichiers texte.

### 3. Gestion des fichiers et répertoires
- Création d'un répertoire de sortie pour sauvegarder les états de la grille.
- Sauvegarde de chaque état dans un fichier nommé par numéro de génération.

## Prérequis

### Logiciels
- **C++17 ou plus récent** (recommandé).
- **SFML 2.5+** pour le mode graphique.

### Bibliothèques et fichiers requis
- Fichier de configuration : `arial.ttf` (pour les textes graphiques).
- Fichier d'entrée : fichier texte contenant la configuration initiale (mode terminal).

### Système d'exploitation
- Windows (à l'aide des API Win32 pour la gestion des répertoires).
- Possibilité de portage sur Linux/Mac avec des ajustements.

## Compilation et exécution

### Compilation avec un compilateur supportant SFML

Utilisez `g++` (ou un autre compilateur C++ compatible) avec les options liées à SFML. Exemple avec g++ :

```bash
g++ -o jeu_de_la_vie jeu_de_la_vie.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

### Exécution

#### Mode graphique

Lancez le programme et choisissez `graphique` comme mode.

```bash
./jeu_de_la_vie
```

#### Mode terminal

Préparez un fichier texte d'entrée contenant :
- Les dimensions de la grille (à la première ligne : `lignes colonnes`).
- L'état initial de chaque cellule (0 = morte, 1 = vivante).

Exemple de fichier : `config.txt`
```
5 5
0 1 0 0 0
1 1 1 0 0
0 1 0 0 0
0 0 0 0 0
0 0 0 0 0
```

Exécutez le programme avec le mode terminal et fournissez le nom du fichier :

```bash
./jeu_de_la_vie
```

## Utilisation

### Mode graphique
- Cliquez sur les cellules pour les activer/désactiver avant le démarrage.
- Utilisez les boutons pour démarrer, pauser ou réinitialiser la simulation.

### Mode terminal
- Le programme lit le fichier d'entrée et simule le nombre de générations souhaité.
- Les états successifs sont sauvegardés dans un répertoire de sortie.

## Structure du projet

- `jeu_de_la_vie.cpp` : fichier source principal.
- `arial.ttf` : police requise pour le mode graphique.
- `config.txt` : exemple de fichier d'entrée pour le mode terminal.

## Limitations

- L'API Win32 est utilisée pour la gestion des répertoires (à modifier pour la compatibilité multiplateforme).
- La taille de la grille et des cellules est fixée au démarrage (non ajustable dynamiquement).
- La présence de `arial.ttf` est obligatoire pour le mode graphique.

## Améliorations possibles

1. Portabilité multiplateforme (éliminer la dépendance à Win32).
2. Interface utilisateur améliorée (ajouter des sliders pour ajuster la vitesse, les dimensions de la grille, etc.).
3. Optimisation pour les grandes grilles.

## Auteur
Créé par [groupe 24].
