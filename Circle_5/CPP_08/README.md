# CPP Module 08

<div align="center">

![Score](https://img.shields.io/badge/Score-100%2F100-success?style=for-the-badge&logo=42)
![C++](https://img.shields.io/badge/C++-98-00599C?style=for-the-badge&logo=c%2B%2B)

*Templated containers, iterators, algorithms*

</div>

---

## 📋 Table of Contents

- [About](#about)
- [Exercises](#exercises)
  - [Exercise 00: Easy find](#exercise-00-easy-find)
  - [Exercise 01: Span](#exercise-01-span)
  - [Exercise 02: Mutant Stack](#exercise-02-mutant-stack)
- [Compilation](#compilation)
- [Usage](#usage)
- [Key Concepts](#key-concepts)
- [Resources](#resources)

---

## 📖 About

Ce module CPP_08 explore les conteneurs STL (Standard Template Library), les itérateurs et les algorithmes en C++98. L'objectif est de comprendre et maîtriser l'utilisation des templates pour créer des structures de données génériques et réutilisables.

**Compétences développées :**
- Templates en C++
- Conteneurs STL (vector, list, stack)
- Itérateurs
- Algorithmes STL
- Gestion d'exceptions
- Classes héritant de conteneurs STL

---

## 🎯 Exercises

### Exercise 00: Easy find

**Fichiers:** `ex00/`

Implémentation d'une fonction template `easyfind` qui recherche la première occurrence d'une valeur entière dans un conteneur.

**Prototype:**
```cpp
template <typename T>
typename T::iterator easyfind(T &container, int value);
```

**Caractéristiques:**
- Fonctionne avec tous les conteneurs STL
- Utilise `std::find` pour la recherche
- Lève une exception si la valeur n'est pas trouvée
- Retourne un itérateur vers l'élément trouvé

**Exemple d'utilisation:**
```cpp
std::vector<int> vector;
vector.push_back(1);
vector.push_back(2);
vector.push_back(3);

try {
    std::cout << *easyfind(vector, 2) << std::endl;  // Affiche: 2
} catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

---

### Exercise 01: Span

**Fichiers:** `ex01/`

Implémentation d'une classe `Span` qui stocke un maximum de N entiers et peut calculer le plus court et le plus long span (différence) entre tous les nombres stockés.

**Interface publique:**
```cpp
class Span {
    Span(unsigned int n);
    void addNumber(int nb);
    int shortestSpan() const;
    int longestSpan() const;
};
```

**Fonctionnalités:**
- Stockage limité à N éléments (défini à la construction)
- `addNumber()` : Ajoute un nombre (exception si plein)
- `shortestSpan()` : Retourne la plus petite différence entre deux nombres
- `longestSpan()` : Retourne la plus grande différence (max - min)
- Gestion d'exceptions pour les cas limites

**Exemple d'utilisation:**
```cpp
Span sp = Span(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);

std::cout << sp.shortestSpan() << std::endl;  // Affiche: 2
std::cout << sp.longestSpan() << std::endl;   // Affiche: 14
```

**Algorithmes utilisés:**
- `std::sort` pour le calcul du shortest span
- `std::min_element` et `std::max_element` pour le longest span

---

### Exercise 02: Mutant Stack

**Fichiers:** `ex02/`

Implémentation d'une classe `MutantStack` qui hérite de `std::stack` et ajoute la fonctionnalité d'itération, normalement absente des stacks.

**Interface:**
```cpp
template <typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    iterator begin();
    iterator end();
};
```

**Caractéristiques:**
- Hérite de `std::stack<T>`
- Ajoute des itérateurs via l'accès au conteneur sous-jacent (`c`)
- Compatible avec toutes les fonctions de `std::stack`
- Permet de parcourir la stack comme un conteneur normal

**Exemple d'utilisation:**
```cpp
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);
mstack.push(3);

MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();

while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
}
```

---

## 🔨 Compilation

Chaque exercice dispose de son propre Makefile. Pour compiler :

```bash
# Exercise 00
cd ex00
make

# Exercise 01
cd ex01
make

# Exercise 02
cd ex02
make
```

**Flags de compilation:**
```
-std=c++98 -Wall -Werror -Wextra
```

**Commandes disponibles:**
- `make` : Compile le programme
- `make clean` : Supprime les fichiers objets
- `make fclean` : Supprime les fichiers objets et l'exécutable
- `make re` : Recompile tout

---

## 🚀 Usage

### Exercise 00
```bash
cd ex00
make
./EasyFind
```

### Exercise 01
```bash
cd ex01
make
./Span
```

### Exercise 02
```bash
cd ex02
make
./MutantStack
```

---

## 💡 Key Concepts

### Templates
Les templates permettent de créer des fonctions et classes génériques qui fonctionnent avec différents types de données.

```cpp
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}
```

### Conteneurs STL
La STL fournit plusieurs conteneurs :
- **Séquentiels**: `vector`, `list`, `deque`
- **Associatifs**: `map`, `set`
- **Adaptateurs**: `stack`, `queue`, `priority_queue`

### Itérateurs
Les itérateurs permettent de parcourir les conteneurs de manière uniforme :
- `begin()` : Pointe vers le premier élément
- `end()` : Pointe après le dernier élément
- `++it` : Avance l'itérateur
- `*it` : Déréférence l'itérateur

### Algorithmes STL
La STL fournit de nombreux algorithmes génériques :
- `std::find` : Recherche linéaire
- `std::sort` : Tri
- `std::min_element` / `std::max_element` : Recherche de min/max

### Exceptions
Gestion des erreurs avec le système d'exceptions C++ :
```cpp
try {
    // Code susceptible de lever une exception
} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

---

## 📚 Resources

- [C++ Reference - Containers](https://en.cppreference.com/w/cpp/container)
- [C++ Reference - Algorithms](https://en.cppreference.com/w/cpp/algorithm)
- [C++ Reference - Iterators](https://en.cppreference.com/w/cpp/iterator)
- [C++ Templates](https://en.cppreference.com/w/cpp/language/templates)
- [Standard Template Library (STL)](https://www.geeksforgeeks.org/the-c-standard-template-library-stl/)

---

<div align="center">

**Made with ☕ at 42**

*"The only way to learn a new programming language is by writing programs in it."* - Dennis Ritchie

</div>
