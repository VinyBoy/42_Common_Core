# Libft

## Description

Premier projet de **42** consistant à recoder des fonctions de la bibliothèque standard C (libc) ainsi que des fonctions utilitaires supplémentaires. Ce projet constitue la base de tous les futurs projets en C à 42.

## Objectifs

- Comprendre le fonctionnement des fonctions standard
- Maîtriser la gestion de la mémoire
- Apprendre à créer et manipuler des bibliothèques statiques
- Développer des fonctions utilitaires réutilisables

## Fonctions implémentées

### Partie 1 - Fonctions de la libc

**Manipulation de caractères :**
- `ft_isalpha` - Vérifie si le caractère est alphabétique
- `ft_isdigit` - Vérifie si le caractère est un chiffre
- `ft_isalnum` - Vérifie si le caractère est alphanumérique
- `ft_isascii` - Vérifie si le caractère est ASCII
- `ft_isprint` - Vérifie si le caractère est imprimable
- `ft_toupper` - Convertit en majuscule
- `ft_tolower` - Convertit en minuscule

**Manipulation de chaînes :**
- `ft_strlen` - Calcule la longueur d'une chaîne
- `ft_strchr` - Recherche un caractère dans une chaîne
- `ft_strrchr` - Recherche un caractère depuis la fin
- `ft_strncmp` - Compare deux chaînes
- `ft_strlcpy` - Copie une chaîne avec taille limitée
- `ft_strlcat` - Concatène avec taille limitée
- `ft_strnstr` - Recherche une sous-chaîne

**Manipulation de mémoire :**
- `ft_memset` - Remplit une zone mémoire
- `ft_bzero` - Met à zéro une zone mémoire
- `ft_memcpy` - Copie une zone mémoire
- `ft_memmove` - Copie avec gestion des chevauchements
- `ft_memchr` - Recherche un octet en mémoire
- `ft_memcmp` - Compare deux zones mémoires

**Conversion et allocation :**
- `ft_atoi` - Convertit une chaîne en entier
- `ft_calloc` - Alloue et initialise à zéro
- `ft_strdup` - Duplique une chaîne

### Partie 2 - Fonctions supplémentaires

- `ft_substr` - Extrait une sous-chaîne
- `ft_strjoin` - Concatène deux chaînes
- `ft_strtrim` - Supprime les caractères spécifiés aux extrémités
- `ft_split` - Découpe une chaîne selon un délimiteur
- `ft_itoa` - Convertit un entier en chaîne
- `ft_strmapi` - Applique une fonction à chaque caractère
- `ft_striteri` - Applique une fonction à chaque caractère (avec index)
- `ft_putchar_fd` - Affiche un caractère sur un fd
- `ft_putstr_fd` - Affiche une chaîne sur un fd
- `ft_putendl_fd` - Affiche une chaîne suivie d'un '\n' sur un fd
- `ft_putnbr_fd` - Affiche un nombre sur un fd

### Bonus - Manipulation de listes chaînées

- `ft_lstnew` - Crée un nouvel élément
- `ft_lstadd_front` - Ajoute un élément au début
- `ft_lstadd_back` - Ajoute un élément à la fin
- `ft_lstsize` - Compte les éléments
- `ft_lstlast` - Retourne le dernier élément
- `ft_lstdelone` - Supprime un élément
- `ft_lstclear` - Supprime toute la liste
- `ft_lstiter` - Applique une fonction à chaque élément
- `ft_lstmap` - Crée une nouvelle liste en appliquant une fonction

## Compilation

Pour compiler la bibliothèque :

```bash
make
```

Cela créera la bibliothèque statique `libft.a`.

Pour compiler avec les bonus :

```bash
make bonus
```

### Commandes disponibles

- `make` ou `make all` - Compile la bibliothèque
- `make bonus` - Compile avec les fonctions bonus
- `make clean` - Supprime les fichiers objets (.o)
- `make fclean` - Supprime les fichiers objets et la bibliothèque
- `make re` - Recompile entièrement le projet

## Utilisation

1. Incluez le header dans votre fichier :
```c
#include "libft.h"
```

2. Compilez votre programme avec la bibliothèque :
```bash
cc main.c -L. -lft
```

3. Exemple d'utilisation :
```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *str = "Hello 42!";
    char *upper;
    
    // Utilisation de ft_strlen
    printf("Longueur: %zu\n", ft_strlen(str));
    
    // Utilisation de ft_strmapi
    upper = ft_strmapi(str, to_upper_func);
    printf("Majuscules: %s\n", upper);
    free(upper);
    
    // Utilisation de ft_split
    char **words = ft_split("Bonjour tout le monde", ' ');
    int i = 0;
    while (words[i])
    {
        printf("Mot %d: %s\n", i, words[i]);
        free(words[i]);
        i++;
    }
    free(words);
    
    return (0);
}
```

## Structure du projet

```
Libft/
├── Makefile
├── libft.h
└── [fonctions].c (tous les fichiers .c)
```

## Notes importantes

- Toutes les fonctions gèrent les erreurs d'allocation mémoire
- Les fonctions de manipulation de chaînes respectent les comportements standards
- La partie bonus introduit les listes chaînées avec la structure `t_list`
- N'oubliez pas de libérer la mémoire allouée avec `free()`

## Auteur

vnieto-j - 42 Student
