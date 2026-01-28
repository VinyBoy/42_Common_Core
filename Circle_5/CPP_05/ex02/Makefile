# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viny <viny@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 11:19:34 by viny              #+#    #+#              #
#    Updated: 2025/11/12 12:42:44 by viny             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	srcs/Bureaucrat.cpp \
		srcs/AForm.cpp \
		srcs/PresidentialPardonForm.cpp \
		srcs/RobotomyRequestForm.cpp \
		srcs/ShrubberyCreationForm.cpp \
		main.cpp

NAME = 28B_Not_28C

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