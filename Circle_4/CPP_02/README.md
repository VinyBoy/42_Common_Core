# CPP Module 02 - Guide Étudiant 📚

## 📊 Évaluation
**Note obtenue : 100/100** 🏆

---

## 🎯 Objectif du Module

Ce module introduit des concepts fondamentaux de la POO en C++ :
- **La Forme Canonique Orthodoxe** (Orthodox Canonical Form)
- **La surcharge d'opérateurs** (Operator Overloading)
- **Les nombres à virgule fixe** (Fixed-point numbers)
- **La conversion de types** (Type conversion)

## 📁 Structure du Projet

```
CPP_02/
├── ex00/          # My First Class in Orthodox Canonical Form
├── ex01/          # Towards a more useful fixed-point number class
└── ex02/          # Now we're talking
```

---

## 📐 Exercice 00 : My First Class in Orthodox Canonical Form

### Description
Créer une classe `Fixed` représentant un nombre à virgule fixe en respectant la **Forme Canonique Orthodoxe**.

### Compilation et Exécution
```bash
cd ex00
make
./Fixed
```

### 🔑 La Forme Canonique Orthodoxe (OCF)

Toute classe C++ doit implémenter ces **4 éléments essentiels** :

```cpp
class Fixed {
public:
    Fixed(void);                          // 1. Constructeur par défaut
    Fixed(Fixed const &src);              // 2. Constructeur de copie
    Fixed& operator=(Fixed const &rhs);   // 3. Opérateur d'assignation
    ~Fixed(void);                         // 4. Destructeur
};
```

#### 1. Constructeur par Défaut
```cpp
Fixed::Fixed(void) : _Raw(0) {
    std::cout << "Default Constructor called" << std::endl;
}
```
- Initialise l'objet avec des valeurs par défaut
- Utilise une liste d'initialisation (`: _Raw(0)`)

#### 2. Constructeur de Copie
```cpp
Fixed::Fixed(Fixed const &src) {
    std::cout << "Copy constructor called" << std::endl;
    *this = src;  // Utilise l'opérateur d'assignation
}
```
- Crée une copie d'un objet existant
- Appelé lors de : `Fixed b(a);` ou `Fixed b = a;`

#### 3. Opérateur d'Assignation
```cpp
Fixed& Fixed::operator=(Fixed const &rhs) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)               // Protection contre l'auto-assignation
        this->_Raw = rhs.getRawBits();
    return (*this);
}
```
- Copie les valeurs d'un objet vers un autre **déjà existant**
- Appelé lors de : `a = b;`
- **TOUJOURS vérifier l'auto-assignation** (`this != &rhs`)
- **TOUJOURS retourner `*this`**

#### 4. Destructeur
```cpp
Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}
```
- Libère les ressources de l'objet
- Appelé automatiquement à la fin du scope

### 💡 Pourquoi l'OCF est Cruciale ?

Sans l'OCF, votre classe peut :
- ❌ Provoquer des fuites mémoires
- ❌ Créer des copies superficielles (shallow copy)
- ❌ Causer des double-free
- ❌ Avoir un comportement indéfini

### Nombres à Virgule Fixe

```cpp
class Fixed {
private:
    int _Raw;                           // Valeur brute (format virgule fixe)
    static const int _fractionalBits = 8; // Nombre de bits fractionnaires
};
```

**Représentation** : 8 bits pour la partie entière, 8 bits pour la partie fractionnaire.

#### Exemple de Stockage
```
Nombre : 42.42
En virgule fixe (8 bits fract.) : 42.42 * 256 = 10859
Stocké dans _Raw : 10859
```

---

## 🔢 Exercice 01 : Towards a more useful fixed-point number class

### Description
Ajouter des constructeurs pour convertir `int` et `float` en virgule fixe, et inversement.

### Compilation et Exécution
```bash
cd ex01
make
./Fixed
```

### Nouvelles Fonctionnalités

#### 1. Constructeur à partir d'un Int
```cpp
Fixed::Fixed(int const n) {
    std::cout << "Int constructor called" << std::endl;
    _Raw = n << 8;  // Décalage de 8 bits à gauche (multiplication par 256)
}
```

**Exemple** :
```
42 en int → 42 << 8 = 10752
```

#### 2. Constructeur à partir d'un Float
```cpp
Fixed::Fixed(float const n) {
    std::cout << "Float constructor called" << std::endl;
    _Raw = roundf(n * (1 << _fractionalBits));
}
```

**Calcul** :
- `1 << 8` = 256
- `42.42 * 256 = 10859.52`
- `roundf(10859.52) = 10859`

