# CPP Module 03 - Guide Étudiant 📚

## 📊 Évaluation
**Note obtenue : À évaluer** ⭐

---

## 🎯 Objectif du Module

Ce module introduit l'**héritage** en C++, un des piliers de la programmation orientée objet :
- **L'héritage simple** (Single Inheritance)
- **L'héritage multiple** (Multiple Inheritance)
- **L'héritage virtuel** (Virtual Inheritance)
- **Le problème du diamant** (Diamond Problem)
- **Les niveaux d'accès** (public, protected, private)

## 📁 Structure du Projet

```
CPP_03/
├── ex00/          # ClapTrap - Classe de base
├── ex01/          # ScavTrap - Héritage simple
├── ex02/          # FragTrap - Héritage multiple
└── ex03/          # DiamondTrap - Héritage en diamant (virtual)
```

---

## 🤖 Exercice 00 : Aaaaand... OPEN!

### Description
Créer la classe de base `ClapTrap` qui servira pour les exercices suivants.

### Compilation et Exécution
```bash
cd ex00
make
./ClapTrap
```

### Architecture de ClapTrap

```cpp
class ClapTrap {
public:
    ClapTrap(void);
    ClapTrap(const std::string &name);
    ClapTrap(ClapTrap const &cpy);
    ClapTrap &operator=(ClapTrap const &assign);
    ~ClapTrap();
    
    void attack(const std::string &target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

private:
    std::string _name;
    int _Hit;           // 10 points de vie
    int _Energy;        // 10 points d'énergie
    int _Attack;        // 0 points d'attaque
};
```

### Attributs

| Attribut | Valeur | Description |
|----------|--------|-------------|
| `_name` | "" | Nom du ClapTrap |
| `_Hit` | 10 | Points de vie |
| `_Energy` | 10 | Points d'énergie |
| `_Attack` | 0 | Points d'attaque |

### Méthodes Principales

#### attack()
```cpp
void ClapTrap::attack(const std::string &target) {
    if (!isAlive(_Hit)) {
        std::cout << "ClapTrap " << _name << " cannot attack: no hit points.\n";
        return;
    }
    if (!hasEnergy(_Energy)) {
        std::cout << "ClapTrap " << _name << " cannot attack: no energy points.\n";
        return;
    }
    std::cout << "ClapTrap " << _name << " attacks " << target 
              << ", causing " << _Attack << " points of damage!\n";
    _Energy -= 1;  // Coûte 1 point d'énergie
}
```

#### takeDamage()
```cpp
void ClapTrap::takeDamage(unsigned int amount) {
    if (!isAlive(_Hit)) {
        std::cout << "ClapTrap " << _name << " is already at 0 HP.\n";
        return;
    }
    if (amount >= static_cast<unsigned int>(_Hit))
        _Hit = 0;
    else
        _Hit -= amount;
    std::cout << "ClapTrap " << _name << " takes " << amount << " damage!\n";
}
```

#### beRepaired()
```cpp
void ClapTrap::beRepaired(unsigned int amount) {
    std::cout << "ClapTrap " << _name << " repairs " << amount << " HP!\n";
    _Hit += amount;
    _Energy -= 1;  // Coûte 1 point d'énergie
}
```

### 🔑 Concepts Clés

#### Helpers Statiques
```cpp
static bool isAlive(unsigned int hp) {
    return (hp > 0);
}

static bool hasEnergy(unsigned int stamina) {
    return (stamina > 0);
}
```
- **`static`** : Fonctions utilitaires locales au fichier
- Pas de `this`, pas d'accès aux membres
- Évite la pollution du namespace

---

## 🛡️ Exercice 01 : Serena, my love!

### Description
Créer `ScavTrap` qui **hérite** de `ClapTrap` avec des attributs différents et une nouvelle méthode.

### Compilation et Exécution
```bash
cd ex01
make
./ScavTrap
```

### Héritage Simple

```cpp
class ScavTrap : public ClapTrap {
public:
    ScavTrap(void);
    ScavTrap(const std::string &name);
    ScavTrap(const ScavTrap &cpy);
    ScavTrap &operator=(const ScavTrap &assign);
    ~ScavTrap(void);
    
    void attack(const std::string &target);  // Redéfinition
    void guardGate();                         // Nouvelle méthode
};
```

### Attributs de ScavTrap

| Attribut | Valeur | vs ClapTrap |
|----------|--------|-------------|
| `_Hit` | 100 | 10 → **100** |
| `_Energy` | 50 | 10 → **50** |
| `_Attack` | 20 | 0 → **20** |

