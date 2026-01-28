# CPP Module 05 - Repetition and Exceptions

<div align="center">

![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)

**Maîtriser les exceptions en C++ à travers un système bureaucratique**

[Aperçu](#aperçu) •
[Structure](#structure) •
[Exercices](#exercices) •
[Compilation](#compilation) •
[Concepts](#concepts-clés) •
[Utilisation](#utilisation)

</div>

---

## 📋 Aperçu

Le module CPP_05 est centré sur l'apprentissage approfondi des **exceptions en C++98**. À travers la métaphore d'un système bureaucratique, ce projet explore la gestion d'erreurs, l'héritage, le polymorphisme et les classes abstraites.

### 🎯 Objectifs Pédagogiques

- ✅ Comprendre et implémenter le système d'exceptions C++
- ✅ Maîtriser les blocs `try`, `catch` et `throw`
- ✅ Créer des classes d'exception personnalisées
- ✅ Utiliser l'héritage avec `std::exception`
- ✅ Implémenter des classes abstraites et virtuelles pures
- ✅ Gérer le polymorphisme avec des pointeurs de base

---

## 📁 Structure du Projet

```
CPP_05/
│
├── ex00/                        # Bureaucrat de base
│   ├── includes/
│   │   └── Bureaucrat.hpp
│   ├── srcs/
│   │   ├── Bureaucrat.cpp
│   │   └── main.cpp
│   └── Makefile
│
├── ex01/                        # Ajout des formulaires
│   ├── includes/
│   │   ├── Bureaucrat.hpp
│   │   └── Form.hpp
│   ├── srcs/
│   │   ├── Bureaucrat.cpp
│   │   ├── Form.cpp
│   └── main.cpp
│
├── ex02/                        # Formulaires spécialisés
│   ├── includes/
│   │   ├── AForm.hpp
│   │   ├── Bureaucrat.hpp
│   │   ├── PresidentialPardonForm.hpp
│   │   ├── RobotomyRequestForm.hpp
│   │   └── ShrubberyCreationForm.hpp
│   ├── srcs/
│   │   ├── AForm.cpp
│   │   ├── Bureaucrat.cpp
│   │   ├── PresidentialPardonForm.cpp
│   │   ├── RobotomyRequestForm.cpp
│   │   └── ShrubberyCreationForm.cpp
│   └── main.cpp
│
└── ex03/                        # Factory Pattern (Intern)
    ├── includes/
    │   ├── AForm.hpp
    │   ├── Bureaucrat.hpp
    │   ├── Intern.hpp
    │   ├── PresidentialPardonForm.hpp
    │   ├── RobotomyRequestForm.hpp
    │   └── ShrubberyCreationForm.hpp
    ├── srcs/
    │   ├── AForm.cpp
    │   ├── Bureaucrat.cpp
    │   ├── Intern.cpp
    │   ├── PresidentialPardonForm.cpp
    │   ├── RobotomyRequestForm.cpp
    │   └── ShrubberyCreationForm.cpp
    └── main.cpp
```

---

## 🎓 Exercices Détaillés

### 📝 Ex00: Bureaucrat

**Premier contact avec les exceptions**

#### Caractéristiques
- Classe `Bureaucrat` avec nom (constant) et grade (1-150)
- Grade 1 = meilleur, 150 = pire
- Exceptions personnalisées :
  - `GradeTooHighException` : grade < 1
  - `GradeTooLowException` : grade > 150
- Méthodes `increment()` et `decrement()` sécurisées
- Surcharge de l'opérateur `<<` pour l'affichage

#### Concepts Clés
```cpp
class Bureaucrat {
    class GradeTooHighException : public std::exception {
        const char* what() const throw() {
            return "Grade too high";
        }
    };
    // ...
};
```

---

### 📄 Ex01: Form

**Introduction des formulaires à signer**

#### Caractéristiques
- Classe `Form` avec :
  - Nom (constant)
  - Statut de signature (booléen)
  - Grade requis pour signer
  - Grade requis pour exécuter
- Méthode `beSigned()` pour qu'un bureaucrate signe
- Méthode `signForm()` dans Bureaucrat pour gérer les erreurs
- Forward declaration pour éviter les inclusions circulaires

#### Validation
```cpp
bool Form::beSigned(const Bureaucrat& instance) {
    if (instance.getGrade() > _requiredGrade)
        throw GradeTooLowException();
    _signed = true;
    return true;
}
```

---

### 🎨 Ex02: Concrete Forms

**Polymorphisme et classes abstraites**

#### Trois Types de Formulaires

| Formulaire | Grade Signature | Grade Exécution | Action |
|------------|----------------|-----------------|--------|
| **ShrubberyCreationForm** | 145 | 137 | Crée un fichier avec un arbre ASCII |
| **RobotomyRequestForm** | 72 | 45 | Robotomise la cible (50% chance) |
| **PresidentialPardonForm** | 25 | 5 | Pardonne la cible par Zaphod Beeblebrox |

#### Hiérarchie de Classes
```
        std::exception
              ↑
              |
          AForm (abstract)
         /     |     \
        /      |      \
Shrubbery  Robotomy  Presidential
```

#### Classe Abstraite AForm
- Méthode virtuelle pure : `virtual void executeAction() const = 0`
- Méthode `execute()` vérifie signature et grade avant exécution
- Exception `FormNotSignedException` si non signé

---

### 🏭 Ex03: Intern (Factory Pattern)

**Pattern de création d'objets**

#### Le Stagiaire (Intern)
- Crée des formulaires dynamiquement par leur nom
- Méthode `makeForm(formName, target)` retourne `AForm*`
- Gère les noms invalides avec une exception

#### Utilisation
```cpp
Intern someRandomIntern;
AForm* rrf;

rrf = someRandomIntern.makeForm("robotomy request", "Bender");
// Intern creates robotomy request
```

#### Implémentation Élégante
Utilise un tableau de pointeurs sur fonctions ou une structure de mapping pour éviter les multiples `if/else`.

---

## 🔧 Compilation

### Prérequis
- Compilateur C++ compatible C++98
- Make
- Système Linux/Unix

### Compiler un Exercice
```bash
# Ex00
cd ex00
make
./Bureaucrat

# Ex01
cd ex01
make
./Bureaucrat_Form

# Ex02
cd ex02
make
./28B_Not_28C

# Ex03
cd ex03
make
./Intern
```

### Flags de Compilation
```makefile
FLAGS = -std=c++98 -Wall -Wextra -Werror
```

### Commandes Make
```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime tout (objets + exécutable)
make re     # Recompile tout
```

---

## 💡 Concepts Clés

### 1️⃣ Exceptions en C++

#### Définition
Mécanisme de gestion d'erreurs qui transfère le contrôle à un gestionnaire d'erreurs.

#### Structure
```cpp
try {
    // Code susceptible de lancer une exception
    throw MyException();
}
catch (const std::exception& e) {
    // Gestion de l'erreur
    std::cerr << e.what() << std::endl;
}
```

#### Bonnes Pratiques
- ✅ Hériter de `std::exception`
- ✅ Implémenter `what()` avec `throw()`
- ✅ Attraper par référence constante
- ✅ Lancer aux bons moments (constructeur, validation)

### 2️⃣ Classes Abstraites

#### Définition
Classe contenant au moins une méthode virtuelle pure (`= 0`).

#### Caractéristiques
- ❌ Ne peut pas être instanciée
- ✅ Sert de classe de base
- ✅ Définit une interface commune
- ✅ Force l'implémentation dans les classes dérivées

```cpp
class AForm {
protected:
    virtual void executeAction() const = 0;  // Virtuelle pure
public:
    void execute() const {
        // Logique commune
        executeAction();  // Appel polymorphique
    }
};
```

### 3️⃣ Polymorphisme

#### Utilisation
```cpp
AForm* form = new PresidentialPardonForm("target");
form->execute(bureaucrat);  // Appelle la méthode de PresidentialPardonForm
delete form;
```

#### Destructeur Virtuel
**OBLIGATOIRE** pour éviter les fuites mémoire :
```cpp
virtual ~AForm();
```

### 4️⃣ Forward Declaration

#### Problème : Dépendance Circulaire
```
Bureaucrat.hpp inclut Form.hpp
Form.hpp inclut Bureaucrat.hpp  ❌
```

#### Solution
```cpp
// Dans Form.hpp
class Bureaucrat;  // Forward declaration

class Form {
    bool beSigned(const Bureaucrat& instance);
};
```

### 5️⃣ Const Correctness

#### Méthodes Constantes
```cpp
int getGrade() const;  // Ne modifie pas l'objet
```

#### Attributs Constants
```cpp
const std::string _name;  // Initialisé dans le constructeur
```

---

## 🚀 Utilisation

### Exemple Ex00
```cpp
try {
    Bureaucrat bob("Bob", 2);
    std::cout << bob;  // Bob bureaucrate grade : 2
    
    bob.increment();   // Grade devient 1
    bob.increment();   // Exception!
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

### Exemple Ex01
```cpp
Bureaucrat john("John", 50);
Form taxForm("Tax Form", 45, 30);

john.signForm(taxForm);  // John couldn't sign Tax Form because Grade too low

Bureaucrat boss("Boss", 1);
boss.signForm(taxForm);  // Boss signed Tax Form
```

### Exemple Ex02
```cpp
Bureaucrat ceo("CEO", 1);
ShrubberyCreationForm shrubbery("home");

ceo.signForm(shrubbery);
ceo.executeForm(shrubbery);
// Crée home_shrubbery avec un arbre ASCII
```

### Exemple Ex03
```cpp
Intern intern;
AForm* form;

form = intern.makeForm("presidential pardon", "Marvin");
// Intern creates presidential pardon

Bureaucrat president("President", 1);
president.signForm(*form);
president.executeForm(*form);
// Marvin has been pardoned by Zaphod Beeblebrox

delete form;
```

---

## 📊 Diagramme de Classes (Ex02/Ex03)

```
┌─────────────────────┐
│   std::exception    │
└──────────┬──────────┘
           │ inherits
           │
┌──────────▼──────────────────────────────────────┐
│                 AForm (abstract)                 │
├──────────────────────────────────────────────────┤
│ - _name: const string                            │
│ - _signed: bool                                  │
│ - _requiredGrade: int                            │
│ - _executeGrade: int                             │
├──────────────────────────────────────────────────┤
│ + beSigned(Bureaucrat): bool                     │
│ + execute(Bureaucrat): void                      │
│ # executeAction(): void = 0  [pure virtual]      │
└─────────────┬────────────────────────────────────┘
              │
     ┌────────┴────────┬────────────────┐
     │                 │                │
┌────▼─────┐  ┌────────▼─────┐  ┌──────▼──────┐
│Shrubbery │  │  Robotomy    │  │Presidential │
│  Form    │  │    Form      │  │    Form     │
└──────────┘  └──────────────┘  └─────────────┘

┌──────────────────────┐
│     Bureaucrat       │
├──────────────────────┤
│ - _name: const string│
│ - _grade: int        │
├──────────────────────┤
│ + signForm(Form&)    │
│ + executeForm(Form&) │
└──────────────────────┘

┌──────────────────────┐
│       Intern         │
├──────────────────────┤
│ + makeForm(): AForm* │
└──────────────────────┘
```

---

## ⚠️ Pièges Courants

### 1. Oubli du Destructeur Virtuel
```cpp
// ❌ FAUX
class AForm {
    ~AForm();
};

// ✅ CORRECT
class AForm {
    virtual ~AForm();
};
```

### 2. Exception Non Capturée
```cpp
// ❌ FAUX - Programme crash
Bureaucrat bob("Bob", 151);

// ✅ CORRECT
try {
    Bureaucrat bob("Bob", 151);
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

### 3. Fuite Mémoire avec Pointeurs
```cpp
// ❌ FAUX
AForm* form = intern.makeForm("robotomy", "target");
// ... utilisation ...
// Oubli du delete !

// ✅ CORRECT
AForm* form = intern.makeForm("robotomy", "target");
delete form;
```

### 4. Grade Inversé
```cpp
// ❌ Attention ! 1 = meilleur, 150 = pire
if (grade > _requiredGrade)  // ✅ Bon sens
    throw GradeTooLowException();
```

---

## 📚 Ressources Utiles

### Documentation C++
- [cppreference.com - Exceptions](https://en.cppreference.com/w/cpp/language/exceptions)
- [cppreference.com - std::exception](https://en.cppreference.com/w/cpp/error/exception)
- [LearnCpp - Exception Handling](https://www.learncpp.com/cpp-tutorial/basic-exception-handling/)

### Concepts Avancés
- **RAII** (Resource Acquisition Is Initialization)
- **Exception Safety** (Basic, Strong, No-throw)
- **Factory Pattern** (Design Pattern)
- **Template Method Pattern** (executeAction)

---

## 🎯 Points d'Attention pour l'Évaluation

### Checklist Obligatoire

- [ ] **Compilation** : `-Wall -Wextra -Werror -std=c++98`
- [ ] **Forme canonique** : Constructeur par défaut, destructeur, constructeur de copie, opérateur d'affectation
- [ ] **Pas de fuite mémoire** : Vérifier avec `valgrind`
- [ ] **Exceptions** : Toutes héritent de `std::exception`
- [ ] **Const correctness** : Méthodes et paramètres appropriés
- [ ] **Destructeur virtuel** : Dans toutes les classes de base
- [ ] **Tests complets** : Cas nominaux et cas d'erreur

### Tests Suggérés

#### Ex00
- ✅ Création avec grade valide (1, 75, 150)
- ✅ Création avec grade invalide (0, 151)
- ✅ Incrémentation/décrémentation aux limites
- ✅ Affichage avec operator<<

#### Ex01
- ✅ Création de Form avec grades valides/invalides
- ✅ Signature par bureaucrate avec grade suffisant/insuffisant
- ✅ Affichage du statut de signature

#### Ex02
- ✅ Exécution sans signature (FormNotSignedException)
- ✅ Exécution avec grade insuffisant
- ✅ Exécution réussie de chaque type de formulaire
- ✅ Création du fichier pour ShrubberyCreationForm
- ✅ Aléatoire pour RobotomyRequestForm

#### Ex03
- ✅ Création de formulaires par nom (valide/invalide)
- ✅ Vérification du polymorphisme
- ✅ Pas de fuite mémoire avec les formulaires créés

---

## 🏆 Barème de Notation

| Critère | Points |
|---------|--------|
| Ex00 - Bureaucrat | 20 |
| Ex01 - Form | 25 |
| Ex02 - Concrete classes | 30 |
| Ex03 - Intern | 25 |
| **TOTAL** | **100** |

### Bonus Potentiels
- Tests exhaustifs dans main.cpp
- Gestion d'erreurs robuste
- Code propre et bien commenté
- Utilisation avancée de const

---

## 👨‍💻 Auteur

**Projet réalisé dans le cadre du cursus 42**

- Circle 5 - CPP Module 05
- Standard C++98
- Focus : Exceptions et Classes Abstraites

---

## 📝 Notes de Développement

### Choix d'Implémentation

#### Grades 1-150
Le choix de 1 comme meilleur grade est contre-intuitif mais respecte le sujet. Attention aux comparaisons !

#### Protected vs Private
`executeAction()` est `protected` pour permettre l'accès aux classes dérivées tout en masquant l'implémentation.

#### Return des Getters
`getName()` retourne `std::string` (copie) pour éviter les modifications non désirées, bien que `const std::string&` soit plus efficace.

### Optimisations Possibles
- Utilisation de `const std::string&` pour les retours de chaînes
- Smart pointers (C++11+) pour éviter les `delete` manuels
- Exception avec messages personnalisés incluant le grade

---

<div align="center">

**Made with ☕ and 🧠 at 42 School**

⭐ Si ce README vous a aidé, n'oubliez pas de partager ! ⭐

</div>
