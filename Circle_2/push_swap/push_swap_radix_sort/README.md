# 📊 Push_swap

![42 School Project](https://img.shields.io/badge/42-Project-00babc?style=flat-square&logo=42)
![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![Algorithm](https://img.shields.io/badge/Algorithm-Radix_Sort-green?style=flat-square)

> Algorithme de tri efficace avec manipulation de deux piles

## 📝 Description

**Push_swap** est un projet algorithmique du cursus de l'école 42. L'objectif est de trier une pile de nombres en utilisant un nombre minimal d'opérations avec l'aide d'une pile auxiliaire.

Ce projet implémente l'**algorithme Radix Sort** pour les grandes listes et un algorithme optimisé pour les petites listes (≤ 5 éléments).

## 🎯 Objectifs

- Maîtriser les structures de données (listes chaînées)
- Comprendre et implémenter des algorithmes de tri
- Optimiser la complexité algorithmique
- Manipuler des piles avec un ensemble d'opérations limité

## 🛠️ Opérations Autorisées

| Opération | Description |
|-----------|-------------|
| `sa` | Swap le premier et le deuxième élément de la pile A |
| `sb` | Swap le premier et le deuxième élément de la pile B |
| `ss` | `sa` et `sb` en même temps |
| `pa` | Push le premier élément de B vers A |
| `pb` | Push le premier élément de A vers B |
| `ra` | Rotate la pile A (premier élément devient le dernier) |
| `rb` | Rotate la pile B |
| `rr` | `ra` et `rb` en même temps |
| `rra` | Reverse rotate la pile A (dernier élément devient le premier) |
| `rrb` | Reverse rotate la pile B |
| `rrr` | `rra` et `rrb` en même temps |

## 📦 Installation

```bash
# Cloner le repository
git clone https://github.com/votre-username/push_swap_radix_sort.git
cd push_swap_radix_sort

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
# Exemple basique
./push_swap 4 67 3 87 23

# Avec des arguments entre guillemets
./push_swap "4 67 3 87 23"

# Vérifier le nombre d'opérations
./push_swap 4 67 3 87 23 | wc -l

# Vérifier que la pile est bien triée avec un checker
./push_swap 4 67 3 87 23 | ./checker 4 67 3 87 23
```

## 🧮 Algorithmes Implémentés

### Radix Sort (> 5 éléments)

L'algorithme Radix Sort est utilisé pour les listes de plus de 5 éléments. Il offre une complexité optimale :
- **Complexité** : O(n * k) où k est le nombre de bits
- Tri les nombres bit par bit, du moins significatif au plus significatif
- Utilise un système d'indexation pour normaliser les valeurs

### Algorithme optimisé (≤ 5 éléments)

Pour les petites listes, un algorithme spécifique et optimisé est utilisé :
- **2 éléments** : Maximum 1 opération
- **3 éléments** : Maximum 3 opérations
- **4-5 éléments** : Algorithme dédié avec pré-tri

## 📊 Performance

| Taille | Opérations (Radix Sort) |
|--------|-------------------------|
| 3 nombres | ≤ 3 opérations |
| 5 nombres | ≤ 12 opérations |
| 100 nombres | < 700 opérations (optimal < 900) |
| 500 nombres | < 5500 opérations (optimal < 7000) |

## 📂 Structure du Projet

```
.
├── Makefile                    # Compilation
├── README.md                   # Documentation
├── include/
│   └── push_swap.h            # Header principal
├── libft/                     # Bibliothèque personnelle
│   └── Libft/
│       ├── ft_*.c             # Fonctions de la libft
│       ├── ft_printf/         # Printf custom
│       └── get_next_line/     # Lecture de fichiers
└── src/
    ├── main.c                 # Point d'entrée
    ├── parcing.c              # Validation et parsing des arguments
    ├── radix_sort.c           # Implémentation du Radix Sort
    ├── sort_few.c             # Tri pour 3-5 éléments
    ├── sort_few_five.c        # Algorithmes spécifiques
    ├── sort_few_utils.c       # Utilitaires de tri
    ├── fonctions_listes.c     # Gestion des listes chaînées
    ├── instructions_1.c       # Opérations (sa, sb, pa, pb)
    ├── instructions_2.c       # Opérations (ra, rra, etc.)
    └── utils.c                # Fonctions utilitaires
```

## ⚠️ Gestion d'Erreurs

Le programme affiche `Error` sur stderr dans les cas suivants :
- Arguments non numériques
- Nombres hors limites (INT_MIN à INT_MAX)
- Doublons dans la liste
- Pas d'arguments fournis

## 🧪 Tests

```bash
# Générer des nombres aléatoires et tester
ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l

# Test avec 500 nombres
ARG=$(seq 1 500 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l

# Vérifier avec plusieurs tests
for i in {1..10}; do ARG=$(seq 1 100 | shuf | tr '\n' ' '); echo -n "Test $i: "; ./push_swap $ARG | wc -l; done
```

## 🔍 Ressources

- [Visualiseur Push_swap](https://github.com/o-reo/push_swap_visualizer)
- [Comprendre le Radix Sort](https://en.wikipedia.org/wiki/Radix_sort)
- [Tests automatiques](https://github.com/lmalki-h/push_swap_tester)

## 👤 Auteur

**vnieto-j** - École 42

## 📜 Licence

Ce projet est réalisé dans le cadre du cursus de l'école 42.

---

<p align="center">
  <i>Made with ☕ at 42 School</i>
</p>
