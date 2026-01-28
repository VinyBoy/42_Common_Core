# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/19 17:58:15 by viny              #+#    #+#              #
#    Updated: 2025/12/17 13:01:03 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	srcs/main.cpp \

NAME = PmergeMe

OBJ = $(SRC:.cpp=.o)

FLAGS = -std=c++98 -Wall -Werror -Wextra

CC = c++

HEADERS = includes/PmergeMe.hpp srcs/Pmerge.tpp

%.o	: %.cpp $(HEADERS)
		$(CC) $(FLAGS) -c $< -o $@

all	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re	: fclean all

.PHONY: all clean fclean re