#### 3. Conversion vers Float
```cpp
float Fixed::toFloat(void) const {
    return ((float)_Raw / (1 << _fractionalBits));
}
```

**Exemple** :
```
_Raw = 10859
10859 / 256 = 42.417969... ≈ 42.42
```

#### 4. Conversion vers Int
```cpp
int Fixed::toInt(void) const {
    return (_Raw >> _fractionalBits);  // Décalage de 8 bits à droite
}
```

**Exemple** :
```
_Raw = 10859
10859 >> 8 = 42
```

### Surcharge de l'Opérateur <<

```cpp
std::ostream & operator<<(std::ostream &o, Fixed const &i) {
    o << i.toFloat();
    return (o);
}
```

**Usage** :
```cpp
Fixed a(42.42f);
std::cout << a << std::endl;  // Affiche: 42.42
```

### 🎓 Concepts des Opérateurs de Décalage

| Opération | Symbole | Effet | Exemple |
|-----------|---------|-------|---------|
| Décalage gauche | `<<` | Multiplie par 2^n | `5 << 2` = 20 |
| Décalage droite | `>>` | Divise par 2^n | `20 >> 2` = 5 |

**En virgule fixe (8 bits fract.)** :
- `<< 8` = `* 256` (conversion int → fixe)
- `>> 8` = `/ 256` (conversion fixe → int)

---

## ⚙️ Exercice 02 : Now we're talking

### Description
Surcharger tous les opérateurs de comparaison, arithmétiques et d'incrémentation/décrémentation.

### Compilation et Exécution
```bash
cd ex02
make
./Fixed
```

### Opérateurs de Comparaison

```cpp
bool Fixed::operator>(Fixed const& rhs) const {
    return (this->_Raw > rhs._Raw);
}

bool Fixed::operator<(Fixed const& rhs) const {
    return (this->_Raw < rhs._Raw);
}

bool Fixed::operator>=(Fixed const& rhs) const {
    return (this->_Raw >= rhs._Raw);
}

bool Fixed::operator<=(Fixed const& rhs) const {
    return (this->_Raw <= rhs._Raw);
}

bool Fixed::operator==(Fixed const& rhs) const {
    return (this->_Raw == rhs._Raw);
}

bool Fixed::operator!=(Fixed const& rhs) const {
    return (this->_Raw != rhs._Raw);
}
```

**Usage** :
```cpp
Fixed a(42.42f);
Fixed b(10.5f);

if (a > b)
    std::cout << "a est plus grand" << std::endl;
```

### Opérateurs Arithmétiques

```cpp
Fixed Fixed::operator+(Fixed const &rhs) const {
    return Fixed(this->toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(Fixed const &rhs) const {
    return Fixed(this->toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(Fixed const &rhs) const {
    return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(Fixed const &rhs) const {
    return Fixed(this->toFloat() / rhs.toFloat());
}
```

**Usage** :
```cpp
Fixed a(10);
Fixed b(5);
Fixed c = a + b;  // c = 15
Fixed d = a * b;  // d = 50
```

### Opérateurs d'Incrémentation/Décrémentation

#### Pré-incrémentation (++a)
```cpp
Fixed& Fixed::operator++() {
    _Raw++;                 // Incrémente la valeur brute
    return (*this);         // Retourne la référence modifiée
}
```

#### Post-incrémentation (a++)
```cpp
Fixed Fixed::operator++(int) {
    Fixed tmp(*this);       // Sauvegarde la valeur actuelle
    _Raw++;                 // Incrémente
    return (tmp);           // Retourne l'ancienne valeur
}
```

#### Différence Fondamentale

| Type | Syntaxe | Retour | Quand l'incrémenter |
|------|---------|--------|---------------------|
| Pré | `++a` | Référence | Avant utilisation |
| Post | `a++` | Copie | Après utilisation |

**Exemple** :
```cpp
Fixed a(5);
Fixed b = ++a;  // a = 6, b = 6 (pré-incrémentation)

Fixed c(5);
Fixed d = c++;  // c = 6, d = 5 (post-incrémentation)
```

### Fonctions Statiques Min/Max

```cpp
// Version non-const
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

// Version const
const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

// Max similaire
Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}
```

**Usage** :
```cpp
Fixed a(42.42f);
Fixed b(10.5f);

std::cout << Fixed::max(a, b) << std::endl;  // Affiche: 42.42
std::cout << Fixed::min(a, b) << std::endl;  // Affiche: 10.5
```

### 🎯 Pourquoi 2 Versions (const et non-const) ?

```cpp
Fixed a(10);
Fixed b(5);
Fixed::max(a, b) = Fixed(100);  // OK avec version non-const

const Fixed c(10);
const Fixed d(5);
Fixed::max(c, d) = Fixed(100);  // ERREUR ! Nécessite version const
```

