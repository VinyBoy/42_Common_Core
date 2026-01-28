# CPP Module 06 🔄

```
 ██████╗██████╗ ██████╗      ██████╗  ██████╗ 
██╔════╝██╔══██╗██╔══██╗    ██╔═████╗██╔════╝ 
██║     ██████╔╝██████╔╝    ██║██╔██║███████╗ 
██║     ██╔═══╝ ██╔═══╝     ████╔╝██║██╔═══██╗
╚██████╗██║     ██║         ╚██████╔╝╚██████╔╝
 ╚═════╝╚═╝     ╚═╝          ╚═════╝  ╚═════╝ 
```

**Cast en C++ : static_cast, reinterpret_cast, dynamic_cast**

> **Note finale : 100/100** ✅

---

## 📚 Description

Ce module explore les différents types de cast en C++ et leurs utilisations appropriées :
- **static_cast** : Conversions de types vérifiées à la compilation
- **reinterpret_cast** : Conversions brutes de pointeurs et types
- **dynamic_cast** : Conversions polymorphiques vérifiées à l'exécution

---

## 🎯 Exercices

### Ex00 : Scalar Converter 🔢

**Objectif** : Créer un convertisseur de types scalaires qui détecte automatiquement le type d'entrée et affiche les conversions vers `char`, `int`, `float` et `double`.

**Classe** : `ScalarConverter` (non-instanciable avec méthode statique)

**Compilation** :
```bash
cd ex00
make
```

**Utilisation** :
```bash
./Scalar 42
./Scalar 42.0f
./Scalar 'a'
./Scalar "nan"
./Scalar "inf"
```

**Exemple de sortie** :
```
./Scalar 42
char: '*'
int: 42
float: 42.0f
double: 42.0

./Scalar "nan"
char: impossible
int: impossible
float: nanf
double: nan
```

**Notions abordées** :
- Détection automatique de types
- Conversions avec `static_cast`
- Gestion des cas limites (nan, inf, overflow)
- Précision d'affichage avec `std::setprecision`

---

### Ex01 : Serialization 💾

**Objectif** : Implémenter la sérialisation et désérialisation de pointeurs en utilisant `reinterpret_cast`.

**Classes** :
- `Data` : Structure contenant des données
- `Serializer` : Classe non-instanciable pour la conversion

**Compilation** :
```bash
cd ex01
make
```

**Utilisation** :
```bash
./Serialization
```

**Exemple de sortie** :
```
Data adress before serialization :0x7ffc8b4a5b80
Value of raw after serialization : 140722384780160
Deserialized ptr : 0x7ffc8b4a5b80

Original pointer :0x7ffc8b4a5b80
Deserialized ptr : 0x7ffc8b4a5b80

Pointeur match.

id : 42 name: test
```

**Notions abordées** :
- `reinterpret_cast` pour la conversion brute
- Type `uintptr_t` pour stocker des adresses
- Sérialisation/désérialisation de pointeurs

---

### Ex02 : Identify Real Type 🎭

**Objectif** : Identifier le type réel d'un objet polymorphique avec et sans utiliser de pointeur.

**Classes** :
- `Base` : Classe de base avec destructeur virtuel
- `A`, `B`, `C` : Classes dérivées vides

**Fonctions** :
- `Base* generate()` : Génère aléatoirement une instance de A, B ou C
- `void identify(Base* p)` : Identifie le type via pointeur
- `void identify(Base& p)` : Identifie le type via référence

**Compilation** :
```bash
cd ex02
make
```

**Utilisation** :
```bash
./Base
```

**Exemple de sortie** :
```
Test generate() / identify()

[Iteration 1]
pointer address: 0x55b8c4c3eeb0
identify(ptr): B
identify(ref): B
(deleted)

[Iteration 2]
pointer address: 0x55b8c4c3eeb0
identify(ptr): A
identify(ref): A
(deleted)
```

**Notions abordées** :
- `dynamic_cast` pour l'identification de type à l'exécution (RTTI)
- Différence entre cast de pointeur et de référence
- Polymorphisme et classes virtuelles
- Gestion aléatoire avec `rand()` et `srand()`

---

## 🛠️ Compilation

Tous les exercices utilisent le standard **C++98** avec les flags suivants :
```bash
-std=c++98 -Wall -Wextra -Werror
```

Chaque exercice possède son propre Makefile avec les règles :
- `make` : Compile le programme
- `make clean` : Supprime les fichiers objets
- `make fclean` : Supprime objets + exécutable
- `make re` : Recompile tout

---

## 📖 Concepts Clés

### Types de Cast en C++

| Cast | Usage | Vérification |
|------|-------|--------------|
| **static_cast** | Conversions standards (int→float, upcast) | Compile-time |
| **reinterpret_cast** | Conversions brutes de pointeurs/types | Aucune |
| **dynamic_cast** | Conversions polymorphiques sûres | Run-time |
| **const_cast** | Ajout/retrait de const (non couvert) | Compile-time |

### Quand utiliser quel cast ?

- **static_cast** : Pour les conversions numériques, upcasts, conversions explicites
- **reinterpret_cast** : Pour la manipulation bas niveau (sérialisation, interfaçage matériel)
- **dynamic_cast** : Pour les downcasts polymorphiques sûrs (nécessite RTTI et vtable)

---

## ⚠️ Points d'attention

- ✅ Pas d'utilisation de cast C-style `(type)value`
- ✅ Classes non-instanciables : constructeurs/destructeur privés
- ✅ Méthodes statiques pour les opérations sans état
- ✅ Gestion des cas limites (nan, inf, overflow, NULL)
- ✅ RTTI activé pour `dynamic_cast` (activé par défaut avec `-Wall`)

---

## 📝 Auteur

**viny** - École 42

---

## 🔗 Ressources

- [cppreference - static_cast](https://en.cppreference.com/w/cpp/language/static_cast)
- [cppreference - reinterpret_cast](https://en.cppreference.com/w/cpp/language/reinterpret_cast)
- [cppreference - dynamic_cast](https://en.cppreference.com/w/cpp/language/dynamic_cast)
- [C++ Type Conversions](https://en.cppreference.com/w/cpp/language/implicit_conversion)

---

*Module CPP 06 - Circle 5 - 42 Common Core* 🚀