### 🔑 Le mot-clé `protected`

```cpp
class ClapTrap {
protected:  // ⬅️ Changement crucial !
    std::string _name;
    int _Hit;
    int _Energy;
    int _Attack;
};
```

#### Niveaux d'Accès

| Niveau | Classe | Classes Dérivées | Extérieur |
|--------|--------|------------------|-----------|
| `private` | ✅ | ❌ | ❌ |
| `protected` | ✅ | ✅ | ❌ |
| `public` | ✅ | ✅ | ✅ |

**Pourquoi `protected` ?**
- Les classes dérivées (`ScavTrap`) doivent accéder aux attributs de la base
- Mais l'extérieur ne doit pas y accéder directement

### Constructeur avec Initialisation de la Base

```cpp
ScavTrap::ScavTrap(void) : ClapTrap("NoName") {
    _Hit = 100;      // Réinitialise les valeurs
    _Energy = 50;
    _Attack = 20;
    std::cout << "ScavTrap default constructor\n";
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    _Hit = 100;
    _Energy = 50;
    _Attack = 20;
    std::cout << "ScavTrap constructor: " << _name << "\n";
}
```

**Ordre d'Appel** :
1. ✅ Constructeur de `ClapTrap` (classe de base)
2. ✅ Réassignation des attributs pour `ScavTrap`
3. ✅ Corps du constructeur `ScavTrap`

### Redéfinition de Méthode

```cpp
void ScavTrap::attack(const std::string &target) {
    if (!isAlive(_Hit)) {
        std::cout << "ScavTrap cannot attack: no hit points.\n";
        return;
    }
    if (!hasEnergy(_Energy)) {
        std::cout << "ScavTrap cannot attack: no energy.\n";
        return;
    }
    std::cout << "ScavTrap " << _name << " attacks " << target 
              << ", causing " << _Attack << " points of damage!\n";
    _Energy -= 1;
}
```

**Différence avec ClapTrap** :
- Même signature
- Comportement légèrement différent (messages)
- Utilise `_Attack = 20` au lieu de `0`

### Nouvelle Méthode Spécifique

```cpp
void ScavTrap::guardGate(void) {
    std::cout << "ScavTrap " << _name << " is now in Gate keeper mode.\n";
}
```

---

## ⚔️ Exercice 02 : Repetitive work

### Description
Créer `FragTrap` qui hérite aussi de `ClapTrap` avec des attributs encore différents.

### Compilation et Exécution
```bash
cd ex02
make
./FragTrap
```

### Architecture

```cpp
class FragTrap : public ClapTrap {
public:
    FragTrap(void);
    FragTrap(const std::string &name);
    FragTrap(const FragTrap &cpy);
    FragTrap &operator=(const FragTrap &assign);
    ~FragTrap(void);
    
    void attack(const std::string &target);
    void highFivesGuys(void);
};
```

### Attributs de FragTrap

| Attribut | ClapTrap | ScavTrap | FragTrap |
|----------|----------|----------|----------|
| `_Hit` | 10 | 100 | **100** |
| `_Energy` | 10 | 50 | **100** |
| `_Attack` | 0 | 20 | **30** |

### Hiérarchie d'Héritage

```
        ClapTrap
         /    \
        /      \
   ScavTrap  FragTrap
```

Deux classes indépendantes héritent de la même base.

---

## 💎 Exercice 03 : Now it's weird!

### Description
Créer `DiamondTrap` qui hérite **à la fois** de `ScavTrap` et `FragTrap`. C'est le fameux **problème du diamant** !

### Compilation et Exécution
```bash
cd ex03
make
./DiamondTrap
```

### Le Problème du Diamant

#### Sans Héritage Virtuel (❌ PROBLÈME)

```
        ClapTrap
         /    \
        /      \
   ScavTrap  FragTrap
        \      /
         \    /
      DiamondTrap
```

**Problème** : `DiamondTrap` hérite de **2 instances** de `ClapTrap` !
- Duplication des attributs `_name`, `_Hit`, etc.
- Ambiguïté : quel `_name` utiliser ?

#### Avec Héritage Virtuel (✅ SOLUTION)

```cpp
// Dans ScavTrap.hpp
class ScavTrap : virtual public ClapTrap { ... };

// Dans FragTrap.hpp  
class FragTrap : virtual public ClapTrap { ... };

// Dans DiamondTrap.hpp
class DiamondTrap : public ScavTrap, public FragTrap { ... };
```

