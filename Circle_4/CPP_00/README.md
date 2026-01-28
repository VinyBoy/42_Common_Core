# CPP Module 00 - Guide Étudiant 📚

## 📊 Évaluation
**Note obtenue : 80/100** ⭐

---

## 🎯 Objectif du Module

Ce module est une introduction à la programmation orientée objet (POO) en C++. Il couvre les concepts fondamentaux comme les classes, les objets, les méthodes membres, et l'encapsulation des données.

## 📁 Structure du Projet

```
CPP_00/
├── ex00/          # Exercice 0 : Megaphone
└── ex01/          # Exercice 1 : Phone Book (Répertoire téléphonique)
```

---

## 📢 Exercice 00 : Megaphone

### Description
Un programme simple qui convertit tous ses arguments en majuscules et les affiche.

### Compilation et Exécution
```bash
cd ex00
make
./megaphone "shhhhh... I think the students are asleep..."
./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
./megaphone
```

### Concepts C++ Utilisés
- **`std::string`** : Manipulation de chaînes de caractères
- **`std::toupper()`** : Conversion en majuscules
- **Boucles** : Parcours des arguments et des caractères

### Points Clés du Code
```cpp
std::string to_uppercase(std::string &str)
```
- Prend une référence à une string (évite la copie)
- Retourne une nouvelle string en majuscules
- Utilise `std::toupper()` pour chaque caractère

---

## 📞 Exercice 01 : Phone Book

### Description
Un répertoire téléphonique interactif qui stocke jusqu'à 8 contacts. Les contacts sont remplacés de manière circulaire (le 9ème remplace le 1er, etc.).

### Compilation et Exécution
```bash
cd ex01
make
./Phone_Book
```

### Commandes Disponibles
- **`ADD`** : Ajouter un nouveau contact
- **`SEARCH`** : Afficher tous les contacts et en consulter les détails
- **`EXIT`** : Quitter le programme

---

## 🏗️ Architecture du Code (ex01)

### 1. Classe `Contact`

**Rôle** : Représente un contact individuel avec ses informations personnelles.

#### Attributs Privés
```cpp
std::string _first_name;      // Prénom
std::string _last_name;       // Nom de famille
std::string _nickname;        // Surnom
std::string _phone_number;    // Numéro de téléphone
std::string _darkest_secret;  // Secret le plus sombre
```

#### Constantes Publiques
```cpp
static const size_t MAX_NAME_LEN = 10;     // Longueur max pour nom/prénom
static const size_t MAX_SECRET_LEN = 20;   // Longueur max pour le secret
static const size_t MAX_PHONE_LEN = 15;    // Longueur max pour le téléphone
```

#### Méthodes Publiques

**Getters** (accesseurs en lecture seule) :
```cpp
std::string getFirstName() const;
std::string getLastName() const;
std::string getNickName() const;
std::string getPhoneNumber() const;
std::string getDarkestSecret() const;
```
> 💡 Le mot-clé `const` à la fin signifie que ces méthodes ne modifient pas l'objet.

**Setters** (modificateurs avec validation) :
```cpp
bool setFirstName(const std::string &fn);
bool setLastName(const std::string &ln);
bool setNickName(const std::string &nn);
bool setPhoneNumber(const std::string &pn);
bool setDarkestSecret(const std::string &ds);
```
> 💡 Retournent `true` si la validation réussit, `false` sinon.

#### Méthodes Privées (Helpers)
```cpp
bool isAlphaString(const std::string &s) const;  // Vérifie que la chaîne ne contient que des lettres
bool isPhoneString(const std::string &s) const;  // Vérifie que la chaîne ne contient que des chiffres
```

### 2. Classe `Phone_Book`

**Rôle** : Gère un tableau de 8 contacts maximum avec remplacement circulaire.

#### Attributs Privés
```cpp
Contact _contact[8];   // Tableau de 8 contacts
int     _next_index;   // Index du prochain contact à remplacer
int     _size;         // Nombre de contacts actuellement stockés
```

#### Méthodes Publiques
```cpp
void addContact(Contact &c);           // Ajoute un contact (avec saisie interactive)
bool printBook(void) const;            // Affiche la table des contacts
bool print_detail(int index) const;    // Affiche les détails d'un contact
bool IsValidIndex(int index) const;    // Vérifie si un index est valide
```

---

## 🔑 Concepts C++ Importants

### 1. Encapsulation
Les attributs sont **privés** (`_first_name`, `_last_name`, etc.) et ne peuvent être accédés que via des **getters/setters publics**.

**Pourquoi ?**
- ✅ Protection des données
- ✅ Validation avant modification
- ✅ Contrôle de l'accès

### 2. Constructeur et Destructeur
```cpp
Contact::Contact(void) : _first_name(), _last_name(), ... { }
Contact::~Contact(void) { }
```
- **Constructeur** : Initialise l'objet à sa création
- **Destructeur** : Nettoie l'objet à sa destruction (ici, rien à faire de spécial)

### 3. Listes d'Initialisation
```cpp
Contact::Contact(void) 
: _first_name(), _last_name(), _nickname(), _phone_number(), _darkest_secret()
```
Initialise les attributs **avant** l'entrée dans le corps du constructeur. Plus efficace que l'assignation.

