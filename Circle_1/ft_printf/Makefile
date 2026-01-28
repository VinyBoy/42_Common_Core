# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 14:58:57 by vnieto-j          #+#    #+#              #
#    Updated: 2024/11/27 15:39:29 by vnieto-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

CC =		@cc

CFLAGS =	-Wall -Wextra -Werror -I$(INC_DIR)

AR = 		@ar rcs

RM =		@rm -rf

INC_DIR	=	./include/

SRC = 		src/ft_print_hexa.c \
			src/ft_print_nb.c \
			src/ft_print_ptr.c \
			src/ft_print_str.c \
			src/ft_printf.c

OBJ = 		$(SRC:.c=.o)

GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
RESET = \033[0m
BOLD = \033[1m

	
$(NAME): $(OBJ)
	@echo "$(BLUE)$(BOLD)\n\t🛠️  Compiling ${NAME}...\n$(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)$(BOLD)\n\t🚀 ${NAME} compiled\n$(RESET)"

all : $(NAME)

clean :
	@echo "$(RED)$(BOLD)\n\t🧹 Cleaning up object files\n$(RESET)"
	$(RM) $(OBJ)
	@echo "$(GREEN)$(BOLD)\n\t✅ Object files removed!\n$(RESET)"

fclean : clean
	@echo "$(RED)$(BOLD)\n\t🗑️  Deleting ${NAME}\n$(RESET)"
	$(RM) $(NAME)
	@echo "$(GREEN)$(BOLD)\n\t❌ ${NAME} deleted!\n$(RESET)"

re : fclean all

.PHONY: all clean fclean re