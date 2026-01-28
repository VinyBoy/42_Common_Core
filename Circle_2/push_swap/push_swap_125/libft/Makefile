# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:35:58 by vnieto-j          #+#    #+#              #
#    Updated: 2023/07/22 09:31:38 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#								    COLOR									   #
################################################################################

GREEN = \033[0;32m
RED = \033[0;31m
LIGHT_RED = \033[91m
LIGHT_GREEN = \033[92m
LIGHT_CYAN = \033[96m
BOLD =	\033[1m
RESET =	\033[0m

################################################################################
#								    CONFIG									   #
################################################################################

NAME	=	libft.a

INC_DIR	=	./include/

CC	=	cc

AR	=	ar rcs

RM	=	rm -rf

CFLAGS	=	-g -Wall -Wextra -Werror -I$(INC_DIR)

################################################################################
#                                 PROGRAM'S SRCSS                               #
################################################################################

SRC_DIR =	./source/

# On attribuer a la variable SRCS tout les fichier .c dans ./src

SRCS =	$(wildcard $(SRC_DIR)*.c)

# Tranforme les fichiers .c en .o dans chaque fichier de SRCS

OBJS = $(SRCS:.c=.o)

################################################################################
#                             		 NAME                                      #
################################################################################


$(NAME):	$(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@printf "$(BOLD)$(LIGHT_GREEN)Libft :$(LIGHT_CYAN)compiled$(LIGHT_GREEN)$(RESET)\n"
	@printf "$(BOLD)$(LIGHT_GREEN)Archive $(NAME) :$(BOLD) $(LIGHT_CYAN)created$(RESET)\n\n"

all	:	$(NAME)

 .c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME) $(OBJS)
	@echo "$(BOLD)$(LIGHT_CYAN)$(NAME) : $(BOLD)$(LIGHT_RED) $(NAME) was clean$(RESET)"

re : 
	make fclean
	make all

.PHONY: all clean fclean re