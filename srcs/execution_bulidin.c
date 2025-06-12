/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bulidin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:13:20 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/12 20:59:11 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_export_execution(char **run)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (run[i])
	{
		j = ft_strlen(run[i]);
		write(1, run[i], j);
		write(1, "\n", 1);
		i++;
	}
}

int	run_buildin_exechr(t_cmd **cmd, char *command)
{
	t_list	*edit_command;

	edit_command = malloc(sizeof(t_list));
	if (!edit_command)
		return (-1);
	edit_command->content = command;
	edit_command->next = NULL;
	if (run_buildin_execution(*cmd, edit_command) < 0)
	{
		free(edit_command);
		return (-1);
	}
	free(edit_command);
	return (0);
}

int	run_buildin_execution_3(t_cmd *cmd, t_list *current, char *tmp)
{
	if (ft_strcmp(tmp, "exit") == 0)
	{
		free(tmp);
		cmd->bulidin = 14;
		return (-1);
	}
	else
	{
		if (run_buildin_execution_4(cmd, current, tmp) < 0)
			return (-1);
	}
	return (0);
}

int	run_buildin_execution_2(t_cmd *cmd, t_list *current, char *tmp)
{
	if (ft_strcmp(tmp, "env") == 0)
	{
		free(tmp);
		run_export_execution(cmd->env);
		cmd->bulidin = 12;
		return (-1);
	}
	else if (ft_strcmp(tmp, "pwd") == 0)
	{
		free(tmp);
		robo_pwd();
		cmd->bulidin = 13;
		return (-1);
	}
	else if (ft_strncmp(tmp, "echo", 4) == 0)
	{
		if (run_buildin_echo(tmp, cmd) < 0)
			return (-1);
		ft_echo(current);
		cmd->bulidin = 17;
		(cmd)->exit_status = 0;
		return (-1);
	}
	else if (run_buildin_execution_3(cmd, current, tmp) < 0)
		return (-1);
	return (0);
}

int	run_buildin_execution(t_cmd *cmd, t_list *current)
{
	char	*tmp;

	tmp = ft_strtrim(current->content, " ");
	if (!tmp)
		return (-1);
	if (ft_strcmp(tmp, "export") == 0)
	{
		free(tmp);
		run_export_execution(cmd->expo);
		frees_split(cmd->expo);
		cmd->bulidin = 11;
		cmd->expo = NULL;
		return (-1);
	}
	else if (run_buildin_execution_2(cmd, current, tmp) < 0)
		return (free_err_ret(NULL, NULL, NULL, -1));
	else if (ft_strncmp(tmp, "export", 6) == 0)
	{
		free(tmp);
		cmd->bulidin = 15;
		return (-1);
	}
	free(tmp);
	return (0);
}
