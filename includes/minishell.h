/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:43:02 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/20 22:04:46 by aalquraa         ###   ########.fr       */
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
	char					**expo;
	char					**env;
	int						*pryority;
	int						who_am_i;
	int						counter;
	int						index;
	int						exit_status;
	int						flag;
};

int							heredoc(char *temp, char **file_loc, size_t size);
int							handle_here_doc(char *temp);
struct						s_exp
{
	char					**name;
	char					**value;
	int						flag;
};
int							check_redirection_mult_siggr(int mult[],
								int conflect_handle[], int is_file_enter[],
								char *input);
int							check_redirection_mult_sign(int mult[],
								int conflect_handle[], int is_file_enter[],
								char *input);
int							check_redirection_mult_sigls(int mult[],
								int conflect_handle[], int is_file_enter[],
								char *input);
int							check_redirection_mult(char *input);
int							setup_redirection(char *input, char **temp,
								char **temp2);
int							ft_execute_redirection_p1(char **redirection_split,
								int ccount, int *fd);
int							ft_execute_redirection_p2(char **redirection_split,
								int ccount, int *fd);
int							redirection_check2free(char **temp,
								char ***redirection_split);
int							setup_extra_command(char *temp5, char **command);
int							extract_apply_short_2(char *tmp, char *temp5,
								char *temp4_copy, char **command);
int							setup_handle_redirection(char *input,
								char ***redirection_split, char **temp,
								char **temp2);
int							error_redirection(char **redirection_split,
								char *command, char *temp2, char *temp);
int							error_process_redirection(char ***redirection_split,
								char **temp, char *input, char **robo_env);
int							error_ft_execute_redirection(char *temp,
								char *command, char **robo_env);
int							process_input(t_cmd **cmd, int *flag, char ***temp,
								char **input, char **robo_env);
int							check_validation(char **paths, char **result,
								char **m);
int							child_process(t_cmd **cmd, t_list **current,
								int pipe_fd2[][2], pid_t pids[]);
int							dup_process(int *i, int size, int pipe_fd2[][2]);
int							dup_process_2(t_cmd **cmd, t_list **current,
								char **file_loc, int i);
int							get_path(char **ev);
int							ft_strfind(char *str, char *c);
int							execution(t_cmd **cmd, char **env);
int							ft_execve(char *file, char **ev);
int							searching_comand(char **input, char **temp);
int							save_data(char **input, t_cmd **cmd, int *flag,
								char ***temp);
int							which_redirection_char(char *temp);
int							reading_manager(t_cmd **cmd, int *flag,
								char ***temp, char **robo_env);
int							ft_redirection(char *input,
								char ***redirection_split, char **robo_env);
int							ft_execute_redirection(char **redirection_split,
								int ccount, int *fd, char *temp3,
								char **robo_env);
int							process_redirections(char ***redirection_split,
								char **robo_env, char **temp3);
int							handle_mult_redirection(char *temp3, char *temp2,
								char **temp, char ***redirection_split);
int							extract_and_apply_redirection(char **temp,
								char *temp2, char ***redirection_split,
								char **command);
int							handle_redirection_segment(char ***redirection_split,
								char **temp, char **temp4, char *th);
int							read_input(char **input);
size_t						element_size(char **str);
void						close_wait(pid_t pids[], int size,
								int pipe_fd2[][2]);
void						extract_apply_short_3(char **tmp, char **temp,
								char *temp4, char **command);
int							extract_apply_short(char **temp, char **tmp,
								char ***redirection_split, char *temp4_copy);
void						free_list(t_list **root);
void						frees(t_list **root);
void						printf_split(char *str, char **split);
void						robo_cd(char **temp, char **robo_env);
void						free_it_now(char **s, char *s2, int emassage);
void						signal_handler(int x);
char						*check_access(char **paths, char **result);
char						*expander_input(t_cmd **cmd);
char						**my_env(char **env);
void						init_data(t_cmd **cmd);
void						robo_export(t_cmd **cmd, t_exp *export);
int							ft_export(char *str, t_cmd **cmd);
int							is_valid(char *name);
int							ft_isspace(char c);
char						**add_env(char **env, char *name, char *value);
char						*get_redirection_command(char *temp,
								char **redirection_split, int iteritor);
int							get_env_j(char **env, char *name);
char						*trim_quotes(char *str);
void						unset(char *name, t_cmd *cmd);
void						env(t_cmd *cmd);
void						robo_pwd(void);
void						robo_exit(char **str, t_cmd *cmd);
void						update_env(char **env, int j, char *name,
								char *value);
void						error_export(t_cmd **cmd);
void						handle_added(t_cmd **cmd, t_exp *export, int i,
								int j);
void						print_with_value(char *name, char *value);
void						handle_invalid(char *name);
void						free_it(char **str, size_t i);
void						save_export_to_expo(t_cmd **cmd);
void						check_redirection_mult_nosiggrle(int mult[],
								int conflect_handle[], int is_file_enter[],
								char *input);
void						init_check_redirection_mult(int mult[],
								int conflect_handle[], int is_file_enter[]);
void						setup_extra_command_2(char **split_2,
								char **command);
void						set_data_extr_apy_redir(int *which, char *temp2,
								char **temp4, char **redirection_split);
int							word_count_custuom(char const *s, char c);
size_t						word_len_custuom(char *s, char c, int *flag);
char						**ft_split_custom_exp(char const *s, char c);
char						*extract_filename(char **redirection_split,
								int ccount);
int							manager_execution_heredoc(char *file, char **temp);
int							set_init(t_cmd **cmd, int size);
int							searching_here_doc_2(t_cmd **cmd,
								t_here_doc **here_doc, t_list **current,
								int i_p[]);
int							searching_here_doc(t_cmd **cmd,
								t_here_doc **here_doc);
int							sizeof_heredoc(char *str);
int							here_doc_manger(t_cmd **cmd, char **file_loc);
int							setup_execution(t_cmd **cmd, int *size);
int							setup_execution_heredoc(t_cmd **cmd,
								char ***file_loc);
int							open_pipe(t_cmd **cmd, int size, int pipe_fd2[][2]);
int							execution_process(t_cmd **cmd, int size,
								char **file_loc);
int							run_buildin_execution(t_cmd *cmd, t_list *current);
int							str_size_element(char const *s, char c);
int							setup_extra_command_h(char *temp5, char **command);
int							ft_heredoc_redirection_process(char **str,
								char *temp);
int							ft_heredoc_redirection_manager(char *file,
								char **str);
int							execute_heredoc_setup_exe(char *file,
								char **file_loc, int i, char **temp);
int							execute_heredoc_manage_exeu(char *file, char **str,
								char **ev, char *temp);
int							execute_heredoc_redirection(char ***redirection_split,
								char *str, char *st, char **ev);
int							execute_heredoc(char *file, char **ev, int i,
								char **file_loc);
int							dup_process_2_handle(t_cmd **cmd, t_list **current,
								char **env);
void						handle_here_doc_unlink(t_cmd **cmd,
								char **file_loc);
void						run_export_execution(char **run);
void						child_process_close(int pipe_fd2[][2], pid_t pids[],
								int i, int size);
void						setup_extra_command_h_2(char **split_2,
								char **command);
void						dup_process_handle(int size, int pipe_fd2[][2]);
void						free_every(t_cmd *cmd);

#endif