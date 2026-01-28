# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 15:08:13 by vnieto-j          #+#    #+#              #
#    Updated: 2025/02/15 18:09:11 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#								    COLOR									   #
################################################################################

# Formatage du texte
BOLD =	\033[1m
UNDERLINE =	\033[4m
SIGNAL = \033[5m
HIGHTLIGHT = \033[7m

# Couleurs
BLACK = \033[030m
RED = \033[031m
GREEN = \033[032m
ORANGE = \033[033m
BLUE = \033[034m
MAGENTA = \033[035m
CYAN = \033[036m
WHITE = \033[047m
LIGHT_RED = \033[91m
LIGHT_GREEN = \033[92m
LIGHT_CYAN = \033[96m

# Reset
RESET =	\033[0m

################################################################################
#								    CONFIG									   #
################################################################################

NAME	=	push_swap
NAMEB	=	checker

INC_DIR	=	./include/

CC	=	cc 
CFLAGS	=	-g3 -Wall -Wextra -Werror -I$(INC_DIR)

RM	=	rm -rf

AUTHOR	=	vnieto-j
LIBFT_PATH = ./libft
LIBS = -L./libft

################################################################################
#                                 PROGRAM'S SRCSS                               #
################################################################################

SRC_DIR =	./src/
SRC_BONUS_DIR = ./src/

SRCS =	fonctions_lists.c \
		instructions_1.c \
		instructions_2.c \
		main.c	\
		new_pre_sort_1.c \
		new_pre_sort_2.c \
		parsing.c \
		parsing2.c \
		sort_few_utils.c \
		sort_few.c \
		utils.c \
		sort.c \
		sort_utils.c \
		sort_rotate.c \

BONUS_SRC =	fonctions_lists.c \
		instructions_1.c \
		instructions_2.c \
		new_pre_sort_1.c \
		new_pre_sort_2.c \
		parsing.c \
		parsing2.c \
		sort_few_utils.c \
		sort_few.c \
		utils.c \
		sort.c \
		sort_utils.c \
		sort_rotate.c \
		checker.c \
		checker_utils.c \
		checker_utils2.c \
		checker_instructions.c \

OBJS = $(addprefix $(SRC_DIR), $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(SRC_BONUS_DIR), $(BONUS_SRC:.c=.o))

# Correction des règles de compilation
$(SRC_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)push_swap.h
	@$(CC) $(CFLAGS) -o $@ -c $<

$(SRC_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c $(INC_DIR)push_swap.h
	@$(CC) $(CFLAGS) -o $@ -c $<

################################################################################
#                             		 NAME                                      #
################################################################################

$(NAME): $(OBJS)
	@make -s -C $(LIBFT_PATH)
	@printf "\t$(BOLD)$(BMAGENTA)Compilation des fichiers .c de $(NAME)$(RESET)\n\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_PATH)/libft.a
	@printf "$(BOLD)$(LIGHT_GREEN)$(NAME) : $(LIGHT_CYAN)compiled$(LIGHT_GREEN)$(RESET)\n"
	@printf "$(BOLD)$(LIGHT_GREEN)Executable de $(NAME) :$(BOLD) $(LIGHT_CYAN)created$(RESET)\n\n"

all: $(NAME)

clean:
	@make -s -C $(LIBFT_PATH) clean 
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@make -s -C ./libft fclean
	@$(RM) $(NAME) $(NAMEB)

re:
	@make -s -C ./libft re
	@make fclean
	@make all

bonus: $(NAMEB)

$(NAMEB): $(BONUS_OBJS)
	@make -s -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) -o $(NAMEB) $(BONUS_OBJS) $(LIBFT_PATH)/libft.a

.PHONY: all clean fclean re
