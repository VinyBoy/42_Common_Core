# CPP Module 01 - Guide Étudiant 📚

## 📊 Évaluation
**Note obtenue : 100/100** 🏆

---

## 🎯 Objectif du Module

Ce module approfondit la gestion de la mémoire en C++ avec un focus sur :
- L'allocation dynamique (heap vs stack)
- Les pointeurs et les références
- Les différences entre `new` et `delete`
- Les fuites mémoires et leur prévention
- Les pointeurs vers fonctions membres

## 📁 Structure du Projet

```
CPP_01/
├── ex00/          # Zombie - BraiiiiiiinnnzzzZ
├── ex01/          # ZombieHorde - Allocation de tableaux
├── ex02/          # Hi This is Brain - Pointeurs vs Références
├── ex03/          # Unnecessary Violence - Armes et humains
├── ex04/          # Sed is for losers - Remplacement de chaînes
├── ex05/          # Harl 2.0 - Pointeurs vers méthodes membres
└── ex06/          # HarlFilter - Switch case avec fall-through
```

---

## 🧟 Exercice 00 : BraiiiiiiinnnzzzZ

### Description
Comprendre la différence entre allocation sur la **stack** et sur le **heap**.

### Compilation et Exécution
```bash
cd ex00
make
./Zombie "ZombieName"
```

### Concepts Clés

#### 1. Allocation sur le Heap (tas)
```cpp
Zombie* newZombie(std::string name) {
    Zombie *zombie = new Zombie();  // Allocation dynamique
    zombie->SetName(name);
    return zombie;                   // Le zombie survit à la fonction
}
```
- ✅ Le zombie existe jusqu'à `delete`
- ✅ Peut être retourné par une fonction
- ❌ **Doit être libéré manuellement** avec `delete`

#### 2. Allocation sur la Stack (pile)
```cpp
void randomChump(std::string name) {
    Zombie zombie;                   // Allocation automatique
    zombie.SetName(name);
    zombie.annonce();
}                                     // Zombie détruit automatiquement ici
```
- ✅ Destruction automatique à la fin du scope
- ✅ Pas de risque de fuite mémoire
- ❌ Ne peut pas survivre à la fonction

### Quand utiliser quoi ?

| Stack | Heap |
|-------|------|
| Durée de vie courte | Durée de vie longue |
| Taille connue à la compilation | Taille dynamique |
| Rapide | Plus lent |
| Automatique | Manuel (`new`/`delete`) |

### Protection contre bad_alloc
```cpp
try { 
    newZombie = new Zombie();
}
catch (const std::bad_alloc&) {
    std::cout << "Erreur d'allocation mémoire\n";
    return 1;
}
```

---

## 🧟‍♂️ Exercice 01 : Moar brainz!

### Description
Créer une horde de N zombies alloués en **un seul bloc** sur le heap.

### Compilation et Exécution
```bash
cd ex01
make
./ZombieHorde 5 "Walker"
```

### Allocation de Tableau
```cpp
Zombie* zombieHorde(int N, std::string name) {
    Zombie *horde = new Zombie[N];    // Tableau dynamique
    
    for (int i = 0; i < N; i++) {
        horde[i].setName(name);
        horde[i].annonce();
    }
    
    return horde;
}
```

### ⚠️ Libération Cruciale
```cpp
Zombie *horde = zombieHorde(5, "Walker");
// ... utilisation ...
delete[] horde;  // OBLIGATOIRE : delete[] pour les tableaux !
```

**IMPORTANT** :
- `new` → `delete`
- `new[]` → `delete[]`

Ne **JAMAIS** mélanger :
- ❌ `new[]` avec `delete` → Comportement indéfini
- ❌ `new` avec `delete[]` → Comportement indéfini

---

## 🧠 Exercice 02 : HI THIS IS BRAIN

### Description
Comprendre la différence fondamentale entre **pointeurs** et **références**.

### Compilation et Exécution
```bash
cd ex02
make
./Hi_This_is_brain
```

