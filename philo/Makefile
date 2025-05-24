NAME		= philo
CC			= cc
CFLAGS		= -Wextra -Wall -Werror -pthread -g

OBJ_DIR		= obj/
SRC_DIR		= src

INCLUDES	= -I ./inc
HEADERS		= inc/philo.h

SRC 		= 	main.c \
				validation.c \
				init.c \
				delete.c \
				simu.c \
				action/routine.c \
				action/monitor.c \
				utils/utils.c \
				utils/print.c


OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32mPhilo built successfully ✅\033[0m"

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;32mPhilo cleaned successfully ✅\033[0m"

fclean: clean
	@rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

