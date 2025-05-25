/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:22 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/25 23:17:01 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* 
int	ft_mod(int a, int b)
{
	int	r;

	if (b < 0)
		b = -b;
	r = a % b;
	if (r < 0)
		r += b;
	return (r);
} */

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

static void	free_exit(t_cmd *cmd)
{
	if (cmd->env)
		frees_split(cmd->env);
	if (cmd->expo)
		frees_split(cmd->expo);
	if (cmd->here_doc)
	{
		if (cmd->here_doc->file_loc)
			free(cmd->here_doc->file_loc);
		free(cmd->here_doc);
	}
	if (cmd->word)
		free_list(&(cmd->word));
	free(cmd);
}

void	robo_exit(char **split, t_cmd *cmd)
{
	long long	value;
	int			size;

	cmd->exit_status = 0;
	size = ft_strlen(split[1]);
	value = 0;
	if (split && split[1])
	{
		if (!check_n(split[1]))
		{
			ft_printf("%2exit: %s: numeric argument required\n", split[1]);
			cmd->exit_status = 255;
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