```
        ClapTrap (virtual)
         /    \
        /      \
   ScavTrap  FragTrap
   (virtual) (virtual)
        \      /
         \    /
      DiamondTrap
```

**Solution** : Une **seule** instance de `ClapTrap` partagée !

### Implémentation de DiamondTrap

#### Déclaration
```cpp
class DiamondTrap : public ScavTrap, public FragTrap {
public:
    DiamondTrap(void);
    DiamondTrap(const std::string &name);
    DiamondTrap(const DiamondTrap &cpy);
    DiamondTrap &operator=(const DiamondTrap &assign);
    ~DiamondTrap(void);
    
    void attack(const std::string &target);
    void whoAmI();

private:
    std::string _name;  // Shadow ClapTrap::_name
};
```

#### Constructeur avec Double Nom

```cpp
DiamondTrap::DiamondTrap(const std::string &name)
: ClapTrap(name + "_clap_name")  // Nom de ClapTrap
, ScavTrap(name)
, FragTrap(name)
, _name(name)                     // Nom propre de DiamondTrap
{
    _Hit = 100;      // De FragTrap
    _Energy = 50;    // De ScavTrap
    _Attack = 30;    // De FragTrap
    std::cout << "DiamondTrap constructor: " << _name << "\n";
}
```

**Spécificités** :
- `ClapTrap::_name` → `"Bob_clap_name"`
- `DiamondTrap::_name` → `"Bob"`
- Attributs mixtes des deux parents

#### La Méthode whoAmI()

```cpp
void DiamondTrap::whoAmI() {
    std::cout << "DiamondTrap name: " << _name 
              << ", ClapTrap name: " << this->ClapTrap::_name << "\n";
}
```

**Résolution d'ambiguïté** :
- `_name` → Attribut de `DiamondTrap`
- `ClapTrap::_name` → Qualification explicite

#### Utilisation de la Méthode Parente

```cpp
void DiamondTrap::attack(const std::string &target) {
    ScavTrap::attack(target);  // Utilise l'attaque de ScavTrap
}
```

---

## 🔑 Concepts C++ Avancés du Module

### 1. Héritage : Syntaxe

```cpp
class Derived : [access_specifier] Base {
    // ...
};
```

#### Spécificateurs d'Accès

| Héritage | `public` Base | `protected` Base | `private` Base |
|----------|---------------|------------------|----------------|
| **public** | public → public<br>protected → protected | protected → protected<br>public → protected | private → private<br>tout inaccessible |
| **protected** | public → protected<br>protected → protected | Tout protected | Tout private |
| **private** | public → private<br>protected → private | Tout private | Tout private |

**Règle générale** : Utilisez **toujours** `public` pour l'héritage "est-un".

### 2. Ordre de Construction/Destruction

#### Construction
```
1. Classe de Base (ClapTrap)
2. Classes Intermédiaires (ScavTrap, FragTrap)
3. Classe Dérivée (DiamondTrap)
```

#### Destruction (inverse)
```
1. Classe Dérivée (DiamondTrap)
2. Classes Intermédiaires (FragTrap, ScavTrap)
3. Classe de Base (ClapTrap)
```

### 3. Héritage Virtuel en Détail

#### Sans `virtual`
```cpp
class ScavTrap : public ClapTrap { };
class FragTrap : public ClapTrap { };
class DiamondTrap : public ScavTrap, public FragTrap { };

// Résultat :
// DiamondTrap
//   ├─ ScavTrap
//   │   └─ ClapTrap (1ère instance)
//   └─ FragTrap
//       └─ ClapTrap (2ème instance)  ❌ DOUBLON !
```

#### Avec `virtual`
```cpp
class ScavTrap : virtual public ClapTrap { };
class FragTrap : virtual public ClapTrap { };
class DiamondTrap : public ScavTrap, public FragTrap { };

// Résultat :
// DiamondTrap
//   ├─ ScavTrap ┐
//   └─ FragTrap ├─> ClapTrap (unique instance partagée) ✅
```

### 4. Appel des Constructeurs avec Virtual

```cpp
DiamondTrap::DiamondTrap(const std::string &name)
: ClapTrap(name + "_clap_name")  // ⬅️ OBLIGATOIRE avec virtual !
, ScavTrap(name)
, FragTrap(name)
, _name(name)
{
    // ...
}
```

**IMPORTANT** :
- Avec héritage virtuel, la classe **la plus dérivée** doit initialiser la base virtuelle
- Sinon, constructeur par défaut de `ClapTrap` sera appelé

### 5. Shadowing d'Attributs

