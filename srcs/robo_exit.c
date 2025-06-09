/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:22 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/09 18:14:41 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_n(char *n)
{
	int	i;

	i = 0;
	if (n[i] == '-' || n[i] == '+')
		i++;
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (0);
		i++;
	}
	return (1);
}

int	robo_exit(char **split, t_cmd *cmd)
{
	cmd->exit_status = 0;
	if (split[1] && split[2])
	{
		ft_printf("%2exit: too many arguments\n");
		cmd->exit_status = 1;
		return (-1);
	}
	if (split[1] && ft_strlen(split[1]) > 0)
	{
		if (!check_n(split[1]))
		{
			ft_printf("%2exit: %s: numeric argument required\n", split[1]);
			cmd->exit_status = 2;
			return (-12);
		}
		else
			cmd->exit_status = ft_mod(ft_atoi_long(split[1]), 256);
	}
	return (-12);
}
