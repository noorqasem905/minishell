/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:43:02 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/04 22:51:40 by aalquraa         ###   ########.fr       */
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
	int						counter_total;
	int						index;
	char					*input;
	char					*temp;
};
struct						s_cmd
{
	t_here_doc				*here_doc;
	t_list					*word;
	t_list					*current;
	char					*input;
	char					**expo;
	char					**env;
	int						*pryority;
	int						who_am_i;
	int						counter;
	int						index;
	int						bulidin;
	int						exit_status;
	int						flag;
};
typedef struct s_split_state
{
	size_t					i;
	char					quote_char;
}							t_split_state;
void						remove_quote_condition(char **str, char *who_im_i,
								int save_i[3], int *close);
int							heredoc(char *temp, char **file_loc, size_t size);
int							handle_here_doc(char *temp);
struct						s_exp
{
	char					**name;
	char					**value;
	int						flag;
};
void						remove_quote(char **str);
int							check_redirection_mult_siggr(int mult[],
								int conflect_handle[], int is_file_enter[],
								char *input);
int							free_err_ret(char *message, void *free_it,
								char **free_splt, int ret_value);
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
								char **temp, char *input, char **temp3);
int							error_ft_execute_redirection(char *temp,
								char *command, t_cmd **cmd, int i);
int							process_input(t_cmd **cmd, int *flag, char ***temp,
								char **input);
int							check_validation(char **paths, char **result,
								char **m);
int							check_extra_redirection(char *tmp);
int							check_append_redirection(char **curr,
								int heredoc_append[]);
int							ft_heredoc_redirection_manager_2(int *j, char **str,
								char **tmp);
void						init_append_redirection(int heredoc_append[]);
void						close_wait2(pid_t pids[], int size, t_cmd **cmd);
int							child_process(t_cmd **cmd, int pipe_fd2[][2],
								pid_t pids[]);
int							dup_process(int *i, int size, int pipe_fd2[][2]);
int							dup_process_2(t_cmd **cmd, t_list **current, int i);
int							get_path(char **ev);
int							ft_strfind(char *str, char *c);
int							execution(t_cmd **cmd);
int							ft_execve(char *file, t_cmd **cmd);
int							searching_comand(char **temp);
int							save_data(t_cmd **cmd, int *flag, char ***temp);
int							which_redirection_char(char *temp);
int							reading_manager(t_cmd **cmd, int *flag,
								char ***temp);
int							ft_redirection(char *input,
								char ***redirection_split, t_cmd **cmd);
int							ft_execute_redirection(char **redirection_split,
								int ccount_i[], int *fd, char *temp3);
int							process_redirections(char ***redirection_split,
								t_cmd **cmd, char **temp3, int i);
int							handle_mult_redirection(char *temp3, char *temp2,
								char **temp, char ***redirection_split);
int							extract_and_apply_redirection(char **temp,
								char *temp2, char ***redirection_split,
								char **command);
int							handle_redirection_segment(char
								***redirection_split,
								char **temp, char **temp4, char *th);
int							read_input(char **input);
size_t						element_size(char **str);
void						close_wait(pid_t pids[], int size,
								int pipe_fd2[][2], t_cmd **cmd);
void						extract_apply_short_3(char **tmp, char **temp,
								char *temp4, char **command);
int							extract_apply_short(char **temp, char **tmp,
								char ***redirection_split, char *temp4_copy);
void						free_list(t_list **root);
void						frees(t_list **root);
void						printf_split(char *str, char **split);
void						robo_cd(char **temp);
void						free_it_noww(char **s, char *s2, int emassage);
void						signal_handler(int x);
char						*check_access(char **paths, char **result);
char						*expander_input(t_cmd **cmd);
void						expand_cmds(t_cmd **cmd, char *input);
char						**my_env(char **env);
void						robo_unset(char *name, t_cmd **cmd);
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
void						robo_exit(char **split, t_cmd *cmd);
void						env(t_cmd *cmd);
void						handle_here_doc_nolink(t_cmd **cmd);
void						robo_pwd(void);
void						update_env(char **env, int j, char *name,
								char *value);
void						error_export(t_cmd **cmd);
void						handle_added(t_cmd **cmd, t_exp *export, int i,
								int j);
void						skip_delimiters(char const **s, char c);
void						skip_word(char const **s, char c, int *flag,
								char *quote_char);
void						print_with_value(char *name, char *value);
void						handle_invalid(char *name, t_cmd **cmd);
void						print_saved_cmd(t_list *saved_cmd);
void						free_it(char **str, size_t i);
void						save_export_to_expo(t_cmd **cmd);
void						check_redirection_mult_nosiggrle(int mult[],
								int conflect_handle[], int is_file_enter[]);
void						init_check_redirection_mult(int mult[],
								int conflect_handle[], int is_file_enter[]);
void						setup_extra_command_2(char **split_2,
								char **command);
