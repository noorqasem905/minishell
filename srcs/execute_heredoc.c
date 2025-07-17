/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:54:15 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/17 14:58:26 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	manager_execution_heredoc(char *file, char **temp)
{
	char	*command;
	int		which;

	which = which_redirection_char(file);
	command = ft_strfchr(file, which);
	if (setup_extra_command_h(file, &command))
	{
		free(command);
		return (-1);
	}
	*temp = command;
	return (0);
}

static int	st_protuction(char **st, char *temp, char *str)
{
	(*st) = ft_strjoin(temp, str);
	if (!(*st))
	{
		free_err_ret(NULL, str, NULL, -1);
		return (free_err_ret(NULL, temp, NULL, -1));
	}
	return (0);
}

static int	nono_heredoc_command(char *temp, t_cmd **cmd)
{
	int	i;

	i = 0;
	while (ft_isspace(temp[i]))
		i++;
	if (!temp[i])
	{
		(*cmd)->flag = 19;
		(*cmd)->exit_status = 0;
		free(temp);
		return (-1);
	}
	return (0);
}

int	execute_heredoc(char *file, t_cmd **cmd, int i)
{
	char	**redirection_split;
	char	*temp;
	char	*str;
	char	*st;

	(*cmd)->flag = 0;
	if (execute_heredoc_setup_exe(file, cmd, i, &temp) < 0)
		return (-1);
	nono_heredoc_command(temp, cmd);
	if (execute_heredoc_manage_exeu(file, &str, cmd, temp) < 0)
		return (-1);
	if ((*cmd)->flag == 19)
		temp = "ls";
	st_protuction(&st, temp, str);
	if (execute_heredoc_red(&redirection_split, str, st, cmd) < 0)
	{
		if ((*cmd)->exit_status != 127)
			(*cmd)->exit_status = 2;
		if (temp)
			free(temp);
		return (-1);
	}
	if (temp)
		free(temp);
	return (0);
}