```cpp
class ClapTrap {
protected:
    std::string _name;  // Nom de ClapTrap
};

class DiamondTrap : public ScavTrap, public FragTrap {
private:
    std::string _name;  // Cache (shadow) ClapTrap::_name
};
```

**Accès** :
```cpp
_name                   // DiamondTrap::_name
this->_name             // DiamondTrap::_name
ClapTrap::_name         // ClapTrap::_name (explicite)
this->ClapTrap::_name   // ClapTrap::_name (explicite)
```

---

## 📊 Tableau Comparatif des Classes

| Classe | HP | Energy | Attack | Méthodes Spéciales |
|--------|----|----|--------|-------------------|
| `ClapTrap` | 10 | 10 | 0 | - |
| `ScavTrap` | 100 | 50 | 20 | `guardGate()` |
| `FragTrap` | 100 | 100 | 30 | `highFivesGuys()` |
| `DiamondTrap` | 100 | 50 | 30 | `whoAmI()` |

---

## 🎯 Exemple Complet

```cpp
int main() {
    // ClapTrap de base
    ClapTrap clap("Clappy");
    clap.attack("target");      // 0 dégâts
    clap.takeDamage(5);
    clap.beRepaired(3);
    
    // ScavTrap (héritage simple)
    ScavTrap scav("Scavy");
    scav.attack("enemy");       // 20 dégâts
    scav.guardGate();           // Mode gardien
    
    // FragTrap
    FragTrap frag("Fraggy");
    frag.attack("monster");     // 30 dégâts
    frag.highFivesGuys();       // High five !
    
    // DiamondTrap (héritage multiple + virtuel)
    DiamondTrap diamond("Diamondy");
    diamond.attack("boss");     // Utilise ScavTrap::attack()
    diamond.whoAmI();           // Affiche les deux noms
    diamond.guardGate();        // Hérité de ScavTrap
    diamond.highFivesGuys();    // Hérité de FragTrap
    
    return 0;
}
```

**Output** :
```
ClapTrap Clappy attacks target, causing 0 points of damage!
ClapTrap Clappy takes 5 damage!
ClapTrap Clappy repairs 3 HP!

ScavTrap Scavy attacks enemy, causing 20 points of damage!
ScavTrap Scavy is now in Gate keeper mode.

FragTrap Fraggy attacks monster, causing 30 points of damage!
FragTrap Fraggy: High fives guys!

DiamondTrap Diamondy attacks boss, causing 20 points of damage!
DiamondTrap name: Diamondy, ClapTrap name: Diamondy_clap_name
ScavTrap Diamondy is now in Gate keeper mode.
FragTrap Diamondy: High fives guys!
```

---

## 🛡️ Bonnes Pratiques

### 1. Utiliser `protected` pour l'Héritage
```cpp
class Base {
protected:  // ✅ Accessible aux dérivées
    int _value;
};
```

### 2. Toujours Initialiser la Base
```cpp
Derived::Derived() : Base() {  // ✅ Explicite
    // ...
}
```

### 3. Appeler operator= de la Base
```cpp
Derived& Derived::operator=(const Derived &rhs) {
    if (this != &rhs) {
        Base::operator=(rhs);  // ✅ Ne pas oublier !
        // ... attributs propres ...
    }
    return *this;
}
```

### 4. Virtual pour l'Héritage Multiple
```cpp
// ✅ CORRECT pour éviter le problème du diamant
class ScavTrap : virtual public ClapTrap { };
class FragTrap : virtual public ClapTrap { };
```

### 5. Messages de Debug
```cpp
ScavTrap::ScavTrap() {
    std::cout << "ScavTrap constructor\n";  // ✅ Aide au debug
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap destructor\n";   // ✅ Vérifier l'ordre
}
```

---

## 🐛 Erreurs Courantes

### 1. Oublier `protected`
```cpp
// ❌ ERREUR
class ClapTrap {
private:
    int _Hit;  // Inaccessible aux dérivées !
};

// ✅ CORRECT
class ClapTrap {
protected:
    int _Hit;  // Accessible aux dérivées
};
```

### 2. Ne pas appeler le constructeur de base
```cpp
// ❌ ERREUR
ScavTrap::ScavTrap(const std::string &name) {
    _name = name;  // _name pas initialisé !
}

// ✅ CORRECT
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    // ...
}
```

### 3. Oublier `virtual` pour le diamant
```cpp
// ❌ PROBLÈME : Duplication de ClapTrap
class ScavTrap : public ClapTrap { };
class FragTrap : public ClapTrap { };

// ✅ SOLUTION
class ScavTrap : virtual public ClapTrap { };
class FragTrap : virtual public ClapTrap { };
```

