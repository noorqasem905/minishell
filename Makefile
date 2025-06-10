CC =  cc
CFLAGS =  -g
NAME = minishell

SRCS = 	srcs/env.c							\
		srcs/unset.c						\
		srcs/utils.c						\
		srcs/export.c						\
		srcs/signal.c 						\
		srcs/handling.c 					\
		srcs/set_data.c 					\
		srcs/expander.c						\
		srcs/here_doc.c						\
		srcs/robo_env.c						\
		srcs/robo_pwd.c						\
		srcs/minishell.c 					\
		srcs/execution.c					\
		srcs/save_expo.c					\
		srcs/robo_exit.c					\
		srcs/bulidin_cmd.c					\
		srcs/redirection.c					\
		srcs/utils_export.c					\
		srcs/helper_export.c				\
		srcs/handle_export.c				\
		srcs/setup_execution.c				\
		srcs/setup_execution_heredoc.c		\
		srcs/setup_heredoc_redirection.c	\
		srcs/utils_exection_heredoc.c		\
		srcs/redirection_extract_2.c		\
		srcs/replace_special_char.c 		\
		srcs/redirection_extract.c			\
		srcs/redirection_handle2.c			\
		srcs/retore_special_char.c 			\
		srcs/redirection_heredoc.c			\
		srcs/dup_process_handle.c			\
		srcs/remove_quote_utils.c			\
		srcs/redirection_handle.c			\
		srcs/exeute_redirection.c			\
		srcs/append_redirection.c			\
		srcs/execution_bulidin2.c			\
		srcs/check_redirection.c			\
		srcs/execution_bulidin.c			\
		srcs/utils_redirection.c			\
		srcs/searching_bulidin.c			\
		srcs/setup_redirection.c			\
		srcs/handle_export_2.c				\
		srcs/helper_export_2.c 				\
		srcs/execute_heredoc.c				\
		srcs/utils_set_data2.c				\
		srcs/utils_exeution.c				\
		srcs/utils_here_doc.c				\
		srcs/utils_expander.c				\
		srcs/utils_set_data.c				\
		srcs/process_input.c				\
		srcs/utils_export2.c				\
		srcs/ft_echo_utils.c				\
		srcs/remove_qoute.c 				\
		srcs/dup_process.c					\
		srcs/utils_setup.c					\
		srcs/init_export.c					\
		srcs/open_pipe.c 					\
		srcs/utils_dup.c					\
		srcs/robo_cd.c						\
		srcs/utils2.c 						\
		srcs/ft_echo.c						\
		srcs/skp_export.c					\
		srcs/utils_skp.c
all: $(NAME)

OBJS_DIR =includes/build
# OBJS = $(SRCS:.c=.o)
OBJS = $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)

LIBFT = libft
HEADERS = includes/minishell.h
HIDE = $(if $(set),, @)
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
	$(HIDE)rm -f $(OBJS)
	$(HIDE)rm -f $(HEADERS)
	$(HIDE)rm -f $(HEADERS)

fclean:
	$(HIDE)make $(HIDED) -C libft/printf fclean
	$(HIDE)make $(HIDED) -C libft fclean
	$(HIDE)rm -f $(OBJS)
	$(HIDE)rm -f $(NAME)
	$(HIDE)rm -df $(OBJS_DIR)

re: fclean all

.PHONY: all clean fclean re