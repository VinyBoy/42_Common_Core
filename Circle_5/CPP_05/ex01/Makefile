# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 11:19:34 by viny              #+#    #+#              #
#    Updated: 2025/10/23 19:13:11 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	srcs/Bureaucrat.cpp \
		srcs/Form.cpp \
		main.cpp

NAME = Bureaucrat_Form

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