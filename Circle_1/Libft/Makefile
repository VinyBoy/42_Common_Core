# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 by vnieto-j             #+#    #+#              #
#    Updated: 2024/11/19 by vnieto-j            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
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
		ft_strchr.c \
		ft_strrchr.c \
		ft_strdup.c \
		ft_strnstr.c \
		ft_memchr.c \
		ft_atoi.c \
		ft_memcmp.c \
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

BONUSSRC =	ft_lstnew.c \
			ft_lstlast.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstsize.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
RESET = \033[0m
BOLD = \033[1m

all: $(NAME)

$(NAME):
	@echo "$(BLUE)$(BOLD)\n\t🛠️  Compiling ${NAME}...\n$(RESET)"
	@$(CC) $(CFLAGS) -c $(SRC)
	@ar rcs $(NAME) *.o
	@echo "$(GREEN)$(BOLD)\n\t🚀 ${NAME} compiled\n$(RESET)"

bonus:
	@echo "$(BLUE)$(BOLD)\n\t🛠️  Compiling ${NAME} with bonus...\n$(RESET)"
	@$(CC) $(CFLAGS) -c $(SRC) $(BONUSSRC)
	@ar rcs $(NAME) *.o
	@echo "$(GREEN)$(BOLD)\n\t🚀 ${NAME} compiled with bonus\n$(RESET)"

clean:
	@echo "$(RED)$(BOLD)\n\t🧹 Cleaning up object files\n$(RESET)"
	@rm -f *.o
	@echo "$(GREEN)$(BOLD)\n\t✅ Object files removed!\n$(RESET)"

fclean: clean
	@echo "$(RED)$(BOLD)\n\t🗑️  Deleting ${NAME}\n$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(BOLD)\n\t❌ ${NAME} deleted!\n$(RESET)"

re: fclean all
	@echo "$(YELLOW)$(BOLD)\n\t🔄 Recompiling ${NAME}\n$(RESET)"
	@echo "$(YELLOW)$(BOLD)\n\t✅ Done recompiling!\n$(RESET)"

.PHONY: all clean fclean re bonus