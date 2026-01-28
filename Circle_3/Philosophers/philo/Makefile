NAME =			philo
CC =			@cc
CFLAGS =		-Wall -Wextra -Werror -g3 -pthread
OBJS =			$(patsubst srcs%, objs%, $(SRCS:.c=.o))
SRCS =			srcs/actions.c \
				srcs/death.c \
				srcs/init_data.c \
				srcs/philo_utils.c \
				srcs/philosophers.c \
				srcs/print.c \
				srcs/time.c \

GREEN =			\033[1;32m
YELLOW =		\033[1;33m
BLUE =			\033[1;34m
RED =			\033[1;31m
RESET =			\033[0m
BOLD =			\033[1m

all:			objs ${NAME}

${NAME}:		${OBJS}
				@echo "$(BLUE)$(BOLD)\n\tCompiling ${NAME}... 🛠️\n$(RESET)"
				${CC} ${CFLAGS} -o ${NAME} ${OBJS}
				@echo "$(GREEN)$(BOLD)\n\t${NAME} compiled 🚀\n$(RESET)"

objs:
				@mkdir -p objs

objs/%.o:		srcs/%.c
				$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
				@echo "$(RED)$(BOLD)\n\tCleaning up ${NAME} object files 🧹\n$(RESET)"
				@rm -rf ${OBJS} objs
				@echo "$(GREEN)$(BOLD)\n\t${NAME} object files removed! ✅\n$(RESET)"

fclean:			clean
				@echo "$(RED)$(BOLD)\n\tDeleting ${NAME} 🗑️\n$(RESET)"
				@rm -rf ${NAME}
				@echo "$(GREEN)$(BOLD)\n\t${NAME} deleted! ❌\n$(RESET)"

re:			
				@echo "$(YELLOW)$(BOLD)\n\tRecompiling ${NAME} 🔄\n$(RESET)"
				@$(MAKE) -s fclean all
				@echo "$(YELLOW)$(BOLD)\n\tDone recompiling! ✅\n$(RESET)"

.PHONY:			all clean fclean re