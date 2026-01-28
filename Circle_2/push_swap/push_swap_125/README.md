# Push_swap

![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)

## 📝 Description

**Push_swap** est un projet de l'école 42 qui consiste à trier une pile de nombres entiers en utilisant un ensemble limité d'instructions, tout en minimisant le nombre d'opérations. Le projet utilise deux piles (stack A et stack B) et impose des règles strictes pour manipuler les données.

## 🎯 Objectifs du projet

- Comprendre et implémenter des algorithmes de tri complexes
- Optimiser le nombre d'opérations nécessaires au tri
- Manipuler des structures de données de type pile (stack)
- Gérer le parsing d'arguments avec gestion d'erreurs robuste
- Développer des stratégies de tri adaptées selon la taille de l'entrée

## 🛠️ Compilation

### Prérequis

- `gcc` ou `cc`
- `make`
- Système d'exploitation UNIX/Linux

### Installation

```bash
# Cloner le dépôt
git clone [votre-repo] push_swap
cd push_swap

# Compiler le projet
make

# Compiler avec le bonus (checker)
make bonus

# Nettoyer les fichiers objets
make clean

# Nettoyer complètement
make fclean

# Recompiler
make re
```

Cela générera les exécutables :
- `push_swap` : Programme principal de tri
- `checker` : Programme bonus pour vérifier le tri (avec `make bonus`)

## 🚀 Utilisation

### Push_swap

```bash
./push_swap <nombre1> <nombre2> <nombre3> ...
```

Le programme affiche la liste des instructions nécessaires pour trier les nombres.

### Exemples

```bash
# Trier 5 nombres
./push_swap 3 2 5 1 4
# Affiche les instructions de tri

# Avec des nombres négatifs
./push_swap -5 2 0 -1 8

# Format avec guillemets (tous les nombres dans une chaîne)
./push_swap "3 2 5 1 4"
```

### Checker (bonus)

Le checker vérifie si une séquence d'instructions trie correctement la pile :

```bash
# Générer les instructions et les vérifier
./push_swap 3 2 5 1 4 | ./checker 3 2 5 1 4
# Affiche : OK (si le tri est correct) ou KO (si incorrect)

# Tester manuellement
./checker 3 2 1
sa
ra
# Ctrl+D pour terminer
# Affiche : OK ou KO
```

## 📋 Instructions disponibles

Le programme utilise un ensemble limité d'instructions :

### Opérations de swap (échange)

| Instruction | Description |
|-------------|-------------|
| `sa` | Swap les 2 premiers éléments de la pile A |
| `sb` | Swap les 2 premiers éléments de la pile B |
| `ss` | `sa` et `sb` en même temps |

### Opérations de push (déplacement)

| Instruction | Description |
|-------------|-------------|
| `pa` | Prend le premier élément de B et le met sur A |
| `pb` | Prend le premier élément de A et le met sur B |

### Opérations de rotation

| Instruction | Description |
|-------------|-------------|
| `ra` | Rotation vers le haut de A (le premier devient le dernier) |
| `rb` | Rotation vers le haut de B |
| `rr` | `ra` et `rb` en même temps |

### Opérations de rotation inverse

| Instruction | Description |
|-------------|-------------|
| `rra` | Rotation vers le bas de A (le dernier devient le premier) |
| `rrb` | Rotation vers le bas de B |
| `rrr` | `rra` et `rrb` en même temps |

## 🧮 Algorithmes de tri

Le projet implémente différentes stratégies selon la taille de l'entrée :

### Petites tailles (2-5 éléments)

- **2 éléments** : Simple swap si nécessaire
- **3 éléments** : Algorithme optimisé avec maximum 2 opérations
- **4-5 éléments** : Push des plus petits vers B, tri de 3 sur A, puis repush

### Moyennes tailles (≤100 éléments)

- Tous les éléments (sauf 3) sont poussés vers B
- Tri de 3 éléments sur A
- Repush optimal des éléments de B vers A

### Grandes tailles (>100 éléments)

- **Algorithme Chunky (par quartiles)** :
  - Division de la pile en quartiles
  - Push progressif par segments
  - Optimisation des rotations doubles
  - Calcul du coût minimal pour chaque élément
  - Tri final par coût optimal

## 📊 Performance

### Objectifs de nombre d'opérations

