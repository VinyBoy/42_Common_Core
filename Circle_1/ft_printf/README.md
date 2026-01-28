# ft_printf

## Description

Projet de **42** consistant à recoder la fonction `printf` de la libc. Ce projet permet de comprendre les fonctions variadiques et d'améliorer ses compétences en programmation C.

## Fonctionnalités

La fonction `ft_printf` gère les conversions suivantes :

- `%c` - Affiche un caractère
- `%s` - Affiche une chaîne de caractères
- `%p` - Affiche un pointeur en format hexadécimal
- `%d` - Affiche un nombre décimal (base 10)
- `%i` - Affiche un entier en base 10
- `%u` - Affiche un nombre décimal non signé (base 10)
- `%x` - Affiche un nombre en hexadécimal (base 16) minuscule
- `%X` - Affiche un nombre en hexadécimal (base 16) majuscule
- `%%` - Affiche un pourcentage

## Compilation

Pour compiler la bibliothèque :

```bash
make
```

Cela créera la bibliothèque statique `libftprintf.a`.

### Commandes disponibles

- `make` ou `make all` - Compile la bibliothèque
- `make clean` - Supprime les fichiers objets (.o)
- `make fclean` - Supprime les fichiers objets et la bibliothèque
- `make re` - Recompile entièrement le projet

## Utilisation

1. Incluez le header dans votre fichier :
```c
#include "ft_printf.h"
```

2. Compilez votre programme avec la bibliothèque :
```bash
cc main.c -L. -lftprintf -I./include
```

3. Exemple d'utilisation :
```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s!\n", "42");
    ft_printf("Nombre: %d\n", 42);
    ft_printf("Hexadécimal: %x\n", 255);
    ft_printf("Pointeur: %p\n", &main);
    return (0);
}
```

## Structure du projet

```
ft_printf/
├── Makefile
├── include/
│   └── ft_printf.h
└── src/
    ├── ft_printf.c
    ├── ft_print_str.c
    ├── ft_print_nb.c
    ├── ft_print_hexa.c
    └── ft_print_ptr.c
```

## Auteur

vnieto-j - 42 Student
