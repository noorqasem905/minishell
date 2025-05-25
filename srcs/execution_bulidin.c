/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bulidin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:13:20 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/25 23:26:02 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_export_execution(char **run)
{
	int	i;

	i = 0;
	while (run[i])
	{
		ft_printf("%s\n", run[i]);
		i++;
	}
}

static int	check_env(t_cmd *cmd)
{
	run_export_execution(cmd->env);
	return (-1);
}

int	run_buildin_execution(t_cmd *cmd, t_list *current)
{
	char	*tmp;
	char	**split;

	tmp = ft_strtrim(current->content, " ");
	if (!tmp)
		return (-1);
	if (ft_strcmp(tmp, "export") == 0)
	{
		free(tmp);
		run_export_execution(cmd->expo);
		frees_split(cmd->expo);
		cmd->expo = NULL;
		return (-1);
	}
	else if (ft_strcmp(tmp, "env") == 0)
	{
		free(tmp);
		check_env(cmd);
	}
	else if (ft_strcmp(tmp, "pwd") == 0)
	{
		free(tmp);
		robo_pwd();
		return (-1);
	}
	else if (ft_strcmp(tmp, "exit") == 0)
	{
		free(tmp);
		return (-1);
	}
	else if (ft_strncmp(tmp, "exit", 4) == 0)
	{
		split = ft_split(current->content, ' ');
		robo_exit(split, cmd);
		frees_split(split);
		free(tmp);
		return (-1);
	}
	if (ft_strncmp(tmp, "export", 6) == 0)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}
