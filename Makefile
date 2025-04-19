CC =  cc
# CFLAGS = -Wall -Werror -Wextra -g
NAME = minishell

SRCS = 	srcs/minishell.c 					\
		srcs/handling.c 					\
		srcs/set_data.c 					\
		srcs/signal.c 						\
		srcs/bulidin_cmd.c					\
		srcs/expander.c						\
		srcs/setup_execution.c				\
		srcs/execution.c

all: $(NAME)

OBJS = $(SRCS:.c=.o)

HEADERS = includes/minishell.h
$(NAME): $(OBJS) $(HEADERS)
	make -C libft/printf
	make -C libft
	make -C libft bonus
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft/printf -lftprintf -Llibft -lft -lreadline -g
clean:
	make -C libft/printf clean
	make -C libft clean
	make -C libft bonus clean
	rm -f $(OBJS)
fclean: clean
	make -C libft/printf fclean
	make -C libft fclean
	make -C libft bonus fclean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
