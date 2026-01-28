# Get Next Line

## Description

Projet de **42** consistant à créer une fonction qui lit une ligne depuis un file descriptor. Ce projet permet de comprendre la gestion de la mémoire statique, les buffers et la lecture de fichiers en C.

## Fonctionnalités

La fonction `get_next_line` permet de :

- Lire une ligne depuis un file descriptor (fichier, stdin, etc.)
- Gérer plusieurs appels successifs pour lire l'intégralité d'un fichier ligne par ligne
- Gérer la taille du buffer via la macro `BUFFER_SIZE`
- Retourner la ligne lue avec le `\n` final (si présent)
- Retourner `NULL` en fin de fichier ou en cas d'erreur

## Prototype

```c
char *get_next_line(int fd);
```

### Paramètres

- `fd` - Le file descriptor depuis lequel lire

### Retour

- La ligne lue (incluant le `\n` si présent)
- `NULL` si la fin du fichier est atteinte ou en cas d'erreur

## Compilation

Pour compiler avec votre programme :

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Vous pouvez ajuster la valeur de `BUFFER_SIZE` selon vos besoins.

## Utilisation

1. Incluez le header dans votre fichier :
```c
#include "get_next_line.h"
```

2. Exemple d'utilisation :
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("fichier.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## Structure du projet

```
Get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
└── get_next_line.h
```

## Fichiers

- **get_next_line.c** - Fonction principale et logique de lecture
- **get_next_line_utils.c** - Fonctions utilitaires
- **get_next_line.h** - Header avec prototypes et définitions

## Notes importantes

- N'oubliez pas de `free()` la ligne retournée après chaque appel
- La fonction gère un seul file descriptor à la fois (version obligatoire)
- `BUFFER_SIZE` doit être défini à la compilation

## Auteur

vnieto-j - 42 Student