### 4. Ambiguïté non résolue
```cpp
DiamondTrap d;
d.attack("target");  // ❌ Ambiguïté : quelle attack() ?

// ✅ Solution 1 : Redéfinir dans DiamondTrap
void DiamondTrap::attack(const std::string &target) {
    ScavTrap::attack(target);
}

// ✅ Solution 2 : Qualifier l'appel
d.ScavTrap::attack("target");
```

### 5. Oublier d'initialiser la base virtuelle
```cpp
// ❌ ERREUR
DiamondTrap::DiamondTrap(const std::string &name)
: ScavTrap(name), FragTrap(name)  // ClapTrap pas initialisé !
{
    // ...
}

// ✅ CORRECT
DiamondTrap::DiamondTrap(const std::string &name)
: ClapTrap(name + "_clap_name")  // OBLIGATOIRE !
, ScavTrap(name), FragTrap(name)
{
    // ...
}
```

---

## 📈 Diagrammes UML

### ex00 : ClapTrap seul
```
┌──────────────────┐
│    ClapTrap      │
├──────────────────┤
│ - _name: string  │
│ - _Hit: int      │
│ - _Energy: int   │
│ - _Attack: int   │
├──────────────────┤
│ + attack()       │
│ + takeDamage()   │
│ + beRepaired()   │
└──────────────────┘
```

### ex01 : Héritage simple
```
┌──────────────────┐
│    ClapTrap      │
└────────┬─────────┘
         │
         │ inherits
         │
┌────────▼─────────┐
│    ScavTrap      │
├──────────────────┤
│ + guardGate()    │
└──────────────────┘
```

### ex03 : Diamant virtuel
```
        ┌──────────────────┐
        │    ClapTrap      │
        └────────┬─────────┘
                 │ virtual
         ┌───────┴───────┐
         │               │
┌────────▼─────┐  ┌──────▼───────┐
│  ScavTrap    │  │   FragTrap   │
└────────┬─────┘  └──────┬───────┘
         │               │
         └───────┬───────┘
                 │
        ┌────────▼─────────┐
        │  DiamondTrap     │
        └──────────────────┘
```

---

## ✅ Checklist de Compréhension

Avant de passer au module suivant :

- [ ] Comprendre l'héritage simple
- [ ] Savoir utiliser `protected`
- [ ] Maîtriser l'ordre de construction/destruction
- [ ] Comprendre le problème du diamant
- [ ] Savoir utiliser `virtual` pour l'héritage
- [ ] Résoudre les ambiguïtés (qualification)
- [ ] Initialiser correctement les bases virtuelles
- [ ] Appeler les opérateurs des classes parentes
- [ ] Comprendre le shadowing d'attributs

---

## 🚀 Pour Aller Plus Loin

### Polymorphisme (CPP_04)
L'héritage seul ne suffit pas. Le vrai pouvoir vient avec le **polymorphisme** :
```cpp
ClapTrap *ptr = new ScavTrap("Scavy");
ptr->attack("enemy");  // Appelle quelle version ? 🤔
// → Réponse dans CPP_04 avec virtual !
```

### Concepts Avancés
- **Destructeurs virtuels** (crucial !)
- **Méthodes virtuelles pures** (classes abstraites)
- **Interfaces** en C++
- **RTTI** (Run-Time Type Information)

---

## 📚 Ressources Utiles

- [C++ Inheritance](https://en.cppreference.com/w/cpp/language/derived_class)
- [Virtual Inheritance](https://en.cppreference.com/w/cpp/language/derived_class#Virtual_base_classes)
- [Diamond Problem](https://en.wikipedia.org/wiki/Multiple_inheritance#The_diamond_problem)

---

## 🎓 Points Clés à Retenir

1. **`protected`** permet l'accès aux classes dérivées
2. **Toujours initialiser la classe de base** dans le constructeur
3. **`virtual`** pour éviter les duplications dans l'héritage multiple
4. **Ordre de construction** : Base → Dérivée
5. **Ordre de destruction** : Dérivée → Base (inverse)
6. **Qualifier explicitement** pour résoudre les ambiguïtés
7. **La classe la plus dérivée** initialise les bases virtuelles
8. **Ne pas oublier** d'appeler `Base::operator=()` dans les dérivées

---

**Préparez-vous pour CPP_04 où vous découvrirez le polymorphisme et les destructeurs virtuels ! 🚀**
