# 🍝 Philosophers - Guide Étudiant

## 📖 Description du projet

Le projet **Philosophers** est une implémentation du célèbre problème des philosophes mangeurs (*dining philosophers problem*) d'Edsger Dijkstra. C'est un problème classique de synchronisation en programmation concurrente qui illustre les défis du partage de ressources entre plusieurs threads.

### Le problème

Des philosophes sont assis autour d'une table circulaire avec un bol de spaghetti devant chacun d'eux. Il y a une fourchette entre chaque paire de philosophes (donc autant de fourchettes que de philosophes). Pour manger, un philosophe a besoin de **deux fourchettes** : celle à sa gauche et celle à sa droite.

Chaque philosophe alterne entre trois états :
- 🍴 **Manger** : nécessite 2 fourchettes
- 😴 **Dormir** : repos après avoir mangé
- 🤔 **Penser** : réflexion entre le sommeil et la faim

**Le défi** : éviter les deadlocks (interblocages) et s'assurer qu'aucun philosophe ne meurt de faim !

---

## 🚀 Compilation et Exécution

### Compilation

```bash
make
```

Cela génère l'exécutable `philo`.

### Utilisation

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Arguments obligatoires :

1. **number_of_philosophers** : Nombre de philosophes (et de fourchettes)
2. **time_to_die** : Temps en millisecondes avant qu'un philosophe meure s'il ne mange pas
3. **time_to_eat** : Temps en millisecondes qu'un philosophe prend pour manger
4. **time_to_sleep** : Temps en millisecondes qu'un philosophe passe à dormir

#### Argument optionnel :

5. **number_of_times_each_philosopher_must_eat** : Le programme s'arrête quand tous les philosophes ont mangé au moins ce nombre de fois (sinon, il tourne jusqu'à la mort d'un philosophe)

### Exemples

```bash
# 4 philosophes, meurent après 410ms sans manger, mangent en 200ms, dorment 200ms
./philo 4 410 200 200

# 5 philosophes avec 7 repas maximum par philosophe
./philo 5 800 200 200 7

# Cas limite : 1 philosophe (devrait mourir car il n'a qu'une fourchette)
./philo 1 800 200 200

# Test de survie avec beaucoup de philosophes
./philo 200 410 200 200
```

---

## 🏗️ Architecture du Code

### Structure des fichiers

```
philo/
├── Makefile              # Compilation du projet
├── include/
│   └── philosophers.h    # Structures et prototypes
└── srcs/
    ├── actions.c         # Logique de prise de fourchettes et actions (manger, dormir)
    ├── death.c           # Vérification des conditions de mort et de fin
    ├── init_data.c       # Initialisation des structures de données
    ├── philosophers.c    # Main et création des threads
    ├── philo_utils.c     # Fonctions utilitaires (atoi, usleep, etc.)
    ├── print.c           # Affichage des états avec couleurs
    └── time.c            # Gestion du temps
```

### Structures principales

#### `t_philo` - Structure d'un philosophe
```c
typedef struct s_philo
{
    pthread_mutex_t *mutexlf;      // Mutex fourchette gauche
    pthread_mutex_t *mutexrf;      // Mutex fourchette droite
    pthread_mutex_t fork;          // Fourchette du philosophe
    pthread_mutex_t meal;          // Protection du temps du dernier repas
    unsigned long   philo_id;      // ID du philosophe (1 à N)
    struct s_data   *data;         // Pointeur vers les données partagées
    int             nb_meals;      // Nombre de repas pris
    long            last_meal;     // Timestamp du dernier repas
} t_philo;
```

