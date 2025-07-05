/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:58:41 by nqasem            #+#    #+#             */
/*   Updated: 2025/05/27 21:59:15 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_pipe(t_cmd **cmd, int size, int pipe_fd2[][2])
{
	int	i;

	i = 0;
	if (!cmd || !(*cmd) || !(*cmd)->word)
	{
		ft_printf("%2Invalid command structure");
		return (-1);
	}
	if (size == 0)
	{
		ft_printf("%2No commands to execute");
		return (-1);
	}
	while (i < size - 1)
	{
		if (pipe(pipe_fd2[i]) == -1)
		{
			ft_printf("%2pipe failed at index %d\n", i);
			return (-1);
		}
		i++;
	}
	return (0);
}