| Taille | Nombre max d'opérations |
|--------|-------------------------|
| 3 nombres | 2-3 opérations |
| 5 nombres | ~12 opérations |
| 100 nombres | <700 opérations (note max) / <900 (note moyenne) |
| 500 nombres | <5500 opérations (note max) / <7000 (note moyenne) |

## 📁 Structure du projet

```
push_swap/
├── Makefile
├── README.md
├── include/
│   └── push_swap.h
├── libft/
│   └── (bibliothèque libft)
└── src/
    ├── checker.c                   (bonus)
    ├── checker_instructions.c      (bonus)
    ├── checker_utils.c             (bonus)
    ├── checker_utils2.c            (bonus)
    ├── fonctions_lists.c
    ├── instructions_1.c
    ├── instructions_2.c
    ├── main.c
    ├── new_pre_sort_1.c
    ├── new_pre_sort_2.c
    ├── parsing.c
    ├── parsing2.c
    ├── sort_few.c
    ├── sort_few_utils.c
    ├── sort_rotate.c
    ├── sort_utils.c
    ├── sort.c
    └── utils.c
```

## ⚙️ Gestion des erreurs

Le programme gère tous les cas d'erreur et affiche `Error\n` sur stderr :

- ✅ Arguments non numériques
- ✅ Nombres en dehors de la plage INT (overflow/underflow)
- ✅ Doublons dans la liste
- ✅ Aucun argument fourni
- ✅ Allocations mémoire échouées

### Exemples d'erreurs

```bash
./push_swap 1 2 three
# Error

./push_swap 1 2 2 3
# Error (doublon)

./push_swap 2147483648
# Error (overflow)

./push_swap
# (pas d'erreur, programme se termine)
```

## 🧪 Tests

### Tests basiques

```bash
# Déjà trié (pas d'instruction affichée)
./push_swap 1 2 3 4 5

# Ordre inverse
./push_swap 5 4 3 2 1

# Ordre aléatoire
./push_swap 3 2 5 1 4
```

### Tests avec checker

```bash
# Test automatique
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG

# Test avec compteur d'instructions
./push_swap 3 2 5 1 4 | wc -l
```

### Tests de performance

```bash
# Générer des nombres aléatoires et compter les instructions
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l

# Tester 500 nombres
ARG=$(shuf -i 1-500 -n 500 | tr '\n' ' '); ./push_swap $ARG | wc -l
```

### Testeur automatique (exemple)

```bash
#!/bin/bash
for i in {1..100}; do
    ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ')
    RESULT=$(./push_swap $ARG | ./checker $ARG)
    COUNT=$(./push_swap $ARG | wc -l)
    echo "Test $i: $RESULT ($COUNT operations)"
done
```

## 🔬 Détails techniques

### Structure de données

```c
typedef struct s_nb
{
    int         nb;        // Valeur numérique
    int         index;     // Index après tri (0 = plus petit)
    struct s_nb *next;     // Pointeur vers l'élément suivant
    struct s_nb *prev;     // Pointeur vers l'élément précédent
}   t_nb;
```

### Optimisations clés

- **Indexation** : Attribution d'un index (0 à n-1) pour faciliter les comparaisons
- **Calcul de coût** : Évaluation du nombre d'opérations pour chaque mouvement
- **Rotations doubles** : Utilisation de `rr` et `rrr` quand possible
- **Algorithme adaptatif** : Choix de la stratégie selon la taille

## 💡 Stratégies avancées

### Algorithme Chunky (quartiles)

1. **Division** : Séparation de la pile en 4 quartiles
2. **Push séquentiel** : Déplacement par segments vers stack B
3. **Rotation intelligente** : Rotation de B pour les petits indices
4. **Repush optimal** : Calcul du coût minimal pour chaque élément

### Optimisation des rotations

- Détection des rotations doubles possibles
- Minimisation du nombre total de mouvements
- Choix entre rotation normale et inverse selon la position

## 👤 Auteur

**vnieto-j** - Étudiant à 42

---

## 📚 Ressources

- [Sorting algorithm - Wikipedia](https://en.wikipedia.org/wiki/Sorting_algorithm)
- [Stack (data structure) - Wikipedia](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))
- [Push_swap visualizer](https://github.com/o-reo/push_swap_visualizer)
- [Push_swap tester](https://github.com/lmalki-h/push_swap_tester)

## 📄 Licence

Ce projet est réalisé dans le cadre du cursus de l'école 42.
