# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 11:19:34 by viny              #+#    #+#              #
#    Updated: 2025/11/16 15:54:42 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = srcs/Scalar.cpp \
		srcs/main.cpp

NAME = Scalar

OBJ = $(SRC:.cpp=.o)

FLAGS = -std=c++98 -Wall -Wextra -Werror

CC = c++

%.o		: %.cpp
	$(CC) $(FLAGS) -c $< -o $@
		
all		: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all

.PHONY	: all clean fclean re



# OBJ = $(SRC:.cpp=.o)

# FLAGS = -std=c++98 -Wall -Werror -Wextra

# CC = c++

# %.o: %.cpp
# 	$(CC) $(FLAGS) -c $< -o $@

# all	: $(NAME)

# $(NAME)	: $(OBJ)
# 	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

# clean	:
# 	rm -rf $(OBJ)

# fclean	: clean
# 	rm -rf $(NAME)

# re	: fclean all

# .PHONY: all clean fclean re