#### `t_data` - Données partagées
```c
typedef struct s_data
{
    pthread_mutex_t mutexdead;     // Protection de la variable death
    pthread_mutex_t finish_philo;  // Protection du compteur de philosophes terminés
    pthread_mutex_t print;         // Protection de l'affichage
    unsigned long   nb_philo;      // Nombre de philosophes
    t_philo         *philo;        // Tableau des philosophes
    unsigned long   finish;        // Nombre de philosophes ayant fini de manger
    int             ttdie;         // Time to die (ms)
    int             tteat;         // Time to eat (ms)
    int             ttsleep;       // Time to sleep (ms)
    int             max_meals;     // Nombre de repas max (-1 si infini)
    int             death;         // Flag de mort (0 = vivant, 1 = mort)
    unsigned long   start;         // Timestamp de démarrage
} t_data;
```

---

## 🔑 Concepts Clés

### 1. Threads (pthread)

Chaque philosophe est représenté par un thread indépendant :

```c
pthread_create(&threads[i], NULL, start_routine, (void *)&philo[i]);
```

Tous les threads s'exécutent en parallèle et doivent être synchronisés.

### 2. Mutex (Mutual Exclusion)

Les mutex protègent les ressources partagées (fourchettes, variables) :

```c
pthread_mutex_lock(&mutex);    // Acquisition du mutex
// Section critique
pthread_mutex_unlock(&mutex);  // Libération du mutex
```

**Fourchettes** : Chaque fourchette est protégée par un mutex pour éviter que deux philosophes ne la prennent en même temps.

### 3. Éviter les Deadlocks

**Le problème** : Si tous les philosophes prennent leur fourchette gauche en même temps, ils attendent tous leur fourchette droite → deadlock !

**Solution implémentée** :
- Les philosophes **pairs** prennent gauche puis droite
- Les philosophes **impairs** prennent droite puis gauche

```c
if (philo->philo_id % 2 == 0)
    left_right(philo);  // Pair : gauche → droite
else
    right_left(philo);  // Impair : droite → gauche
```

### 4. Éviter les Data Races

Toutes les variables partagées sont protégées par des mutex :
- `death` : protégé par `mutexdead`
- `finish` : protégé par `finish_philo`
- `last_meal` : protégé par `meal` (propre à chaque philosophe)

### 5. Détection de la mort

Un thread séparé vérifie en boucle si un philosophe est mort :

```c
time = gettime() - philo[i].last_meal;
if (time > data->ttdie)
    is_dead(philo, data, i);
```

---

## 🎨 Codes Couleur de l'Affichage

Le programme affiche les actions avec des couleurs pour faciliter le suivi :

- 🔵 **CYAN** : "has taken a fork"
- 🟢 **GREEN** : "is eating"
- 🟡 **YELLOW** : "is sleeping"
- 🟣 **PURPLE** : "is thinking"
- 🔴 **RED** : "is dead"

---

## 🐛 Pièges Courants et Solutions

### 1. **Deadlock** ❌
**Problème** : Tous les philosophes bloqués, personne ne mange.
**Solution** : Alternance de l'ordre de prise des fourchettes (pairs/impairs).

### 2. **Data Race** ⚡
**Problème** : Plusieurs threads accèdent à une variable sans protection.
**Solution** : Protéger TOUTES les variables partagées avec des mutex.

### 3. **Mort non détectée** 💀
**Problème** : Un philosophe meurt mais le programme continue.
**Solution** : 
- Vérifier `check_death()` régulièrement
- Thread de surveillance qui vérifie `last_meal` en continu

### 4. **Affichage après la mort** 🖨️
**Problème** : Des messages s'affichent après la mort d'un philosophe.
**Solution** : Vérifier `check_death()` AVANT chaque `printf()`.

### 5. **Cas spécial : 1 philosophe** 🤔
**Problème** : Un seul philosophe ne peut pas manger (une seule fourchette).
**Solution** : Gérer ce cas spécialement dans `one_philo()`.

---

## 🧪 Tests Recommandés

### Tests de base
```bash
# Ne doit pas mourir
./philo 5 800 200 200

# Ne doit pas mourir, devrait s'arrêter après 7 repas
./philo 5 800 200 200 7

# Un philosophe devrait mourir
./philo 4 310 200 100
```

