# CPP Module 07 - Templates 🔥

<div align="center">

![Grade](https://img.shields.io/badge/Score-100%2F100-brightgreen?style=for-the-badge)
![C++](https://img.shields.io/badge/C++-98-blue?style=for-the-badge&logo=c%2B%2B)
![42](https://img.shields.io/badge/42-School-000000?style=for-the-badge)

</div>

## 📋 Description

Module d'introduction aux **templates** en C++98. Ce module explore la programmation générique à travers trois exercices progressifs : templates de fonctions, templates avec itérateurs, et templates de classes.

## 🎯 Objectifs d'apprentissage

- Comprendre et implémenter des **templates de fonctions**
- Maîtriser les **templates de classes**
- Gérer la **généricité** en C++
- Implémenter des **conteneurs génériques**
- Respecter la **norme C++98**

## 📁 Structure du projet

```
CPP_07/
├── ex00/          # Templates de fonctions de base
│   ├── includes/
│   │   └── whatever.hpp
│   └── srcs/
│       ├── main.cpp
│       └── whatever.cpp
├── ex01/          # Template iter() pour tableaux
│   ├── includes/
│   │   └── iter.hpp
│   └── srcs/
│       └── main.cpp
└── ex02/          # Template de classe Array<T>
    ├── includes/
    │   └── Array.hpp
    └── srcs/
        ├── Array.tpp
        └── main.cpp
```

## 🚀 Exercices

### Ex00 - Templates de fonctions
Implémentation de trois templates de fonctions génériques :
- `swap()` : échange deux valeurs
- `min()` : retourne la plus petite valeur
- `max()` : retourne la plus grande valeur

**Fonctionnalités :**
- ✅ Templates fonctionnant avec n'importe quel type
- ✅ Tests avec `int` et `std::string`
- ✅ Utilisation du scope resolution `::` pour éviter les conflits

### Ex01 - Fonction iter()
Template de fonction qui applique une fonction à chaque élément d'un tableau.

**Fonctionnalités :**
- ✅ Template prenant un tableau, sa taille et une fonction
- ✅ Support des tableaux const et non-const
- ✅ Tests avec différents types de données
- ✅ Fonctions de callback personnalisées

### Ex02 - Classe Array<T>
Implémentation d'une classe template représentant un tableau dynamique générique.

**Fonctionnalités :**
- ✅ Constructeur par défaut (tableau vide)
- ✅ Constructeur avec taille `n`
- ✅ Copy constructor avec **deep copy**
- ✅ Opérateur d'affectation avec deep copy
- ✅ Opérateur d'accès `[]` avec vérification des bornes
- ✅ Méthode `size()` pour obtenir la taille
- ✅ Exception `OutOfRange` pour les accès invalides
- ✅ Support des tableaux const

## 🔨 Compilation

Chaque exercice possède son propre Makefile :

```bash
# Ex00
cd ex00 && make
./whatever

# Ex01
cd ex01 && make
./Iter

# Ex02
cd ex02 && make
./Array
```

**Flags de compilation :** `-std=c++98 -Wall -Werror -Wextra`

## 💡 Concepts clés

### Templates de fonctions
```cpp
template <typename T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
```

### Templates de classes
```cpp
template <typename T>
class Array {
private:
    T*           _array;
    unsigned int _size;
public:
    Array();
    Array(unsigned int n);
    // ...
};
```

### Séparation des templates
Les implémentations de templates doivent être dans les headers ou incluses via `.tpp` car le compilateur doit connaître le code à la compilation.

## ⚠️ Points d'attention

- **Pas de `using namespace std;`** : respect de la norme 42
- **Deep copy obligatoire** : pour Array, copie complète du contenu
- **Gestion mémoire** : pas de leaks (vérifiable avec valgrind)
- **Exceptions** : utilisation de `std::exception` pour les erreurs
- **Const correctness** : surcharge const et non-const de `operator[]`

## 🧪 Tests

### Ex00
- Tests avec types primitifs (`int`)
- Tests avec objets (`std::string`)
- Vérification du scope resolution

### Ex01
- Itération sur tableaux d'entiers
- Modification d'éléments via iter
- Tests avec différentes fonctions callback

### Ex02
- Construction de tableaux vides
- Construction avec taille spécifique
- Deep copy et indépendance des copies
- Accès const et non-const
- Gestion des exceptions (accès hors limites)
- Tests avec différents types (`int`, `std::string`)

## 📚 Ressources

- [cppreference - Templates](https://en.cppreference.com/w/cpp/language/templates)
- [C++ Templates: The Complete Guide](https://www.josuttis.com/tmplbook/)
- Norme C++98

## 🎓 Compétences développées

- ✅ Programmation générique
- ✅ Templates en C++
- ✅ RAII et gestion mémoire
- ✅ Surcharge d'opérateurs
- ✅ Gestion d'exceptions
- ✅ Const correctness

## 📊 Note

**100/100** ✨

---

<div align="center">

Fait avec ❤️ par un étudiant de 42

*"Code is like humor. When you have to explain it, it's bad."* – Cory House

</div>
