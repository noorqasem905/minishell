/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:11 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/24 01:20:30 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define COLOR_CUSTOM "\x1b[38;2;42;161;179m"
#define COLOR_RESET "\x1b[0m"

int	searching_bulidin_2(char **split, t_cmd **cmd, char *t)
{
	int	s;

	if (ft_strcmp(split[0], "export") == 0)
	{
		ft_export(t, cmd);
		return (13);
	}
	if (ft_strcmp(split[0], "unset") == 0)
	{
		s = 1;
		while (split[s])
		{
			robo_unset(split[s], cmd);
			s++;
		}
		return (-3);
	}
	if (ft_strcmp(split[0], "env") == 0)
	{
		env(*cmd);
		return (-3);
	}
	return (0);
}

int	searching_bulidin(char **split, t_cmd **cmd, char *t, char **input)
{
	int ret;

	ret = searching_bulidin_2(split, cmd, t);
	if(ret < 0)
		return (ret);
	if (ft_strcmp(split[0], "pwd") == 0)
		robo_pwd();
	if (ft_strncmp(split[0], "cd", 2) == 0)
	{
		robo_cd(split, (*cmd)->env);
		free(*input);
		return (-3);
	}
	/*if (ft_strcmp(split[0], "exit") == 0)
		robo_exit(split, *cmd);*/
	return (0);
}

void	handle_here_doc_nolink(t_cmd **cmd)
{
	int	no;

	no = 0;
	while (no < (*cmd)->here_doc->counter)
	{
		if ((*cmd)->here_doc->file_loc[no])
		{
			free((*cmd)->here_doc->file_loc[no]);
			(*cmd)->here_doc->file_loc[no] = NULL;
		}
		no++;
	}
	if ((*cmd)->here_doc->file_loc)
	{
		free((*cmd)->here_doc->file_loc);
		(*cmd)->here_doc->file_loc = NULL;
	}
}

int	exitting_handle(int ret, t_cmd **cmd, char **input)
{
	if (ret == -1)
	{
		free(*input);
		if ((*cmd)->here_doc->file_loc)
			handle_here_doc_nolink(cmd);
		if ((*cmd)->here_doc->pryority)
			free((*cmd)->here_doc->pryority);
		if ((*cmd)->exit_status == -13)
			return (-14);
		return (-12);
	}
	if (ret == 65)
	{
		if ((*cmd)->here_doc->file_loc)
			handle_here_doc_nolink(cmd);
		if ((*cmd)->here_doc->pryority)
			free((*cmd)->here_doc->pryority);
		(*cmd)->here_doc->pryority = NULL;
		(*cmd)->here_doc->file_loc = NULL;
		return (0);
	}
	free(*input);
	return (0);
}
int	process_handle_input(t_cmd **cmd, int *flag, char ***temp, char **input)
{
	if (*input)
		add_history(*input);
	if (check_no_pipe(*input) && check_pipe_input(*input) == -1)
	{
		dprintf(2, "Syntax error: Invalid pipe usage\n");
		return (-42);
	}
	*temp = ft_split(*input, '|');
	if (!*temp)
		return (-1);
	if (!*temp[0])
	{
		free(*temp);
		return (-42);
	}
	if (save_data(NULL, cmd, flag, temp) == -1 || *flag == -3)
	{
		if (*flag == -3)
			return (-3);
		return (-1);
	}
	return(0);
}

int	process_set_input(t_cmd **cmd, char **t, char ***split, char **input)
{
	int	ret_of_searching;

	if (!(*split) || !*(*split))
	{
		if ((*split))
			free((*split));
		free(*input);
		return (-3);
	}
	*t = expander_input(cmd);
	ret_of_searching = searching_bulidin((*split), cmd, (*t), input);
	if (ret_of_searching < 0)
	{
		free(*t);
		frees_split((*split));
		return (ret_of_searching);
	}
	free(*t);
	frees_split((*split));
	return (ret_of_searching);
}

int	process_input_leaks(t_cmd **cmd, int ret)
{
	if (ret < 0)
		return(ret);
	if ((*cmd)->here_doc->file_loc)
		handle_here_doc_nolink(cmd);
	if ((*cmd)->here_doc->pryority)
		free((*cmd)->here_doc->pryority);
	return (0);
}

int	process_input(t_cmd **cmd, int *flag, char ***temp, char **input)
{
	t_list	*current;
	char	**split;
	char	*t;
	int		ret_of_searching;

	ret_of_searching = process_handle_input(cmd, flag, temp, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	if (searching_comand(input, *temp) == -1)
		return (-1);
	split = ft_split((*temp)[0], ' ');
	ret_of_searching = process_set_input(cmd, &t, &split, input);
	if (ret_of_searching < 0)
		return(ret_of_searching);
	if (searching_comand(input, *temp) == -13)
		return (-13);
	expand_cmds(cmd, *input);
	ret_of_searching = execution(cmd);
	ret_of_searching = exitting_handle(ret_of_searching, cmd, input);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	ret_of_searching = process_input_leaks(cmd, ret_of_searching);
	if (ret_of_searching < 0)
		return (ret_of_searching);
	return (0);
}

int	reading_manager(t_cmd **cmd, int *flag, char ***temp, char **robo_env)
{
	char	*input;
	int		ret;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while ((input = readline(COLOR_CUSTOM "~/Roboshell> " COLOR_RESET)) != NULL)
	{
		if (is_closed(input) == -1)
		{
			ft_printf("%2Syntax error: Unclosed quotes\n");
			free(input);
			continue ;
		}
		ret = process_input(cmd, flag, temp, &input);
		if (ret < 0 && ret != -3 && ret != -42 && ret != -55)
		{
			frees_split(*temp);
			free_list((&(*cmd)->word));
			if (ret == -1)
				ft_printf("%2No command found\n");
			if (ret == -12)
			{
				frees_split((*cmd)->env);
				if ((*cmd)->expo)
					frees_split((*cmd)->expo);
				(*cmd)->expo = NULL;
				free((*cmd)->here_doc);
				free(*cmd);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		else if (ret == -3 || ret == -14)
		{
			*flag = 0;
			frees_split(*temp);
			free_list(&(*cmd)->word);
			// free((*cmd)->word);
			continue ;
		}
		else if (ret == -42)
			continue ;
		frees_split(*temp);
		free_list(&(*cmd)->word);
	}
	ft_printf("Exiting...\n");
	return (0);
}
