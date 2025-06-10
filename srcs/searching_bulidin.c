/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_bulidin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:43:49 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/10 13:39:48 by aalquraa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	searching_bulidin_3(char **split, t_cmd **cmd)
{
	int	ret;

	if (!ft_strncmp(split[0], "exit", 4)
		&& !ft_strchr((*cmd)->input, '|'))
	{
		(*cmd)->who_am_i = 402;
		ret = robo_exit(split, *cmd);
		if (ret == -1)
			return (-22);
		return (ret);
	}
	return (0);
}

int	searching_bulidin_2(char **split, t_cmd **cmd, char *t)
{
	int	i;

	if (!ft_strncmp(split[0], "export", 6)
		&& !ft_strchr((*cmd)->input, '|'))
	{
		ft_export(t, cmd);
		return (13);
	}
	if (!ft_strncmp(split[0], "unset", 5)
		&& !ft_strchr((*cmd)->input, '|'))
	{
		i = 1;
		while (split[i])
		{
			robo_unset(split[i], cmd);
			i++;
		}
		return (0);
	}
	return (searching_bulidin_3(split, cmd));
}

int	searching_bulidin_exit(char **split, t_cmd **cmd, char **input)
{
	if (!ft_strchr(*input, '|'))
		return (0);
	ft_printf("%2%s\n", *input);
	printf_split("output:", split);
	robo_exit(split, *cmd);
	ft_printf("%2e: %d\n", (*cmd)->exit_status);
	return (0);
}

int	searching_bulidin(char **split, t_cmd **cmd, char *t, char **input)
{
	int	ret;

	ret = searching_bulidin_2(split, cmd, t);
	if (ret < 0)
		return (ret);
	if (ft_strncmp(split[0], "cd", 2) == 0)
	{
		robo_cd(split);
		free(*input);
		return (-3);
	}
	return (0);
}