---

## 🔑 Concepts C++ Avancés du Module

### 1. Surcharge d'Opérateurs

#### Règles Générales
```cpp
// Opérateur binaire (a + b)
ReturnType operator+(Type const &rhs) const;

// Opérateur unaire (++a)
ReturnType& operator++();

// Opérateur de flux
friend std::ostream& operator<<(std::ostream &o, Type const &obj);
```

#### Quels Opérateurs Surcharger ?

| Catégorie | Opérateurs | Usage |
|-----------|------------|-------|
| Arithmétiques | `+ - * /` | Calculs |
| Comparaison | `< > <= >= == !=` | Tests |
| Incrémentation | `++ --` | Compteurs |
| Flux | `<< >>` | Affichage/Lecture |
| Assignation | `=` | Copie |

### 2. Const Correctness

```cpp
// Méthode const : Ne modifie pas l'objet
int getRawBits(void) const;

// Paramètre const : Ne sera pas modifié
Fixed(Fixed const &src);

// Référence const : Pas de copie, pas de modification
bool operator==(Fixed const &rhs) const;
```

### 3. Auto-assignation

```cpp
Fixed& Fixed::operator=(Fixed const &rhs) {
    if (this != &rhs)  // ⚠️ CRUCIAL !
        this->_Raw = rhs.getRawBits();
    return (*this);
}
```

**Pourquoi ?**
```cpp
Fixed a(42);
a = a;  // Sans protection, comportement indéfini !
```

### 4. Retour par Référence vs Copie

#### Retour par Référence
```cpp
Fixed& operator++() {
    _Raw++;
    return (*this);  // Retourne l'objet lui-même
}
```
- ✅ Pas de copie (performance)
- ✅ Permet le chaînage : `++++a`
- ⚠️ Ne jamais retourner une référence vers une variable locale !

#### Retour par Copie
```cpp
Fixed operator++(int) {
    Fixed tmp(*this);
    _Raw++;
    return (tmp);  // Retourne une copie
}
```
- ❌ Crée une copie (coût)
- ✅ Sémantique correcte pour post-incrémentation

---

## 💡 Virgule Fixe : Pourquoi et Comment ?

### Avantages
- ✅ **Performance** : Pas de FPU nécessaire
- ✅ **Déterministe** : Résultats reproductibles
- ✅ **Précision contrôlée** : Pas d'erreurs d'arrondi imprévues

### Inconvénients
- ❌ **Plage limitée** : Moins grande que les floats
- ❌ **Précision fixe** : Ne s'adapte pas au nombre

### Calculs en Virgule Fixe

#### Addition/Soustraction
```cpp
// Simple : même échelle
Fixed a(10.5f);  // _Raw = 2688
Fixed b(5.25f);  // _Raw = 1344
// Peut additionner directement _Raw
// Mais ici on convertit pour simplifier
```

#### Multiplication
```cpp
// Attention : résultat sur 2x les bits fractionnaires
// a * b → (_Raw_a * _Raw_b) >> fractionalBits
// Ici simplifié par conversion float
Fixed c = a * b;
```

---

## 🛡️ Bonnes Pratiques

### 1. Liste d'Initialisation
```cpp
// ✅ BIEN : Initialisation directe
Fixed::Fixed(int n) : _Raw(n << 8) {}

// ❌ ÉVITER : Assignation dans le corps
Fixed::Fixed(int n) {
    _Raw = n << 8;
}
```

### 2. Const Correctness
```cpp
// ✅ Méthodes qui ne modifient pas : const
int getRawBits(void) const;

// ✅ Paramètres en lecture seule : const &
Fixed(Fixed const &src);
```

### 3. Protection Auto-assignation
```cpp
if (this != &rhs)  // ⚠️ TOUJOURS vérifier !
```

### 4. Retour de *this
```cpp
Fixed& operator=(Fixed const &rhs) {
    // ...
    return (*this);  // ⚠️ OBLIGATOIRE pour chaînage
}
```

---

## 🐛 Erreurs Courantes

### 1. Oublier le `const` dans operator=
```cpp
// ❌ ERREUR
Fixed& operator=(Fixed &rhs);

// ✅ CORRECT
Fixed& operator=(Fixed const &rhs);
```

### 2. Ne pas retourner `*this`
```cpp
// ❌ ERREUR
void operator=(Fixed const &rhs);

// ✅ CORRECT
Fixed& operator=(Fixed const &rhs) {
    // ...
    return (*this);
}
```

