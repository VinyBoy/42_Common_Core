# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 16:15:03 by vnieto-j          #+#    #+#              #
#    Updated: 2025/05/30 16:15:05 by vnieto-j         ###   ########.fr        #
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
WHITE = \033[037m
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

NAME =			minishell

CC =			@cc

CFLAGS =		-Wall -Wextra -Werror -g3

OBJS =			$(patsubst srcs%, objs%, $(SRCS:.c=.o))

SRCS =			srcs/main.c \
				srcs/utils/utils.c \
				srcs/utils/free.c \
				srcs/utils/export_utils.c \
				srcs/utils/ft_dprintf.c \
				srcs/utils/ft_split_mem.c \
				srcs/utils/mem_manager.c \
				srcs/utils/libft_mem.c \
				srcs/builtin/pwd.c \
				srcs/builtin/cd.c \
				srcs/builtin/echo.c \
				srcs/builtin/builtin.c \
				srcs/builtin/env.c \
				srcs/builtin/exit.c \
				srcs/builtin/export.c \
				srcs/builtin/unset.c \
				srcs/exec/exec.c \
				srcs/exec/exec2.c \
				srcs/exec/exec3.c \
				srcs/exec/exec4.c \
				srcs/exec/exec_redir.c \
				srcs/exec/exec_redir2.c \
				srcs/exec/exec_redir3.c \
				srcs/exec/exec_redir4.c \
				srcs/exec/exec_redir5.c \
				srcs/exec/free_exec.c \
				srcs/exec/exec_utils.c \
				srcs/exec/exec_wait.c \
				srcs/exec/here_doc/here_doc.c \
				srcs/exec/here_doc/here_doc2.c \
				srcs/exec/here_doc/here_doc3.c \
				srcs/exec/here_doc/here_doc_signals.c \
				srcs/exec/here_doc/expand_here.c \
				srcs/exec/here_doc/here_doc_child.c \
				srcs/utils/signal.c \
				srcs/parsing/env.c \
				srcs/parsing/is_redir_token.c \
				srcs/parsing/lexer_1.c \
				srcs/parsing/lexer_2.c \
				srcs/parsing/lexer_3.c \
				srcs/parsing/lexer_syntax_error.c \
				srcs/parsing/lexer_utils.c \
				srcs/parsing/new_expand_1.c \
				srcs/parsing/new_expand_2.c \
				srcs/parsing/new_expand_3.c \
				srcs/parsing/parsing.c \
				srcs/parsing/print_lexer.c \
				srcs/parsing/quotes.c \
				srcs/parsing/token.c \
				srcs/parsing/token_1.c \
				srcs/parsing/token_2.c \
				srcs/parsing/token_utils.c \
				srcs/parsing/token_utils_1.c \
				srcs/parsing/token_utils_2.c \

all:			objs ${NAME}

${NAME}:		${OBJS}
				@echo "$(BLUE)$(BOLD)\n\tCompiling libft.a... 🛠️\n$(RESET)"
				@make -sC libft/
				@echo "$(GREEN)$(BOLD)\n\tlibft.a compiled 🚀\n$(RESET)"
				@echo "$(BLUE)$(BOLD)\n\tCompiling ${NAME}... 🛠️\n$(RESET)"
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} libft/libft.a -lreadline
				@echo "$(GREEN)$(BOLD)\n\t${NAME} compiled 🚀\n$(RESET)"

objs:
				@mkdir -p $(dir $(OBJS))


objs/%.o:		srcs/%.c
				$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
				@echo "$(RED)$(BOLD)\n\tCleaning up libft object files 🧹\n$(RESET)"
				@make clean -sC libft/
				@echo "$(GREEN)$(BOLD)\n\tlibft object files removed! ✅\n$(RESET)"
				@echo "$(RED)$(BOLD)\n\tCleaning up ${NAME} object files 🧹\n$(RESET)"
				@rm -rf ${OBJS} objs
				@echo "$(GREEN)$(BOLD)\n\t${NAME} object files removed! ✅\n$(RESET)"

fclean:			clean
				@echo "$(RED)$(BOLD)\n\tDeleting libft.a 🗑️\n$(RESET)"
				@make fclean -sC libft/
				@echo "$(GREEN)$(BOLD)\n\tlibft.a deleted! ❌\n$(RESET)"
				@echo "$(RED)$(BOLD)\n\tDeleting ${NAME} 🗑️\n$(RESET)"
				@rm -rf ${NAME}
				@echo "$(GREEN)$(BOLD)\n\t${NAME} deleted! ❌\n$(RESET)"

re:
				@echo "$(YELLOW)$(BOLD)\n\tRecompiling ${NAME} 🔄\n$(RESET)"
				@$(MAKE) -s fclean all
				@echo "$(YELLOW)$(BOLD)\n\tDone recompiling! ✅\n$(RESET)"

.PHONY:			all clean fclean re
