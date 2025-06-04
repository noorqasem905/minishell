/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalquraa <aalquraa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:22 by aalquraa          #+#    #+#             */
/*   Updated: 2025/06/04 19:17:36 by aalquraa         ###   ########.fr       */
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

void	robo_exit(char **split, t_cmd *cmd)
{
	long long	value;
	int			size;

	ft_printf("exit\n");
	cmd->exit_status = 0;
	size = ft_strlen(split[1]);
	value = 0;
	if (split && split[1])
	{
		if (!check_n(split[1]))
		{
			ft_printf("%2exit: %s: numeric argument required\n", split[1]);
			cmd->exit_status = 1;
		}
		else if (split[2] || size > 19)
		{
			ft_printf("%2exit: too many arguments\n");
			cmd->exit_status = 1;
			return ;
		}
		else
			cmd->exit_status = ft_mod(ft_atoi_long(split[1]), 256);
	}
}