### Tests de limites
```bash
# 1 philosophe (doit mourir)
./philo 1 800 200 200

# Beaucoup de philosophes
./philo 200 800 200 200

# Timing serré (ne doit pas mourir)
./philo 4 410 200 200
```

### Tests de stabilité
```bash
# Exécution longue sans mort
./philo 4 410 200 200 50

# Test de précision du timing
./philo 2 400 200 200
```

---

## 📊 Outils de Débogage

### Vérifier les data races avec Helgrind
```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

### Vérifier les fuites mémoire
```bash
valgrind --leak-check=full ./philo 5 800 200 200 7
```

### Compiler avec les flags de débogage
```bash
make CFLAGS="-Wall -Wextra -Werror -g3 -fsanitize=thread"
```

---

## 💡 Conseils pour Comprendre le Code

1. **Commencez par le main** ([philosophers.c](srcs/philosophers.c#L72)) :
   - Initialisation des données
   - Création des threads
   - Lancement de la surveillance

2. **Suivez la vie d'un philosophe** ([philosophers.c](srcs/philosophers.c#L42) - `start_routine`) :
   - Boucle infinie jusqu'à mort ou fin
   - Eat → Sleep → Think

3. **Analysez la prise de fourchettes** ([actions.c](srcs/actions.c#L72)) :
   - Ordre différent selon pair/impair
   - Vérifications de mort entre chaque action

4. **Comprenez la surveillance** ([death.c](srcs/death.c#L37)) :
   - Boucle de vérification continue
   - Compare `gettime() - last_meal` avec `ttdie`

---

## 📚 Ressources Utiles

### Documentation
- [Pthread Tutorial (EN)](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
- [Mutex et Synchronisation (FR)](https://openclassrooms.com/fr/courses/1026284-programmation-systeme-en-c-sous-unix/1027430-les-threads)

### Le problème des philosophes
- [Article Wikipedia (FR)](https://fr.wikipedia.org/wiki/D%C3%AEner_des_philosophes)
- [Visualisation interactive](https://www.youtube.com/watch?v=FYUi-u7UWgw)

---

## ✅ Checklist de Validation

- [ ] Compilation sans warnings (`-Wall -Wextra -Werror`)
- [ ] Pas de data races (vérifier avec `helgrind`)
- [ ] Pas de deadlocks (tester avec différents arguments)
- [ ] Gestion correcte du cas `1 philosophe`
- [ ] Mort détectée dans les 10ms après le dépassement
- [ ] Aucun message après la mort d'un philosophe
- [ ] Programme s'arrête correctement avec `max_meals`
- [ ] Pas de fuites mémoire (vérifier avec `valgrind`)
- [ ] Tous les mutex sont détruits (`cleanup_mutexes`)
- [ ] Tous les threads sont joinés (`join_threads`)

---

## 🎯 Points Importants pour l'Évaluation

1. **Précision du timing** : La mort doit être détectée rapidement (< 10ms)
2. **Aucun message après la mort** : Condition de course critique
3. **Pas de data races** : Utiliser `helgrind` pour vérifier
4. **Protection des ressources** : Tous les accès aux variables partagées doivent être protégés
5. **Norme 42** : Respect de la norme de code

---

## 🤝 Contribution

Ce projet a été réalisé dans le cadre du cursus de l'école 42.

**Auteur** : vnieto-j  
**Date** : Juin 2025

---

## 📝 Notes Finales

Le projet Philosophers est un excellent exercice pour comprendre :
- La programmation concurrente
- Les problèmes de synchronisation
- L'importance des mutex
- La détection et la prévention des deadlocks

Prenez le temps de **bien comprendre** chaque partie du code plutôt que de simplement le copier. C'est la clé pour réussir les projets suivants qui utilisent les threads ! 🚀

Bon courage ! 💪
