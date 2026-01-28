# CPP Module 09

<div align="center">
  
  ![42 Score](https://img.shields.io/badge/Score-100%2F100-brightgreen?style=for-the-badge&logo=42)
  ![C++](https://img.shields.io/badge/C++-98-blue?style=for-the-badge&logo=cplusplus)
  ![STL](https://img.shields.io/badge/STL-Containers-orange?style=for-the-badge)

</div>

## 📋 Table des Matières

- [Description](#-description)
- [Exercices](#-exercices)
  - [Exercise 00: Bitcoin Exchange](#exercise-00-bitcoin-exchange)
  - [Exercise 01: Reverse Polish Notation](#exercise-01-reverse-polish-notation)
  - [Exercise 02: PmergeMe](#exercise-02-pmergeme)
- [Compilation](#-compilation)
- [Utilisation](#-utilisation)
- [Concepts Clés](#-concepts-clés)
- [Ressources](#-ressources)

---

## 📖 Description

Le module CPP 09 est le dernier module de la piscine C++ de 42. Il se concentre sur l'utilisation avancée des conteneurs STL (Standard Template Library) et la compréhension des algorithmes de complexité. Ce module met l'accent sur la performance et le choix approprié des structures de données.

**Objectifs pédagogiques :**
- Maîtriser l'utilisation des conteneurs STL (`std::map`, `std::stack`, `std::vector`, `std::deque`)
- Comprendre les compromis entre différentes structures de données
- Implémenter et analyser des algorithmes de tri avancés
- Mesurer et comparer les performances
- Gérer le parsing et la validation de données

---

## 🎯 Exercices

### Exercise 00: Bitcoin Exchange

**Fichiers:** `BitcoinExchange.{hpp,cpp}`, `main.cpp`

#### Description
Programme qui calcule la valeur d'une certaine quantité de bitcoin à une date donnée, en utilisant une base de données historique des prix.

#### Fonctionnalités
- Lecture et parsing d'une base de données CSV (`data.csv`)
- Utilisation de `std::map` pour stocker les paires date/valeur
- Validation de format de date (YYYY-MM-DD)
- Gestion des erreurs (dates invalides, valeurs négatives, valeurs trop grandes)
- Recherche du prix le plus proche dans l'historique

#### Utilisation
```bash
cd ex00
make
./btc input.txt
```

#### Exemple
```bash
# Input file content:
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648

# Output:
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

#### Conteneur Utilisé
- **`std::map<std::string, float>`**: Stockage ordonné des dates et valeurs
  - Recherche en O(log n)
  - Ordre automatique par clé (date)
  - Facilite la recherche du prix le plus proche

---

### Exercise 01: Reverse Polish Notation

**Fichiers:** `RPN.{hpp,cpp}`, `main.cpp`

#### Description
Calculatrice utilisant la notation polonaise inversée (Reverse Polish Notation). Les opérandes précèdent les opérateurs.

#### Fonctionnalités
- Support des opérations: `+`, `-`, `*`, `/`
- Utilisation de `std::stack` pour l'évaluation
- Gestion des nombres < 10
- Validation de la syntaxe
- Gestion des erreurs (division par zéro, syntaxe invalide)

#### Utilisation
```bash
cd ex01
make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

#### Exemples
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
# Output: 42

./RPN "7 7 * 7 -"
# Output: 42

./RPN "1 2 * 2 / 2 * 2 4 - +"
# Output: 0

./RPN "(1 + 1)"
# Output: Error
```

#### Conteneur Utilisé
- **`std::stack<int>`**: Structure LIFO parfaite pour RPN
  - Push des opérandes
  - Pop de deux valeurs lors d'un opérateur
  - Push du résultat

#### Algorithme
```
Pour chaque token:
  Si c'est un nombre:
    Empiler sur la pile
  Si c'est un opérateur:
    Dépiler deux valeurs
    Appliquer l'opération
    Empiler le résultat
Résultat = sommet de la pile
```

---

### Exercise 02: PmergeMe

**Fichiers:** `PmergeMe.{hpp}`, `Pmerge.tpp`, `main.cpp`

#### Description
Implémentation de l'algorithme de tri **Ford-Johnson** (merge-insertion sort) avec deux conteneurs différents pour comparer les performances.

#### Fonctionnalités
- Tri d'une séquence d'entiers positifs
- Utilisation de templates pour supporter plusieurs conteneurs
- Implémentation avec `std::vector` et `std::deque`
- Mesure précise du temps d'exécution (microsecondes)
- Affichage avant/après tri
- Utilisation de la séquence de Jacobsthal pour l'ordre d'insertion optimal

#### Utilisation
```bash
cd ex02
make
./PmergeMe 3 5 9 7 4
```

#### Exemple
```bash
./PmergeMe 3 5 9 7 4
# Output:
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 42 us
Time to process a range of 5 elements with std::deque : 38 us

./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
# Affiche le tri de 3000 nombres aléatoires avec comparaison de temps
```

#### Conteneurs Utilisés
- **`std::vector<int>`**: 
  - Accès aléatoire en O(1)
  - Mémoire contiguë (meilleur cache)
  - Redimensionnement coûteux
  
- **`std::deque<int>`**:
  - Accès aléatoire en O(1)
  - Insertion/suppression rapide aux extrémités
  - Mémoire non-contiguë

#### Algorithme Ford-Johnson

Le Ford-Johnson merge-insertion sort est l'un des algorithmes de tri par comparaison les plus efficaces en termes de nombre minimal de comparaisons.

**Étapes:**
1. **Regroupement en paires**: Diviser les éléments en paires
2. **Tri des paires**: Comparer et organiser chaque paire (min, max)
3. **Tri récursif**: Trier les éléments maximums de chaque paire
4. **Insertion**: Insérer les minimums en utilisant la séquence de Jacobsthal

**Séquence de Jacobsthal:**
```
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2*J(n-2)

Séquence: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, ...
```

Cette séquence détermine l'ordre optimal d'insertion pour minimiser les comparaisons.

**Complexité:**
- Temps: O(n log n) en moyenne
- Comparaisons: ~n log₂ n - 1.4n (optimal)
- Espace: O(n)

---

## 🔧 Compilation

Chaque exercice dispose de son propre Makefile avec les règles standards de 42:

```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime les objets et l'exécutable
make re     # Recompile tout
```

**Flags de compilation:**
```makefile
-Wall -Wextra -Werror -std=c++98
```

---

## 🚀 Utilisation

### Exercise 00 - Bitcoin Exchange
```bash
cd ex00 && make
./btc input.txt
```

### Exercise 01 - RPN
```bash
cd ex01 && make
./RPN "3 4 + 2 * 7 /"
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

### Exercise 02 - PmergeMe
```bash
cd ex02 && make
./PmergeMe 3 5 9 7 4
./PmergeMe `jot -r 3000 1 100000`  # macOS
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`  # Linux
```

---

## 💡 Concepts Clés

### 1. Conteneurs STL

| Conteneur | Accès | Insertion | Recherche | Mémoire | Usage |
|-----------|-------|-----------|-----------|---------|-------|
| `std::vector` | O(1) | O(n) | O(n) | Contiguë | Tableau dynamique |
| `std::deque` | O(1) | O(1) aux bouts | O(n) | Non-contiguë | File double |
| `std::map` | O(log n) | O(log n) | O(log n) | Non-contiguë | Arbre binaire |
| `std::stack` | O(1) sommet | O(1) | - | Dépend | Pile LIFO |

### 2. Choix du Conteneur

**Utilisez `std::map` quand:**
- Vous avez besoin d'un ordre trié
- Recherche par clé fréquente
- Insertion/suppression dynamique

**Utilisez `std::stack` quand:**
- Vous avez besoin d'un comportement LIFO
- Seul l'accès au sommet est nécessaire
- Évaluation d'expressions

**Utilisez `std::vector` quand:**
- Accès aléatoire fréquent
- Taille relativement stable
- Performance du cache importante

**Utilisez `std::deque` quand:**
- Insertion/suppression aux extrémités
- Pas de réallocation souhaitée
- Accès aléatoire nécessaire

### 3. Templates C++

Les templates permettent de créer du code générique:

```cpp
template<typename Container>
class PmergeMe {
    private:
        Container _data;
    // ...
};
```

Avantages:
- Réutilisabilité du code
- Type safety à la compilation
- Aucun coût d'exécution (résolution compile-time)

### 4. Mesure de Performance

Utilisation de `<ctime>` pour mesurer le temps:

```cpp
clock_t start = clock();
// ... code à mesurer ...
clock_t end = clock();
unsigned long microseconds = (end - start) * 1000000UL / CLOCKS_PER_SEC;
```

### 5. Complexité Algorithmique

| Algorithme | Meilleur | Moyen | Pire | Espace |
|------------|----------|-------|------|--------|
| Ford-Johnson | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) |

---

## 📚 Ressources

### Documentation
- [C++ Reference - STL Containers](https://en.cppreference.com/w/cpp/container)
- [Ford-Johnson Algorithm](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
- [Jacobsthal Sequence](https://oeis.org/A001045)

### Concepts Importants
- **STL Containers**: `vector`, `deque`, `map`, `stack`
- **Templates**: Programmation générique
- **Algorithmique**: Tri, recherche, évaluation
- **Complexité**: Analyse temporelle et spatiale
- **Performance**: Mesure et comparaison

### Parsing et Validation
- Validation de dates (format ISO)
- Parsing de CSV
- Validation de nombres
- Gestion d'erreurs robuste

---

## ⚠️ Points d'Attention

### Exercise 00
- ✅ Gérer les dates invalides (29/02 non-bissextile, mois > 12, etc.)
- ✅ Trouver le prix le plus proche si date exacte n'existe pas
- ✅ Valider les nombres (0-1000, pas de négatifs)
- ✅ Format CSV strict

### Exercise 01
- ✅ Nombres limités à < 10
- ✅ Uniquement `+`, `-`, `*`, `/`
- ✅ Gérer division par zéro
- ✅ Format strict avec espaces

### Exercise 02
- ✅ Implémenter Ford-Johnson correctement
- ✅ Utiliser la séquence de Jacobsthal
- ✅ Gérer les nombres impairs (straggler)
- ✅ Mesurer avec précision (microsecondes)
- ✅ Templates fonctionnels avec vector ET deque
- ✅ Pas de doublons dans l'input

---

## 🎓 Compétences Acquises

- ✅ Maîtrise des conteneurs STL
- ✅ Programmation générique avec templates
- ✅ Algorithmes de tri avancés
- ✅ Analyse de complexité
- ✅ Mesure de performance
- ✅ Parsing et validation de données
- ✅ Gestion d'erreurs robuste
- ✅ Choix de structures de données appropriées

---

<div align="center">

**Module complété avec succès - 100/100** ✨

*Fait avec ❤️ pour 42*

</div>
