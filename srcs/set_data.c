/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:11 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 16:53:14 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define COLOR_CUSTOM "\x1b[38;2;42;161;179m"
#define COLOR_RESET "\x1b[0m"

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
			free((*cmd)->here_doc->file_loc);
		if ((*cmd)->here_doc->pryority)
			free((*cmd)->here_doc->pryority);
		(*cmd)->here_doc->pryority = NULL;
		(*cmd)->here_doc->file_loc = NULL;
		return (0);
	}
	free(*input);
	return (0);
}

int	reading_manager_handle_2(t_cmd **cmd, int ret, char ***temp)
{
	int	exit_status;

	exit_status = 0;
	frees_split(*temp);
	free_list((&(*cmd)->word));
	if ((*cmd)->who_am_i == 102)
		(*cmd)->exit_status = 0;
	if (ret == -1)
	{
		ft_printf("%2No command found\n");
		(*cmd)->exit_status = 127;
	}
	if (ret == -12)
	{
		frees_split((*cmd)->env);
		if ((*cmd)->expo)
			frees_split((*cmd)->expo);
		(*cmd)->expo = NULL;
		free((*cmd)->here_doc);
		exit_status = (*cmd)->exit_status;
		if ((*cmd)->who_am_i == 42)
			exit_status = 42;
		free(*cmd);
		exit(exit_status);
	}
	return (25);
}

int	reading_manager_handle(t_cmd **cmd, int *flag, char ***temp, char **input)
{
	int	ret;

	ret = process_input(cmd, flag, temp, input);
	if ((*cmd)->who_am_i == 102)
		(*cmd)->exit_status = 0;
	if (ret < 0 && ret != -3 && ret != -42 && ret != -55)
		return (reading_manager_handle_2(cmd, ret, temp));
	else if (ret == -3 || ret == -14)
	{
		*flag = 0;
		frees_split(*temp);
		free_list(&(*cmd)->word);
		return (26);
	}
	else if (ret == -42)
		return (26);
	frees_split(*temp);
	free_list(&(*cmd)->word);
	return (0);
}

int	reading_manager(t_cmd **cmd, int *flag, char ***temp, char **robo_env)
{
	char	*input;
	int		ret;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(COLOR_CUSTOM "~/Roboshell> " COLOR_RESET);
		if (input == NULL)
			break ;
		if (is_closed(input) == -1)
		{
			ft_printf("%2Syntax error: Unclosed quotes\n");
			(*cmd)->exit_status = 1;
			free(input);
			continue ;
		}
		ret = reading_manager_handle(cmd, flag, temp, &input);
		if (ret == 25)
			break ;
		else if (ret == 26)
			continue ;
	}
	ft_printf("exit\n");
	return (0);
}
