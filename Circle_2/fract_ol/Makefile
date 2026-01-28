# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 17:33:41 by viny              #+#    #+#              #
#    Updated: 2023/07/28 14:19:48 by vnieto-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#								    COLOR									   #
################################################################################

#Formatage du texte
BOLD =	\033[1m
UNDERLINE =	\033[4m
SIGNAL = \033[5m
HIGHTLIGHT = \033[7m

#Couleur du texte
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

#Couleur arriere plan
BBLACK = \033[040m
BRED = \033[041m
BGREEN = \033[042m
BORANGE = \033[043m
BBLUE = \033[044m
BMAGENTA = \033[045m
BCYAN = \033[046m
BWHITE = \033[047m

#Reset
RESET =	\033[0m

################################################################################
#								    CONFIG									   #
################################################################################

NAME	=	fractol

INC_DIR	=	./include/

CC	=	cc 

CFLAGS	=	-g -Wall -Wextra -Werror -I$(INC_DIR)

RM	=	rm -rf

AUTHOR	=	vnieto-j

LDFLAGS	=	-lmlx -lX11 -lXext -lz -lm

LIBFT_PATH = ./libft/Libft

MLX_PATH = ./mlx_linux

LIBS = -L./mlx_linux

LIBSS = -L./libft/Libft

################################################################################
#                                 PROGRAM'S SRCSS                               #
################################################################################


SRC_DIR =	./src/

# On attribuer a la variable SRCS tout les fichier .c dans ./src

SRCS =	$(wildcard $(SRC_DIR)*.c)

# Tranforme les fichiers .c en .o dans chaque fichier de SRCS

OBJS =	$(patsubst %.c, %.o, $(SRCS))
# OBJS = $(SRC:.c=.o)

################################################################################
#                             		 NAME                                      #
################################################################################

$(NAME): $(OBJS) $(INC_DIR)fractol.h $(LIBFT_PATH)/libft.a $(MLX_PATH)/libmlx.a
	@make -C ./libft/Libft
	@printf "\t\t\t$(BOLD)$(BMAGENTA)Compilation des fichiers .c de fract_ol $(RESET)\n\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) -lft $(LIBSS) $(LDFLAGS)

all : $(NAME)

$(LIBFT_PATH)/libft.a :
	@printf "\t$(BOLD)$(BMAGENTA)Execution de make dans $(LIBFT_PATH)$(RESET)\n\n"
	@make -s -C $(LIBFT_PATH)

$(MLX_PATH)/libmlx.a :
	@printf "\t$(BOLD)$(BMAGENTA)Execution de make dans $(MLX_PATH)$(RESET)\n\n"
	@make -C $(MLX_PATH)

clean :
	@make  -C $(LIBFT_PATH) clean 
	@make  -C $(MLX_PATH) clean
	$(RM) $(OBJS)

fclean : clean
	@make -C libft/Libft fclean
	@$(RM) $(NAME) $(OBJS)

re : 
	@make -C libft/Libft re
	@make fclean
	@make all

.PHONY: all clean fclean re