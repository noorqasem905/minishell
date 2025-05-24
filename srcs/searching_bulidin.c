/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_bulidin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:43:49 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/24 14:44:04 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int	ret;

	ret = searching_bulidin_2(split, cmd, t);
	if (ret < 0)
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
