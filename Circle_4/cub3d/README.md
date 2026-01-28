# 🎮 cub3D

![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success)
![Grade](https://img.shields.io/badge/Grade-115%2F100-brightgreen)

> Un moteur de rendu 3D inspiré du légendaire jeu **Wolfenstein 3D**, premier FPS de l'histoire.

## 📋 Description

**cub3D** est un projet de l'école 42 qui consiste à créer une vue 3D réaliste à l'intérieur d'un labyrinthe en utilisant le **raycasting**. Le projet utilise la MiniLibX pour afficher les graphiques et gérer les événements.

### Objectifs pédagogiques
- 🔍 Comprendre et implémenter l'algorithme de raycasting
- 🎨 Gérer les textures et les couleurs
- 🖼️ Manipuler des images avec la MiniLibX
- 📐 Travailler avec des mathématiques vectorielles
- 🗺️ Parser et valider des fichiers de configuration

## ✨ Fonctionnalités

### Fonctionnalités obligatoires
- ✅ Rendu 3D d'un labyrinthe en temps réel
- ✅ Textures différentes pour chaque mur (Nord, Sud, Est, Ouest)
- ✅ Couleurs personnalisables pour le sol et le plafond
- ✅ Déplacements fluides (W, A, S, D)
- ✅ Rotation de la caméra avec les flèches directionnelles
- ✅ Gestion propre de la fermeture de fenêtre (ESC et bouton X)

### Fonctionnalités bonus
- 🗺️ **Minimap** dynamique avec position du joueur en temps réel
- 🖱️ **Rotation avec la souris** pour une expérience immersive
- 📏 Minimap adaptative avec bordures

## 🛠️ Installation

### Prérequis
```bash
# Debian/Ubuntu
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Fedora
sudo dnf install gcc make xorg-x11-server-Xorg libXext-devel libbsd-devel
```

### Compilation
```bash
# Cloner le repository
git clone <votre-repo> cub3d
cd cub3d

# Compiler le projet
make

# Compiler avec les bonus
make bonus
```

## 🎮 Utilisation

```bash
./cub3D maps/subject_map.cub
```

### Contrôles
| Touche | Action |
|--------|--------|
| `W` | Avancer |
| `S` | Reculer |
| `A` | Déplacement latéral gauche |
| `D` | Déplacement latéral droite |
| `←` | Rotation gauche |
| `→` | Rotation droite |
| `Souris` | Rotation de la caméra |
| `ESC` | Quitter le jeu |

## 📁 Structure du projet

```
cub3d/
├── include/
│   └── cub3d.h              # Header principal
├── srcs/
│   ├── cub3d.c              # Point d'entrée
│   ├── utils.c              # Fonctions utilitaires
│   ├── free.c               # Gestion de la mémoire
│   ├── exec/                # Moteur de rendu
│   │   ├── draw.c           # Fonctions de dessin
│   │   ├── exec_1.c         # Initialisation
│   │   ├── hook.c           # Gestion des événements
│   │   ├── init_mlx.c       # Initialisation MiniLibX
│   │   ├── minimap_1.c      # Minimap (partie 1)
│   │   ├── minimap_2.c      # Minimap (partie 2)
│   │   ├── move.c           # Déplacements du joueur
│   │   ├── raycasting_1.c   # Algorithme de raycasting
│   │   ├── raycasting_init.c
│   │   ├── raycasting_texture_1.c
│   │   └── raycasting_texture_2.c
│   └── parsing/             # Parsing de la map
│       ├── parsing.c
│       ├── read_map.c
│       ├── check_close.c
│       ├── check.c
│       ├── color.c
│       ├── duplicate.c
│       ├── fill_map.c
│       ├── img.c
│       └── utils.c
├── libft/                   # Bibliothèque personnelle
├── maps/                    # Fichiers de maps
│   └── subject_map.cub
├── textures/                # Textures XPM
│   ├── north.xpm
│   ├── south.xpm
│   ├── east.xpm
│   └── west.xpm
├── Makefile
└── README.md
```

## 🗺️ Format du fichier de map

Les maps doivent avoir l'extension `.cub` et suivre ce format :

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,225,225

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Règles du format
- **Textures** : `NO`, `SO`, `WE`, `EA` suivies du chemin vers les fichiers XPM
- **Couleurs** : `F` (floor/sol) et `C` (ceiling/plafond) en format RGB (0-255)
- **Map** :
  - `0` : Espace vide
  - `1` : Mur
  - `N`, `S`, `E`, `W` : Position et orientation de départ du joueur
  - Espaces : Zone en dehors de la map
- La map doit être entourée de murs (`1`)
- Un seul joueur doit être présent

## 🧮 Algorithme de Raycasting

Le raycasting est la technique utilisée pour créer une illusion de 3D :

1. **Pour chaque colonne de pixels** sur l'écran :
   - Calculer la direction du rayon
   - Avancer le rayon pas à pas dans la grille
   - Détecter le premier mur touché
   - Calculer la distance au mur (distance perpendiculaire)
   - Calculer la hauteur du mur à afficher
   - Récupérer la texture appropriée
   - Dessiner la colonne texturée

## 🎨 Gestion des textures

Les textures sont chargées depuis des fichiers XPM (128x128 pixels) et appliquées selon :
- La direction du mur (Nord, Sud, Est, Ouest)
- La position exacte de l'impact du rayon sur le mur

## 📊 Architecture du code

### Structures principales

```c
t_exec      // Structure principale du moteur
t_player    // Position et direction du joueur
t_ray       // Informations sur chaque rayon
t_assets    // Ressources (textures, map, couleurs)
t_texture_mlx // Données des textures
```

### Modules

- **Parsing** : Validation et lecture du fichier de configuration
- **Execution** : Boucle principale et rendu
- **Raycasting** : Calcul des distances et projections
- **Textures** : Chargement et application des textures
- **Minimap** : Affichage de la carte en temps réel

## 🐛 Gestion des erreurs

Le programme gère et affiche des messages d'erreur explicites pour :
- ❌ Fichier de map invalide ou manquant
- ❌ Extensions incorrectes
- ❌ Map non fermée ou mal formatée
- ❌ Textures manquantes ou inaccessibles
- ❌ Couleurs invalides
- ❌ Plusieurs joueurs ou aucun joueur
- ❌ Caractères invalides dans la map
- ❌ Erreurs d'allocation mémoire

## 🧹 Nettoyage

```bash
make clean   # Supprime les fichiers objets
make fclean  # Supprime tout (objets + exécutable)
make re      # Recompile entièrement
```

## 📚 Normes et bonnes pratiques

- ✅ Code conforme à la **Norme 42**
- ✅ Pas de fuites mémoire (vérifié avec Valgrind)
- ✅ Gestion propre des erreurs
- ✅ Code modulaire et commenté
- ✅ Protection contre les segfaults

## 🔍 Tests

Pour tester le projet avec différentes maps :
```bash
# Map du sujet
./cub3D maps/subject_map.cub

# Créer vos propres maps
./cub3D maps/custom_map.cub
```

## 🤝 Auteurs

- **vnieto-j** - Développement principal de l'execution
- **oztozdem** - Développement principal du parsing

## 📖 Ressources utiles

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d)

## 📝 Licence

Ce projet est réalisé dans le cadre du cursus de l'école 42.

---

*Projet réalisé en 2025 à 42*
