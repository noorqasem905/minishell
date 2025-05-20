/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bulidin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:13:20 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/20 17:14:00 by nqasem           ###   ########.fr       */
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

int	run_buildin_execution(t_cmd *cmd, t_list *current)
{
	char	*tmp;

	tmp = ft_strtrim(current->content, " ");
	if (!tmp)
		return (-1);
	if (ft_strcmp(tmp, "export") == 0 || ft_strcmp(tmp, "env") == 0)
	{
		free(tmp);
		run_export_execution(cmd->env);
		return (-1);
	}
	free(tmp);
	return (0);
}
