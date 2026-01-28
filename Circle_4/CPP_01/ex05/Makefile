# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 19:27:06 by viny              #+#    #+#              #
#    Updated: 2025/08/29 16:25:42 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= 	main.cpp \
		Harl.cpp

NAME = 	Harl_2.0

OBJ	= 	$(SRC:.cpp=.o)

FLAGS =	-std=c++98 -Wall -Werror -Wextra

CC	= 	c++

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re	: fclean all

.PHONY: all clean fclean re