/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:22 by aalquraa          #+#    #+#             */
/*   Updated: 2025/05/25 15:17:31 by nqasem           ###   ########.fr       */
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
	cmd->exit_status = 0;
	ft_printf("exit\n");
	if (split && split[1])
	{
		if (!check_n(split[1]))
		{
			ft_printf("%2exit: %s: numeric argument required\n", split[1]);
			cmd->exit_status = 255;
		}
		else if (split[2])
		{
			ft_printf("%2exit: too many arguments\n");
			cmd->exit_status = 1;
			return ;
		}
		else
			cmd->exit_status = ft_atoi(split[1]);
	}
}