### Code Principal
```cpp
std::string temp = "HI THIS IS BRAIN";
std::string* stringPTR = &temp;      // Pointeur
std::string& stringREF = temp;       // Référence
```

### Comparaison Pointeur vs Référence

| Aspect | Pointeur | Référence |
|--------|----------|-----------|
| **Syntaxe** | `*` | `&` |
| **Initialisation** | Peut être NULL | Doit être initialisée |
| **Réassignation** | ✅ Oui | ❌ Non (alias permanent) |
| **Déréférencement** | Explicite `*ptr` | Implicite |
| **Arithmétique** | ✅ Oui | ❌ Non |
| **Sécurité** | Peut être dangereux | Plus sûr |

### Exemple Détaillé
```cpp
// Adresses mémoires
std::cout << &temp;        // 0x7ffd1234abcd
std::cout << stringPTR;    // 0x7ffd1234abcd (même adresse)
std::cout << &stringREF;   // 0x7ffd1234abcd (même adresse)

// Valeurs
std::cout << temp;         // HI THIS IS BRAIN
std::cout << *stringPTR;   // HI THIS IS BRAIN (déréférencement)
std::cout << stringREF;    // HI THIS IS BRAIN (automatique)
```

### 💡 Règle de Base
- Préférez les **références** quand c'est possible (plus sûr)
- Utilisez les **pointeurs** quand vous avez besoin de :
  - Réassignation
  - Possibilité de NULL
  - Arithmétique de pointeur

---

## ⚔️ Exercice 03 : Unnecessary violence

### Description
Différencier les références et pointeurs dans un contexte pratique avec des armes et des humains.

### Compilation et Exécution
```bash
cd ex03
make
./Unnecessary_violence
```

### Architecture

#### Classe Weapon
```cpp
class Weapon {
private:
    std::string _type;
public:
    Weapon(const std::string weapon);
    const std::string& getType() const;
    void setType(std::string type);
};
```

#### HumanA - Référence (toujours armé)
```cpp
class HumanA {
private:
    std::string _name;
    Weapon& _weapon;  // Référence : TOUJOURS initialisée
public:
    HumanA(const std::string name, Weapon &type);
    void attack();
};
```

**Pourquoi une référence ?**
- ✅ HumanA a **toujours** une arme
- ✅ L'arme doit être fournie à la construction
- ✅ Impossible d'être sans arme

#### HumanB - Pointeur (peut être désarmé)
```cpp
class HumanB {
private:
    std::string _name;
    Weapon* _weapon;  // Pointeur : Peut être NULL
public:
    HumanB(const std::string name);
    void setWeapon(Weapon &type);
    void attack();
};
```

**Pourquoi un pointeur ?**
- ✅ HumanB peut être créé **sans** arme
- ✅ L'arme peut être assignée plus tard
- ✅ Peut vérifier si l'arme existe avant d'attaquer

### Exemple d'utilisation
```cpp
// HumanA : Arme obligatoire dès la construction
Weapon club("crude spiked club");
HumanA bob("Bob", club);
bob.attack();  // Bob a toujours une arme

// HumanB : Arme optionnelle
HumanB jim("Jim");
jim.attack();           // Affiche qu'il n'a pas d'arme
jim.setWeapon(club);    // Maintenant il en a une
jim.attack();           // Jim peut attaquer
```

### Gestion des Cas Limites
```cpp
void HumanB::attack() {
    if (_weapon == 0 || _weapon->getType().empty())
        std::cout << _name << " has no weapon!\n";
    else
        std::cout << _name << " attacks with " << _weapon->getType() << "\n";
}
```

### 🎓 Leçon Importante
**Utilisez une référence quand l'objet DOIT exister.**  
**Utilisez un pointeur quand l'objet PEUT ne pas exister.**

---

## 📝 Exercice 04 : Sed is for losers

### Description
Remplacer toutes les occurrences d'une chaîne dans un fichier sans utiliser les fonctions C.

### Compilation et Exécution
```bash
cd ex04
make
./sed_is_for_losers filename "s1" "s2"
# Crée filename.replace avec s1 remplacé par s2
```

