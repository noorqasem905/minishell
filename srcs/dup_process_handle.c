/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_process_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:14:36 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/31 15:24:58 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_process_2_handle(t_cmd **cmd, t_list **current)
{
	if (run_buildin_execution(*cmd, *current) < 0)
		return (-1);
	if (ft_execve((*current)->content, cmd) == -1)
	{
		(*cmd)->exit_status = 127;
		ft_printf("%2Command not found\n");
		return (-1);
	}
	return (0);
}

void	dup_process_handle(int size, int pipe_fd2[][2])
{
	int	j;

	j = 0;
	while (j < size - 1)
	{
		close(pipe_fd2[j][0]);
		close(pipe_fd2[j][1]);
		j++;
	}
}
