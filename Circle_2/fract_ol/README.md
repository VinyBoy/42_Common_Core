# Fract'ol

![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)

## 📝 Description

**Fract'ol** est un projet de l'école 42 qui consiste à créer un visualiseur de fractales graphiques en utilisant la MiniLibX. Ce projet permet de découvrir et d'explorer différents ensembles fractals célèbres à travers une interface graphique interactive.

## 🎯 Objectifs du projet

- Découvrir la programmation graphique avec la MiniLibX
- Comprendre et implémenter des algorithmes mathématiques complexes
- Gérer les événements clavier et souris
- Optimiser le rendu graphique

## ✨ Fractales disponibles

Le programme supporte trois types de fractales :

1. **Mandelbrot** - L'ensemble de Mandelbrot classique
2. **Julia** - L'ensemble de Julia avec paramètres configurables
3. **Ship** - Le Burning Ship fractal

## 🛠️ Compilation

### Prérequis

- `gcc` ou `cc`
- `make`
- La MiniLibX (incluse dans `mlx_linux/`)
- Les bibliothèques X11 : `libX11`, `libXext`

### Installation

```bash
# Cloner le dépôt
git clone [votre-repo] fract_ol
cd fract_ol

# Compiler le projet
make

# Nettoyer les fichiers objets
make clean

# Nettoyer complètement
make fclean

# Recompiler
make re
```

## 🚀 Utilisation

```bash
./fractol <nom_de_la_fractale>
```

### Exemples

```bash
./fractol Mandelbrot
./fractol Julia
./fractol Ship
```

## 🎮 Contrôles

### Clavier

| Touche | Action |
|--------|--------|
| `ESC` | Quitter le programme |
| `←` `→` `↑` `↓` | Se déplacer dans la fractale |
| `R` | Réinitialiser la vue |
| `C` | Changer la palette de couleurs |
| `J` | Générer un nouveau set de Julia (mode Julia uniquement) |

### Souris

| Action | Effet |
|--------|-------|
| `Molette haut` | Zoom avant |
| `Molette bas` | Zoom arrière |
| `✕` (fermer la fenêtre) | Quitter le programme |

## 📊 Fonctionnalités

- ✅ Rendu en temps réel des fractales
- ✅ Zoom infini avec la molette de la souris
- ✅ Navigation fluide avec les flèches directionnelles
- ✅ Changement dynamique des couleurs
- ✅ Julia sets aléatoires
- ✅ Gestion propre de la mémoire
- ✅ Interface responsive

## 📁 Structure du projet

```
fract_ol/
├── Makefile
├── README.md
├── include/
│   └── fractol.h
├── libft/
│   └── Libft/
├── mlx_linux/
└── src/
    ├── burning_ship.c
    ├── init.c
    ├── julia.c
    ├── main.c
    ├── mandelbrot.c
    ├── mlx_hook.c
    └── utils.c
```

## 🔬 Détails techniques

### Algorithme de rendu

Le programme utilise l'**algorithme d'échappement** pour déterminer si un point appartient à l'ensemble fractal :

- Pour chaque pixel de l'écran, on calcule le nombre d'itérations nécessaires avant que la valeur ne diverge
- Si le point ne diverge pas après un nombre maximal d'itérations (300 par défaut), il appartient à l'ensemble
- La couleur du pixel est déterminée par le nombre d'itérations

### Paramètres par défaut

- Taille de la fenêtre : `1000 x 1000` pixels
- Itérations maximales : `300`
- Zoom initial : `200`
- Couleur de base : `0xFCBE11` (jaune/or)

## 👤 Auteur

**vnieto-j** - Étudiant à 42

---

## 📚 Ressources

- [Mandelbrot set - Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set)
- [Julia set - Wikipedia](https://en.wikipedia.org/wiki/Julia_set)
- [Burning Ship fractal - Wikipedia](https://en.wikipedia.org/wiki/Burning_Ship_fractal)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## 📄 Licence

Ce projet est réalisé dans le cadre du cursus de l'école 42.
