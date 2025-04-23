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
		srcs/redirection.c					\
		srcs/execution.c					\
		srcs/env.c									

all: $(NAME)

OBJS_DIR =includes/build
# OBJS = $(SRCS:.c=.o)
OBJS = $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)

LIBFT = libft
HEADERS = includes/minishell.h
HIDE = $(if $(SET),, @)
HIDED = $(if $(DIR),, --no-print-directory)

$(NAME): $(OBJS) $(HEADERS) $(LIBFT)
	$(HIDE)make $(HIDED) -C libft/printf
	$(HIDE)make $(HIDED) -C libft
	$(HIDE)make $(HIDED) -C libft bonus
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft/printf -lftprintf -Llibft -lft -lreadline -g

$(OBJS_DIR)/%.o: srcs/%.c $(HEADERS)
	$(HIDE)mkdir -p $(OBJS_DIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(HIDE)make $(HIDED) -C libft/printf clean
	$(HIDE)make $(HIDED) -C libft clean
	$(HIDE)make $(HIDED) -C libft bonus clean
	$(HIDE)rm -f $(OBJS)
fclean: clean
	$(HIDE)make $(HIDED) -C libft/printf fclean
	$(HIDE)make $(HIDED) -C libft fclean
	$(HIDE)make $(HIDED) -C libft bonus fclean
	$(HIDE)rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