### Concepts C++ Utilisés

#### 1. Lecture de Fichier (mode binaire)
```cpp
std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
if (!in) {
    std::cout << "Erreur d'ouverture\n";
    return 1;
}
```

**Pourquoi `std::ios::binary` ?**
- Préserve les caractères spéciaux
- Pas de conversion de fin de ligne
- Lecture fidèle du fichier original

#### 2. Lecture Complète avec Buffer
```cpp
std::ostringstream buffer;
buffer << in.rdbuf();  // Pompe tout le contenu
const std::string content = buffer.str();
```

#### 3. Algorithme de Remplacement
```cpp
bool replace_all(const std::string &input, const std::string &s1,
                 const std::string &s2, std::string &output) {
    if (s1.empty())
        return false;
    
    output.clear();
    std::string::size_type pos = 0;
    
    while (true) {
        std::string::size_type found = input.find(s1, pos);
        
        if (found == std::string::npos) {
            output.append(input, pos, std::string::npos);
            break;
        }
        
        // Ajoute ce qui précède l'occurrence
        output.append(input, pos, found - pos);
        // Ajoute le remplacement
        output.append(s2);
        // Saute l'occurrence trouvée
        pos = found + s1.size();
    }
    return true;
}
```

#### 4. Écriture du Fichier de Sortie
```cpp
const std::string outname = filename + ".replace";
std::ofstream out(outname.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

out.write(replaced.data(), static_cast<std::streamsize>(replaced.size()));

if (!out.good()) {
    std::cout << "Erreur d'écriture\n";
    return 1;
}
```

### Gestion d'Erreurs Robuste
- ✅ Vérification de l'ouverture des fichiers
- ✅ Vérification de la lecture (`in.good()` et `in.eof()`)
- ✅ Vérification de l'écriture (`out.good()`)
- ✅ Validation des arguments

---

## 🍔 Exercice 05 : Harl 2.0

### Description
Utiliser des **pointeurs vers méthodes membres** pour implémenter un système de dispatch.

### Compilation et Exécution
```bash
cd ex05
make
./Harl_2.0
```

### Pointeurs vers Méthodes Membres

#### Déclaration du Type
```cpp
class Harl {
private:
    typedef void(Harl::*Action)(void);  // Type : pointeur vers méthode membre
    
    struct Entry {
        const char *name;
        Action fn;
    };
    
    static const Entry Table[];
};
```

#### Table de Dispatch Statique
```cpp
const Harl::Entry Harl::Table[] = {
    {"DEBUG",   &Harl::debug},
    {"INFO",    &Harl::info},
    {"WARNING", &Harl::warning},
    {"ERROR",   &Harl::error}
};
```

#### Appel de la Méthode
```cpp
void Harl::complain(const std::string level) {
    const size_t N = sizeof(Table) / sizeof(Table[0]);
    
    for (size_t i = 0; i < N; i++) {
        if (level == Table[i].name) {
            Action a = Table[i].fn;     // Récupère le pointeur
            (this->*a)();                // Appel avec this
            return;
        }
    }
}
```

### Syntaxe des Pointeurs vers Méthodes Membres

```cpp
// Déclaration
void(Harl::*Action)(void)

// Affectation
Action a = &Harl::debug;

// Appel
(this->*a)();       // Avec instance (this)
(obj.*a)();         // Avec objet
(ptr->*a)();        // Avec pointeur d'objet
```

### 💡 Avantages
- ✅ Pas de `if/else` en cascade
- ✅ Facile d'ajouter de nouveaux niveaux
- ✅ Table de dispatch efficace
- ✅ Code maintenable et extensible

---

## 🔊 Exercice 06 : HarlFilter

### Description
Filtrer les messages de Harl à partir d'un niveau donné en utilisant un **switch avec fall-through**.

### Compilation et Exécution
```bash
cd ex06
make
./HarlFilter DEBUG
./HarlFilter WARNING
./HarlFilter INVALID
```

