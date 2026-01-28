# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 15:37:43 by cgerner           #+#    #+#              #
#    Updated: 2025/10/15 16:08:42 by oztozdem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRCS =	srcs/Server/main.cpp \
		srcs/Server/WebServer.cpp \
		srcs/Server/ListenSocket.cpp \
		srcs/Server/AcceptSocket.cpp \
		srcs/Server/OpenSocket.cpp \
		srcs/HTTP/HttpRequest.cpp \
		srcs/HTTP/HttpResponse.cpp \
		srcs/ConfigParser/ConfigParser.cpp \
		srcs/AfterParse/Router.cpp \
		srcs/AfterParse/ExecRules.cpp \
		srcs/AfterParse/HandleFile.cpp \
		srcs/AfterParse/HandleCgi.cpp \
		srcs/AfterParse/HandleUpload.cpp

OBJS_DIR = objs

OBJS = $(SRCS:srcs/%.cpp=$(OBJS_DIR)/%.o)

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

GREEN = \033[1;32m
PINK = \033[1;35m
RED = \033[1;31m
RESET = \033[0m

all: $(NAME)

$(OBJS_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(dir $@)
	@echo "$(PINK)Compiling... 💭​​$(RESET) $(GREEN)$<$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@echo "$(PINK)Linked ✅​🥇​​$(RESET) $(GREEN)$(NAME)$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@echo "$(RED)Cleaning object files... 🚸​​$(RESET)"
	@rm -rf $(OBJS_DIR)
	@rm -rf socket_log.txt

fclean: clean
	@echo "$(RED)Removing executable... 🚸​​$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re