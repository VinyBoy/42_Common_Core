# Minitalk

![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)

## 📝 Description

**Minitalk** est un projet de l'école 42 qui consiste à créer un système de communication inter-processus utilisant uniquement les signaux UNIX. Le projet comprend un serveur qui reçoit des messages et un client qui les envoie, en transmettant les données bit par bit via les signaux `SIGUSR1` et `SIGUSR2`.

## 🎯 Objectifs du projet

- Comprendre les signaux UNIX et leur manipulation
- Maîtriser la communication inter-processus (IPC)
- Gérer la transmission de données au niveau bit
- Implémenter un protocole de communication fiable
- Utiliser `sigaction` pour une gestion avancée des signaux

## 🛠️ Compilation

### Prérequis

- `gcc` ou `cc`
- `make`
- Système d'exploitation UNIX/Linux

### Installation

```bash
# Cloner le dépôt
git clone [votre-repo] minitalk
cd minitalk

# Compiler le projet
make

# Nettoyer les fichiers objets
make clean

# Nettoyer complètement
make fclean

# Recompiler
make re
```

Cela générera deux exécutables :
- `server` : Le serveur qui reçoit les messages
- `client` : Le client qui envoie les messages

## 🚀 Utilisation

### Lancer le serveur

```bash
./server
```

Le serveur affichera son PID (Process ID) :
```
Serveur en attente de signaux ... PID: 12345
```

### Envoyer un message avec le client

```bash
./client <PID_SERVEUR> "<MESSAGE>"
```

### Exemples

```bash
# Terminal 1 - Lancer le serveur
./server
# Affiche : Serveur en attente de signaux ... PID: 12345

# Terminal 2 - Envoyer un message
./client 12345 "Hello, World!"
# Le serveur affichera : Hello, World!

# Envoyer un autre message
./client 12345 "Minitalk is working! 🚀"
# Le serveur affichera : Minitalk is working! 🚀

# Arrêter le serveur proprement
./client 12345 "STOP_THE_SERVER"
# Le serveur se termine proprement
```

## 🔧 Fonctionnalités

### Fonctionnalités de base

- ✅ Transmission de messages caractère par caractère via signaux
- ✅ Reconstruction complète du message côté serveur
- ✅ Support des chaînes de caractères de longueur variable
- ✅ Gestion des caractères spéciaux et UTF-8
- ✅ Affichage en temps réel des messages reçus

### Fonctionnalités avancées

- ✅ Système d'accusé de réception (ACK) après chaque bit
- ✅ Confirmation de réception complète du message
- ✅ Arrêt propre du serveur avec commande spéciale
- ✅ Gestion robuste des erreurs
- ✅ Libération propre de la mémoire

## 📁 Structure du projet

```
minitalk/
├── Makefile
├── README.md
├── include/
│   └── minitalk.h
├── libft/
│   └── (bibliothèque libft)
└── src/
    ├── client.c
    ├── client_utils.c
    ├── server.c
    └── server_utils.c
```

## 🔬 Détails techniques

### Protocole de communication

Le projet utilise un protocole de communication bit par bit :

1. **Encodage** : Chaque caractère est décomposé en 8 bits
2. **Transmission** : 
   - `SIGUSR1` représente un bit à `1`
   - `SIGUSR2` représente un bit à `0`
3. **Reconstruction** : Le serveur reconstruit chaque caractère à partir des 8 bits reçus
4. **Accusé de réception** : Le serveur renvoie un `SIGUSR1` après chaque bit reçu
5. **Fin de message** : Un caractère nul (`\0`) marque la fin du message

### Gestion des signaux

- Utilisation de `sigaction` pour une gestion avancée des signaux
- `SA_SIGINFO` pour obtenir des informations sur l'émetteur du signal
- Variables globales de type `volatile sig_atomic_t` pour la communication avec les handlers

### Limites

- Longueur maximale du message : `1,000,000` caractères (définie par `MAX_LENGHT`)
- Délai entre les bits : `5000` microsecondes (5 ms) pour garantir la fiabilité

## 💡 Commandes spéciales

| Commande | Action |
|----------|--------|
| `STOP_THE_SERVER` | Arrête proprement le serveur et libère la mémoire |

```bash
./client <PID> "STOP_THE_SERVER"
```

## ⚙️ Gestion des erreurs

Le programme gère les cas d'erreur suivants :

- ✅ Nombre d'arguments incorrect
- ✅ PID invalide
- ✅ Échec de l'allocation mémoire
- ✅ Échec de l'envoi de signal
- ✅ Messages trop longs
- ✅ Interruptions de signal

## 🧪 Tests

### Test basique

```bash
# Terminal 1
./server

# Terminal 2
./client <PID> "Test"
```

### Test avec caractères spéciaux

```bash
./client <PID> "Hello! @#$%^&*()"
./client <PID> "Émojis: 🚀 🎉 ✅"
```

### Test de longue chaîne

```bash
./client <PID> "Lorem ipsum dolor sit amet, consectetur adipiscing elit..."
```

### Test de messages multiples

```bash
./client <PID> "Message 1"
./client <PID> "Message 2"
./client <PID> "Message 3"
```

## 👤 Auteur

**vnieto-j** - Étudiant à 42

---

## 📚 Ressources

- [Signal (IPC) - Wikipedia](https://en.wikipedia.org/wiki/Signal_(IPC))
- [sigaction() man page](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [UNIX Signals Tutorial](https://www.tutorialspoint.com/unix/unix-signals-traps.htm)
- [Inter-Process Communication](https://www.geeksforgeeks.org/inter-process-communication-ipc/)

## 📄 Licence

Ce projet est réalisé dans le cadre du cursus de l'école 42.