### Switch avec Fall-Through
```cpp
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./HarlFilter <level>\n";
        return 1;
    }
    
    const int index = recover_index(argv[1]);
    Harl h;
    
    switch (index) {
        case 0:
            std::cout << "[ DEBUG ]\n";
            h.complain("DEBUG");
            /* fall through */
        case 1:
            std::cout << "[ INFO ]\n";
            h.complain("INFO");
            /* fall through */
        case 2:
            std::cout << "[ WARNING ]\n";
            h.complain("WARNING");
            /* fall through */
        case 3:
            std::cout << "[ ERROR ]\n";
            h.complain("ERROR");
            break;
        default:
            std::cout << "Invalid level\n";
    }
    return 0;
}
```

### Fonction Helper
```cpp
static int recover_index(const std::string &level) {
    const char *name[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    
    for (size_t i = 0; i < 4; i++) {
        if (level == name[i])
            return i;
    }
    return -1;  // Niveau invalide
}
```

### 🎯 Comportement du Fall-Through

| Input | Output |
|-------|--------|
| `DEBUG` | DEBUG → INFO → WARNING → ERROR |
| `INFO` | INFO → WARNING → ERROR |
| `WARNING` | WARNING → ERROR |
| `ERROR` | ERROR seulement |
| `INVALID` | Message d'erreur |

### Pourquoi `/* fall through */` ?
- Commentaire explicite pour indiquer l'intention
- Évite les warnings du compilateur
- Documente le comportement voulu

---

## 🔑 Concepts C++ Avancés du Module

### 1. Gestion de la Mémoire

#### new vs malloc
```cpp
// C++
Zombie *z = new Zombie();  // Appelle le constructeur
delete z;                  // Appelle le destructeur

// C (à éviter en C++)
Zombie *z = (Zombie*)malloc(sizeof(Zombie));  // Pas de constructeur !
free(z);                                       // Pas de destructeur !
```

#### Fuites Mémoires
```cpp
// ❌ Fuite mémoire
Zombie *z = new Zombie();
// ... oubli de delete z;

// ✅ Bonne pratique
Zombie *z = new Zombie();
// ... utilisation ...
delete z;
z = NULL;  // Optionnel mais recommandé
```

### 2. Références vs Pointeurs

```cpp
// Référence : alias permanent
int x = 42;
int &ref = x;      // ref est x
ref = 100;         // x = 100 maintenant

// Pointeur : adresse variable
int *ptr = &x;     // ptr pointe vers x
*ptr = 200;        // x = 200 maintenant
ptr = NULL;        // ptr peut changer de cible
```

### 3. const avec Références
```cpp
// Référence constante (lecture seule)
const std::string& getType() const {
    return _type;  // Évite la copie
}

// Avantages :
// ✅ Pas de copie (performance)
// ✅ Protection contre modification
// ✅ Peut lier des temporaires
```

### 4. Streams et Fichiers

```cpp
// Lecture
std::ifstream in("file.txt");
std::string line;
std::getline(in, line);

// Écriture
std::ofstream out("output.txt");
out << "Hello World\n";

// Modes
std::ios::in      // Lecture
std::ios::out     // Écriture
std::ios::binary  // Mode binaire
std::ios::trunc   // Tronquer le fichier
std::ios::app     // Append
```

---

## 🛡️ Bonnes Pratiques de Mémoire

### 1. RAII (Resource Acquisition Is Initialization)
```cpp
void function() {
    Zombie z;          // Construction automatique
    // ... utilisation ...
}                      // Destruction automatique (RAII)
```

### 2. Toujours delete ce que vous new
```cpp
Zombie *z = new Zombie();
try {
    // ... code qui peut lever une exception ...
    delete z;
} catch (...) {
    delete z;  // Ne pas oublier même en cas d'erreur
    throw;
}
```

### 3. Préférer la Stack quand c'est possible
```cpp
// ✅ Préféré
void f() {
    Zombie z;
    z.annonce();
}

// ❌ Éviter si pas nécessaire
void f() {
    Zombie *z = new Zombie();
    z->annonce();
    delete z;
}
```

