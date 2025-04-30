/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:43:02 by nqasem            #+#    #+#             */
/*   Updated: 2025/04/30 18:55:30 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd	t_cmd;
typedef struct s_here_doc	t_here_doc;
struct					s_cmd
{
	t_list						*word;
	char 						*input;
	char						**env;
	int							*pryority;
	int 						who_am_i;
	int 						exit_status;
}		;

struct s_here_doc
{
	int		fd;
	int		*pryority;
	char	*input;
	char	*temp;
}		;

int						heredoc(char *temp);
int						handle_here_doc(char *temp);
int						process_input(t_cmd **cmd, int *flag, char ***temp,
							char **input, char **robo_env);
int						check_validation(char **paths, char **result, char **m);
int						get_path(char **ev);
int						ft_strfind(char *str, char *c);
int						execution(t_cmd **cmd, char **env);
int						ft_execve(char *file, char **ev);
int						searching_comand(char **input, char **temp);
int						save_data(char **input, t_cmd **cmd, int *flag,
							char ***temp);
int						reading_manager(t_cmd **cmd, int *flag,
							char ***temp, char **robo_env);
int						ft_redirection(char *input, char ***redirection_split,
							char **robo_env);
int						ft_execute_redirection(char **redirection_split ,int ccount, int *fd,
							char *temp3, char **robo_env);
int						read_input(char **input);
void					free_list(t_list **root);
void					frees(t_list **root);
void					robo_cd(char **temp, char **robo_env);
void					free_it_now(char **s, char *s2, int emassage);
void					expand_cmds(t_cmd **cmd, char **env);
void					signal_handler(int x);
char					*check_access(char **paths, char **result);
char					*expander_input(t_list *input, char **env);
char					**my_env(char **env);
#endif