### 3. Mauvais type de retour pour ++
```cpp
// ❌ ERREUR : Pré-incrémentation doit retourner référence
Fixed operator++();

// ✅ CORRECT
Fixed& operator++();
```

### 4. Confusion Pré/Post Incrémentation
```cpp
// Pré : ++a (pas de paramètre)
Fixed& operator++();

// Post : a++ (paramètre int dummy)
Fixed operator++(int);
```

### 5. Retourner une référence locale
```cpp
// ❌ DANGER !
Fixed& operator+(Fixed const &rhs) const {
    Fixed result(this->toFloat() + rhs.toFloat());
    return result;  // result est détruit en sortie de fonction !
}

// ✅ CORRECT
Fixed operator+(Fixed const &rhs) const {
    return Fixed(this->toFloat() + rhs.toFloat());
}
```

---

## 📊 Tableau Récapitulatif des Opérateurs

| Opérateur | Syntaxe | Type Retour | const? |
|-----------|---------|-------------|--------|
| `=` | `a = b` | `Fixed&` | Non |
| `+` | `a + b` | `Fixed` | Oui |
| `-` | `a - b` | `Fixed` | Oui |
| `*` | `a * b` | `Fixed` | Oui |
| `/` | `a / b` | `Fixed` | Oui |
| `==` | `a == b` | `bool` | Oui |
| `!=` | `a != b` | `bool` | Oui |
| `<` | `a < b` | `bool` | Oui |
| `>` | `a > b` | `bool` | Oui |
| `<=` | `a <= b` | `bool` | Oui |
| `>=` | `a >= b` | `bool` | Oui |
| `++` (pré) | `++a` | `Fixed&` | Non |
| `++` (post) | `a++` | `Fixed` | Non |
| `--` (pré) | `--a` | `Fixed&` | Non |
| `--` (post) | `a--` | `Fixed` | Non |

---

## 📈 Exemple Complet

```cpp
#include "Fixed.hpp"

int main() {
    Fixed a(10);
    Fixed b(5.5f);
    
    // Arithmétique
    Fixed sum = a + b;      // 15.5
    Fixed prod = a * b;     // 55
    
    // Comparaison
    if (a > b)
        std::cout << "a > b" << std::endl;
    
    // Incrémentation
    ++a;                    // a = 11
    Fixed old = b++;        // old = 5.5, b = 6.5
    
    // Min/Max
    Fixed min = Fixed::min(a, b);  // 6.5
    Fixed max = Fixed::max(a, b);  // 11
    
    // Affichage
    std::cout << "sum: " << sum << std::endl;
    std::cout << "min: " << min << std::endl;
    
    return 0;
}
```

---

## ✅ Checklist de Compréhension

Avant de passer au module suivant :

- [ ] Comprendre et implémenter l'OCF complète
- [ ] Savoir quand utiliser `const`
- [ ] Maîtriser la différence pré/post incrémentation
- [ ] Comprendre le retour par référence vs copie
- [ ] Protéger contre l'auto-assignation
- [ ] Comprendre les nombres à virgule fixe
- [ ] Savoir surcharger les opérateurs arithmétiques
- [ ] Savoir surcharger les opérateurs de comparaison
- [ ] Comprendre les décalages binaires (`<<`, `>>`)

---

## 🚀 Pour Aller Plus Loin

### Améliorations Possibles
1. **Division par zéro** : Ajouter une protection
2. **Overflow** : Détecter les dépassements de capacité
3. **Précision variable** : Template pour choisir le nombre de bits
4. **Opérateurs composés** : `+=`, `-=`, `*=`, `/=`

### Concepts Avancés
- **Move semantics** (C++11) : `Fixed(Fixed &&src)`
- **Template classes** : `template<int N> class Fixed`
- **Constexpr** : Calculs à la compilation

---

## 📚 Ressources Utiles

- [Operator Overloading](https://en.cppreference.com/w/cpp/language/operators)
- [Fixed-point arithmetic](https://en.wikipedia.org/wiki/Fixed-point_arithmetic)
- [Orthodox Canonical Form](https://www.francescmm.com/orthodox-canonical-class-form/)

---

## 🎓 Points Clés à Retenir

1. **L'OCF est OBLIGATOIRE** pour toute classe gérant des ressources
2. **Toujours protéger contre l'auto-assignation**
3. **Retourner `*this` dans operator=**
4. **Préférer const & pour les paramètres**
5. **Pré-incrémentation → référence, Post → copie**
6. **Les opérateurs de comparaison doivent être const**
7. **Virgule fixe = décalages binaires**

---

**Félicitations pour les 100/100 ! 🎉**  
**Passez maintenant au CPP_03 pour découvrir l'héritage ! 🚀**