---

## 🐛 Erreurs Courantes à Éviter

### 1. Double Delete
```cpp
Zombie *z = new Zombie();
delete z;
delete z;  // ❌ ERREUR : Comportement indéfini
```

### 2. Delete sans New
```cpp
Zombie z;
delete &z;  // ❌ ERREUR : z est sur la stack !
```

### 3. Mauvais Opérateur Delete
```cpp
Zombie *horde = new Zombie[5];
delete horde;    // ❌ ERREUR : Utiliser delete[]
delete[] horde;  // ✅ CORRECT
```

### 4. Utilisation après Delete
```cpp
Zombie *z = new Zombie();
delete z;
z->annonce();  // ❌ ERREUR : Dangling pointer
```

### 5. Référence Non Initialisée
```cpp
class Test {
    std::string& ref;  // ❌ ERREUR : Doit être initialisée
public:
    Test() {}  // Ne compile pas !
};
```

---

## 📊 Récapitulatif des Exercices

| Exercice | Concept Principal | Difficulté |
|----------|-------------------|------------|
| ex00 | Heap vs Stack | ⭐ |
| ex01 | Tableaux dynamiques | ⭐⭐ |
| ex02 | Pointeurs vs Références | ⭐ |
| ex03 | Références/Pointeurs pratiques | ⭐⭐ |
| ex04 | Streams et fichiers | ⭐⭐⭐ |
| ex05 | Pointeurs vers méthodes | ⭐⭐⭐⭐ |
| ex06 | Switch fall-through | ⭐⭐ |

---

## 💡 Astuces pour Réussir

### Déboguer les Fuites Mémoires
```bash
# Utiliser Valgrind
valgrind --leak-check=full ./programme
```

### Vérifier les Erreurs de Mémoire
```bash
# Avec AddressSanitizer
g++ -fsanitize=address -g programme.cpp
./a.out
```

### Compilation Stricte
```bash
c++ -std=c++98 -Wall -Wextra -Werror -g programme.cpp
```

---

## ✅ Checklist de Compréhension

Avant de passer au module suivant, vous devez maîtriser :

- [ ] Différence entre stack et heap
- [ ] Quand utiliser `new` et `delete`
- [ ] Différence entre `delete` et `delete[]`
- [ ] Pointeurs vs Références
- [ ] Quand préférer l'un ou l'autre
- [ ] Protection contre les fuites mémoires
- [ ] Gestion des exceptions avec `bad_alloc`
- [ ] Utilisation de `std::ifstream` et `std::ofstream`
- [ ] Pointeurs vers méthodes membres
- [ ] Switch avec fall-through

---

## 🚀 Pour Aller Plus Loin

### Smart Pointers (C++11+)
Bien que non autorisés dans le module, ils sont l'avenir :
```cpp
std::unique_ptr<Zombie> z = std::make_unique<Zombie>();
// Pas besoin de delete, gestion automatique !
```

### Améliorations Possibles
1. **ex00** : Ajouter un compteur de zombies vivants
2. **ex01** : Permettre des noms différents pour chaque zombie
3. **ex04** : Supporter les expressions régulières
4. **ex05** : Ajouter des timestamps aux messages

---

## 📚 Ressources Utiles

- [cppreference.com](https://en.cppreference.com/) - Référence complète
- [Valgrind](https://valgrind.org/) - Détection de fuites mémoires
- [C++ FAQ](https://isocpp.org/faq) - Questions fréquentes

---

## 🎓 Points Clés à Retenir

1. **Toujours libérer la mémoire allouée dynamiquement**
2. **Préférer les références aux pointeurs quand c'est possible**
3. **La stack est votre amie (RAII)**
4. **`new` → `delete`, `new[]` → `delete[]`**
5. **Vérifier les erreurs d'allocation avec `bad_alloc`**

---

**Félicitations pour les 100/100 ! 🎉**  
**Passez maintenant au CPP_02 pour découvrir l'Orthodox Canonical Form ! 🚀**
