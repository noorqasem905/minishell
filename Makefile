CC =  cc
# CFLAGS = -Wall -Werror -Wextra -g
NAME = minishell
SRCS = srcs/minishell.c

all: $(NAME)

OBJS = $(SRCS:.c=.o)
HEADERS = includes/minishell.h
$(NAME): $(OBJS) $(HEADERS)
	make -C libft/printf
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft/printf -lftprintf -Llibft -lft -g
clean:
	make -C libft/printf clean
	make -C libft clean
	rm -f $(OBJS)
fclean: clean
	make -C libft/printf fclean
	make -C libft fclean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
