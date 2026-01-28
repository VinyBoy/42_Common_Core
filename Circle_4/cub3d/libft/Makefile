# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:35:58 by vnieto-j          #+#    #+#              #
#    Updated: 2025/05/12 06:26:36 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

RM = rm -rf

SRC =		ft_isdigit.c \
		ft_isalpha.c \
		ft_isprint.c \
		ft_isascii.c \
		ft_isalnum.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strncmp.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strdup.c \
		ft_strnstr.c \
		ft_memchr.c \
		ft_atoi.c \
		ft_memcmp.c \
		ft_iswspaces.c \
		ft_strjoin.c \
		ft_substr.c \
		ft_striteri.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_calloc.c \
		ft_lstnew.c \
		ft_lstlast.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstsize.c \
		ft_lstdelone.c \
		ft_strcmp.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_print_hexa.c \
		ft_printf/ft_print_nbr.c \
		ft_printf/ft_print_print.c \
		ft_printf/ft_print_ptr.c \
		ft_printf/ft_print_unsigned.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(AR) $(NAME) $(OBJ)
	
all: $(NAME)

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

so:
	gcc -nostartfiles -shared -o libft.so $(OBJ)

clean:
		@$(RM) $(OBJ)

fclean: clean
		$(RM)	$(NAME)

re: fclean all

.PHONY: all clean fclean re