void						set_data_extr_apy_redir(int *which, char *temp2,
								char **temp4, char **redirection_split);
int							word_count_custom(char const *s, char c);
size_t						word_len_custom(char *s, char c, int *flag,
								char *quote_char);
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
int							setup_execution(t_cmd **cmd);
int							setup_execution_heredoc(t_cmd **cmd,
								char ***file_loc);
int							open_pipe(t_cmd **cmd, int size, int pipe_fd2[][2]);
int							execution_process(t_cmd **cmd);
int							run_buildin_execution(t_cmd *cmd, t_list *current);
int							run_buildin_execution_2(t_cmd *cmd, t_list *current,
								char *tmp);
int							run_buildin_execution_3(t_cmd *cmd, t_list *current,
								char *tmp);
int							run_buildin_exechr(t_cmd **cmd, char *command);
int							str_size_element(char const *s, char c);
int							setup_extra_command_h(char *temp5, char **command);
int							ft_heredoc_redirection_process(char **str,
								char *temp);
int							run_buildin_echo(char *tmp, t_cmd *cmd);
void						remove_qoute(char **str);
int							ft_heredoc_redirection_manager(char *file,
								char **str);
int							execute_heredoc_setup_exe(char *file, t_cmd **cmd,
								int i, char **temp);
int							execute_heredoc_manage_exeu(char *file,
								char **str, t_cmd **cmd,
								char *temp);
int							execute_heredoc_redirection(
								char	***redirection_split,
								char *str, char *st, t_cmd **cmd);
int							execute_heredoc(char *file, t_cmd **cmd, int i);
int							dup_process_2_handle(t_cmd **cmd, t_list **current);
void						handle_here_doc_unlink(t_cmd **cmd);
void						run_export_execution(char **run);
void						child_process_close(int pipe_fd2[][2], int i,
								int size);
void						setup_extra_command_h_2(char **split_2,
								char **command);
void						dup_process_handle(int size, int pipe_fd2[][2]);
int							handle_cd_slash(char *temp);
int							handle_cd_dup_dot(char *temp);
int							build_quoted_string(char **dir, char ***temp,
								int total_len, int *end);
int							merge_quoted_tokens(char ***temp, char **dir,
								int start, int *end);
int							handle_space_infile(char ***temp, char **dir);
int							robo_cd_access(char **dir, char **temp);
char						*trim_quotess(char *str);
void						frees_newsplit(char **root);
t_exp						*init_export(int count);
size_t						word_lenn(char *s, char c);
void						free_exp(t_exp *export);
void						ft_echo_setquotes(char *first, char value);
void						ft_echo_ignore_quotes(int new_line, int ignore,
								char *buff);
int							handle_here_doc_qouts(char *temp);
int							process_token(char **buff, char *token,
								char *ignore);
int							ft_echo_quotes(char *word, char *ignore);
void						ski_delimiters(char **s, char c);
int							is_there_else_heredoc(char *temp);
int							handle_here_doc(char *temp);
char						*strip_outer_quotes(char *str);
int							ft_echo(t_list *command);
int							ft_echo_quotes_manger(char **split, int *index,
								char *ignore, char **buff);
int							get_free_filename(char **file_loc,
								char *new_fullpath);
int							openfile_heredoc(int *fd, char **file_loc);
char						*ft_strjoin_free(char *s1, char *s2);
int							append_char(char **expanded, char ch);
int							append_expansion(char **expanded, char *content,
								int *i, t_cmd *cmd);
void						no_space(int *l, char **m, char **o);
int							is_closed(char *input);
int							check_no_pipe(char *input);
int							check_pipe_input(char *input);
int							searching_bulidin_2(char **split, t_cmd **cmd,
								char *t);
int							searching_bulidin(char **split, t_cmd **cmd,
								char *t, char **input);
int							exitting_handle(int ret, t_cmd **cmd, char **input);
int							process_handle_input(t_cmd **cmd, int *flag,
								char ***temp, char **input);
int							process_set_input(t_cmd **cmd, char **t,
								char ***split, char **input);
int							process_input_leaks(t_cmd **cmd, int ret);
int							reading_manager_handle_2(t_cmd **cmd, int ret,
								char ***temp);
int							reading_manager_handle(t_cmd **cmd, int *flag,
								char ***temp, char **input);
void						set_parent_signals(void);
void						dfl_parent_signals(void);
void						quote_remove_helper(char **str, int *save_i,
								int *close, int *allow);
void						no_value_of_echo(char *str, int save_i[3],
								int *allow);
int							searching_here_doc_2(t_cmd **cmd,
								t_here_doc **here_doc, t_list **current,
								int i_p[]);
int							searching_here_doc(t_cmd **cmd,
								t_here_doc **here_doc);
int							searching_here_doc_2_logic(t_cmd **cmd,
								t_here_doc **here_doc, t_list **current,
								int i_p[]);
#endif