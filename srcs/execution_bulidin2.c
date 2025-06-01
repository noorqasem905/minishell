/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bulidin2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:31:47 by nqasem            #+#    #+#             */
/*   Updated: 2025/06/01 15:32:22 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
