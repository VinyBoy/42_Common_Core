# 🐚 Minishell

![42 Project Badge](https://img.shields.io/badge/42-Minishell-blue)
![Language](https://img.shields.io/badge/language-C-orange)
![Norminette](https://img.shields.io/badge/norminette-passing-success)

Un interpréteur de commandes minimaliste écrit en C, reproduisant le comportement de base de bash.

## 📋 Table des matières

- [À propos](#à-propos)
- [Fonctionnalités](#fonctionnalités)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Commandes intégrées](#commandes-intégrées)
- [Gestion avancée](#gestion-avancée)
- [Architecture](#architecture)
- [Auteurs](#auteurs)

## 🎯 À propos

Minishell est un projet de l'école 42 dont l'objectif est de recréer un shell basique inspiré de bash. Ce projet permet de comprendre en profondeur le fonctionnement des processus, des signaux, des redirections et du parsing de commandes.

## ✨ Fonctionnalités

### Commandes intégrées (Builtins)

- `echo` avec option `-n`
- `cd` avec chemins relatifs et absolus
- `pwd` sans options
- `export` pour définir les variables d'environnement
- `unset` pour supprimer des variables d'environnement
- `env` pour afficher l'environnement
- `exit` avec code de sortie

### Redirections

- `<` : redirection d'entrée
- `>` : redirection de sortie (écrasement)
- `>>` : redirection de sortie (ajout)
- `<<` : heredoc avec délimiteur

### Fonctionnalités avancées

- **Pipes** : Chaînage de commandes avec `|`
- **Expansion de variables** : `$VAR` et `$?` (code de sortie)
- **Gestion des quotes** :
  - Simple quotes `'` : pas d'expansion
  - Double quotes `"` : expansion des variables
- **Gestion des signaux** :
  - `Ctrl-C` : Interruption de la commande en cours
  - `Ctrl-D` : Sortie du shell
  - `Ctrl-\` : Aucun effet (comme bash)
- **Historique** : Navigation avec les flèches ↑ et ↓

## 🔧 Prérequis

- GCC ou Clang
- Make
- Readline library

### Installation de readline

```bash
# Ubuntu/Debian
sudo apt-get install libreadline-dev

# macOS
brew install readline
```

## 📦 Installation

```bash
# Cloner le dépôt
git clone [URL_DU_REPO] minishell
cd minishell

# Compiler le projet
make

# Lancer le shell
./minishell
```

### Commandes make disponibles

```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et l'exécutable
make re     # Recompile entièrement le projet
```

## 🚀 Utilisation

### Lancement

```bash
./minishell
```

Vous verrez apparaître le prompt :
```
MINISHELL
```

### Exemples de commandes

```bash
# Commandes simples
minishell$ echo "Hello World"
minishell$ pwd
minishell$ cd /tmp
minishell$ ls -la

# Redirections
minishell$ echo "test" > file.txt
minishell$ cat < file.txt
minishell$ ls -l >> output.txt

# Heredoc
minishell$ cat << EOF
> line 1
> line 2
> EOF

# Pipes
minishell$ ls -l | grep minishell | wc -l
minishell$ cat file.txt | grep "pattern" | sort

# Variables d'environnement
minishell$ export MY_VAR="Hello"
minishell$ echo $MY_VAR
minishell$ unset MY_VAR

# Code de sortie
minishell$ ls non_existent_file
minishell$ echo $?
```

## 🔨 Commandes intégrées

### `echo`
Affiche des arguments sur la sortie standard.
```bash
echo [-n] [arguments...]
```
- Option `-n` : n'affiche pas le retour à la ligne final

### `cd`
Change le répertoire de travail.
```bash
cd [chemin]
```
- Sans argument : retourne au répertoire HOME
- Met à jour les variables `PWD` et `OLDPWD`

### `pwd`
Affiche le chemin absolu du répertoire courant.
```bash
pwd
```

### `export`
Définit ou affiche les variables d'environnement.
```bash
export [VAR=valeur...]
```
- Sans argument : affiche toutes les variables exportées

### `unset`
Supprime des variables d'environnement.
```bash
unset [VAR...]
```

### `env`
Affiche l'environnement actuel.
```bash
env
```

### `exit`
Quitte le shell avec un code de sortie optionnel.
```bash
exit [n]
```

## 🎓 Gestion avancée

### Gestion de la mémoire

Le projet utilise un gestionnaire de mémoire personnalisé (`mem_manager`) qui :
- Garde une trace de toutes les allocations
- Permet de libérer toute la mémoire en une seule fois
- Évite les fuites de mémoire

### Gestion des erreurs

Le shell gère correctement :
- Les erreurs de syntaxe (pipes, redirections, quotes non fermées)
- Les erreurs d'exécution (commande introuvable, permission refusée)
- Les erreurs de redirections (fichier inexistant, permission refusée)
- Les signaux (interruptions utilisateur)

### Variables spéciales

- `$?` : Code de retour de la dernière commande
- `$$` : PID du shell (non implémenté dans cette version)

## 🏗️ Architecture

```
minishell/
├── include/
│   └── minishell.h          # Déclarations et structures
├── libft/                    # Bibliothèque de fonctions utilitaires
│   ├── ft_printf/
│   └── get_next_line/
├── srcs/
│   ├── main.c               # Point d'entrée
│   ├── builtin/             # Commandes intégrées
│   │   ├── builtin.c
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── pwd.c
│   │   └── unset.c
│   ├── exec/                # Exécution des commandes
│   │   ├── exec.c
│   │   ├── exec_redir*.c    # Gestion des redirections
│   │   ├── exec_utils.c
│   │   └── here_doc/        # Heredoc
│   ├── parsing/             # Analyse lexicale et syntaxique
│   │   ├── lexer*.c         # Tokenisation
│   │   ├── token*.c         # Traitement des tokens
│   │   ├── new_expand*.c    # Expansion des variables
│   │   ├── quotes.c         # Gestion des quotes
│   │   └── parsing.c
│   └── utils/               # Utilitaires
│       ├── free.c
│       ├── mem_manager.c    # Gestionnaire de mémoire
│       ├── signal.c
│       └── ft_dprintf.c
└── Makefile
```

### Flux d'exécution

1. **Lecture** : `readline()` récupère l'entrée utilisateur
2. **Lexing** : Tokenisation de la chaîne en tokens (WORD, PIPE, REDIR, etc.)
3. **Parsing** : Construction de la structure de commandes (AST)
4. **Expansion** : Remplacement des variables d'environnement
5. **Exécution** :
   - Configuration des redirections
   - Création des pipes si nécessaire
   - Fork et exécution des commandes
   - Attente des processus fils
6. **Cleanup** : Libération de la mémoire

## 👥 Auteurs

- **vnieto-j** - [@vnieto-j](https://github.com/VinyBoy)
- **oztozdem** - [@oztozdem](https://github.com/ozkainry)

## 📝 Notes

- Projet réalisé dans le cadre du cursus 42
- Respecte la Norminette (norme de codage de 42)
- Testé avec valgrind pour vérifier l'absence de fuites mémoire
- Compatible avec les comportements standards de bash

## 🔗 Ressources utiles

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- [Guide des signaux UNIX](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)

---

*Made with ☕ at 42*
