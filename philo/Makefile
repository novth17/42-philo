NAME		= philo
CC			= cc
CFLAGS		= -Wextra -Wall -Werror

OBJ_DIR		= obj/
SRC_DIR		= src

INCLUDES	= -I ./inc
HEADERS		= inc/philo.h

SRC 		= 	main.c \
				validation.c \
				utils/ft_putstr_fd.c \
				utils/ft_atoi_philo.c \


OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all:	$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32mPhilo built successfully ✅\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;32mPhilo cleaned successfully ✅\033[0m"

fclean: clean
	@rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

