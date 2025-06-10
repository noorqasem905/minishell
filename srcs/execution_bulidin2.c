/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bulidin2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:31:47 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/10 15:49:52 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_buildin_execution_4(t_cmd *cmd, t_list *current, char *tmp)
{
	char	**split;

	if (ft_strncmp(tmp, "exit", 4) == 0)
	{
		split = ft_split(current->content, ' ');
		if (!split)
		{
			free(tmp);
			return (-1);
		}
		robo_exit(split, cmd);
		frees_split(split);
		free(tmp);
		cmd->bulidin = 16;
		return (-1);
	}
	else if (ft_strncmp(tmp, "unset", 5) == 0)
	{
		free(tmp);
		cmd->bulidin = 18;
		return (-1);
	}
	return (0);
}

int	run_buildin_echo(char *tmp, t_cmd *cmd)
{
	if (ft_strlen(tmp) == 4)
	{
		free(tmp);
		cmd->bulidin = 17;
		return (-1);
	}
	if (!ft_isspace(tmp[4]))
	{
		free(tmp);
		cmd->bulidin = 17;
		ft_printf("%2Command not found\n");
		return (-1);
	}
	free(tmp);
	return (0);
}
