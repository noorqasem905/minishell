/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:43:02 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/15 18:24:06 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd		t_cmd;
typedef struct s_here_doc	t_here_doc;
typedef struct s_exp		t_exp;
struct						s_here_doc
{
	int						fd;
	char					**file_loc;
	int						*pryority;
	int						counter;
	int						index;
	char					*input;
	char					*temp;
};
struct						s_cmd
{
	t_here_doc				*here_doc;
	t_list					*word;
	char					*input;
	char					**env;
	int						*pryority;
	int						who_am_i;
	int						counter;
	int						index;
	int						exit_status;
};

int							heredoc(char *temp, char **file_loc, size_t size);
int							handle_here_doc(char *temp);
struct						s_exp
{
	char						**name;
	char						**value;
	int							flag;
}		;

int						process_input(t_cmd **cmd, int *flag, char ***temp,
							char **input, char **robo_env);
int						check_validation(char **paths, char **result, char **m, t_cmd **cmd);
int						get_path(char **ev);
int						ft_strfind(char *str, char *c);
int						execution(t_cmd **cmd, char **env);
int						ft_execve(char *file, char **ev, t_cmd **cmd);
int						searching_comand(char **input, char **temp);
int						save_data(char **input, t_cmd **cmd, int *flag,
							char ***temp);
int						reading_manager(t_cmd **cmd, int *flag,
							char ***temp, char **robo_env);
int						ft_redirection(char *input, char ***redirection_split,
							char **robo_env, t_cmd **cmd);
int						ft_execute_redirection(char **redirection_split ,int ccount, int *fd,
							char *temp3, char **robo_env);
int						read_input(char **input);
void					free_list(t_list **root);
void					frees(t_list **root);
void					printf_split(char *str, char **split);
void					robo_cd(char **temp, char **robo_env);
void					free_it_now(char **s, char *s2, int emassage);
void					expand_cmds(t_cmd **cmd, char **env);
void					signal_handler(int x);
char					*check_access(char **paths, char **result);
char					*expander_input(t_list *input, char **env, t_cmd *cmd);
char					**my_env(char **env);
void					init_data(t_cmd **cmd);
void 					robo_export(t_cmd **cmd, t_exp *export);
int						ft_export(char *str, t_cmd **cmd);
int						is_valid(char *name);
void					unset(char *name, t_cmd *cmd);
void					env(t_cmd *cmd);
void					robo_pwd(void);
int						ft_isspace(char c);
void					robo_exit(char **str,t_cmd *cmd);
void 					update_env(char **env, int j, char *name, char *value);
char					**add_env(char **env, char *name, char *value);
//char					*get_env_value(char *name, char **env);
int 					get_env_j(char **env, char *name);
char 					*trim_quotes(char *str);
void 					error_export(t_cmd **cmd);
void 					handle_added(t_cmd **cmd, t_exp *export, int i, int j);
void					print_with_value(char *name, char *value);
void					handle_invalid(char *name);
int						word_count_custuom(char const *s, char c);
size_t					word_len_custuom(char *s, char c, int *flag);
char					**ft_split_custom_exp(char const *s, char c);
void					free_it(char **str, size_t i);

#endif