### 4. Passage par Référence Constante
```cpp
bool setFirstName(const std::string &fn);
```
- `const` : Ne peut pas être modifié
- `&` : Passage par référence (évite la copie)
- ⚡ Performance optimale

### 5. Méthodes Constantes
```cpp
std::string getFirstName() const;
```
Le `const` à la fin garantit que la méthode ne modifie pas l'état de l'objet.

### 6. Static const
```cpp
static const size_t MAX_NAME_LEN = 10;
```
- `static` : Partagé par toutes les instances de la classe
- `const` : Ne peut pas être modifié

---

## 🛡️ Validations Implémentées

### Pour les Noms (First/Last Name)
- ❌ Chaîne vide refusée
- ❌ Caractères non alphabétiques refusés (sauf espaces)
- ⚠️ Troncature à 10 caractères avec avertissement

### Pour le Surnom (Nickname)
- ❌ Chaîne vide refusée
- ⚠️ Troncature à 10 caractères avec avertissement
- ✅ Tous caractères acceptés

### Pour le Numéro de Téléphone
- ❌ Chaîne vide refusée
- ❌ Caractères non numériques refusés
- ❌ Plus de 15 chiffres refusés

### Pour le Secret
- ❌ Chaîne vide refusée
- ❌ Plus de 20 caractères refusés

---

## 📊 Affichage des Contacts

### Table des Contacts
```
┌───────────────────────────────────────────┐
│     Index │ First Name│  Last Name│  Nickname │
│───────────────────────────────────────────│
│         0 │      Alice│      Smith│     Ally. │
│───────────────────────────────────────────│
│         1 │        Bob│      Jones│    Bobby. │
└───────────────────────────────────────────┘
```

### Règles d'Affichage
- Colonnes de 10 caractères
- Si le texte dépasse 10 caractères → tronqué avec un point `.`
- Utilisation de `std::setw(10)` pour l'alignement

---

## 🔄 Fonctionnement du Remplacement Circulaire

```cpp
_contact[_next_index] = newContact;
if (_size < 8)
    ++_size;
_next_index = (_next_index + 1) % 8;
```

**Exemple** :
1. Contacts 0-7 ajoutés → `_size = 8`, `_next_index = 0`
2. 9ème contact → Remplace l'index 0
3. 10ème contact → Remplace l'index 1
4. Et ainsi de suite...

---

## 🐛 Gestion des Erreurs

### EOF (End of File)
```cpp
if (std::cin.eof()) {
    std::cout << "\nFin de saisie (EOF).\n";
    std::cin.clear();
    return 1;
}
```
Gère le cas où l'utilisateur tape `Ctrl+D`.

### Validation Stricte des Index
```cpp
static bool parseIndexStrict(const std::string &s, int &out)
```
- Convertit la chaîne en entier
- Vérifie qu'il n'y a pas de caractères supplémentaires
- Retourne `false` si la conversion échoue

---

## 💡 Astuces et Bonnes Pratiques

### 1. Nommage des Attributs Privés
```cpp
_first_name  // Underscore préfixe = attribut privé
```
Convention pour distinguer visuellement les attributs des variables locales.

### 2. Protection contre les Copies Multiples
```cpp
const std::string tmp = new_cmd;
if (newContact.setFirstName(tmp))
```
On crée une copie `const` pour éviter les modifications accidentelles.

### 3. Formatage avec `std::setw`
```cpp
std::cout << std::setw(10) << "Text";
```
Réserve 10 caractères pour l'affichage (alignement à droite par défaut).

### 4. Opérateur Modulo pour la Circularité
```cpp
_next_index = (_next_index + 1) % 8;
```
Retourne automatiquement à 0 après 7.

---

## 📝 Normes 42

Ce projet respecte les normes de l'école 42 :
- ✅ Norme de codage C++ (Orthodox Canonical Form à venir dans les modules suivants)
- ✅ Makefile avec règles standard (all, clean, fclean, re)
- ✅ Compilation avec flags `-Wall -Wextra -Werror`
- ✅ Standard C++98

---

## 🚀 Pour Aller Plus Loin

### Améliorations Possibles
1. **Sauvegarde persistante** : Sauvegarder les contacts dans un fichier
2. **Recherche avancée** : Chercher par nom, surnom, etc.
3. **Suppression** : Ajouter une commande pour supprimer un contact
4. **Édition** : Modifier un contact existant
5. **Tri** : Trier les contacts par ordre alphabétique

### Concepts à Réviser
- Surcharge d'opérateurs (Module 02)
- Héritage (Module 03-04)
- Polymorphisme (Module 04)
- Templates (Modules avancés)

---

## 📚 Ressources Utiles

- [cplusplus.com](https://cplusplus.com/) - Référence C++
- [learncpp.com](https://learncpp.com/) - Tutoriels C++
- Documentation `std::string`, `std::iostream`

---

## ✅ Checklist de Compréhension

Avant de passer au module suivant, assurez-vous de comprendre :
- [ ] La différence entre classe et objet
- [ ] Le rôle des getters et setters
- [ ] L'encapsulation et les niveaux d'accès (public/private)
- [ ] Les constructeurs et destructeurs
- [ ] Le passage par référence vs par valeur
- [ ] Les méthodes constantes
- [ ] La gestion de la mémoire avec des tableaux d'objets

---

**Bon courage pour la suite des modules CPP ! 🚀**
